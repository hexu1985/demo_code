/* 
 * Copyright © 2001 Keith Packard, member of The XFree86 Project, Inc.
 * Copyright © 2002 Hewlett Packard Company, Inc.
 * Copyright © 2006 Intel Corporation
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 *
 * Thanks to Jim Gettys who wrote most of the client side code,
 * and part of the server code for randr.
 */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xrender.h>	/* we share subpixel information */
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <math.h>

static char	*program_name;
static Display	*dpy;
static Window	root;
static int	screen = -1;
static Bool	verbose = False;
static Bool	automatic = False;
static Bool	properties = False;
static Bool	providers = False;
static Bool	grab_server = True;
static Bool	no_primary = False;

static const char *direction[5] = {
    "normal", 
    "left", 
    "inverted", 
    "right",
    "\n"};

static const char *reflections[5] = {
    "normal", 
    "x", 
    "y", 
    "xy",
    "\n"};

/* subpixel order */
static const char *order[6] = {
    "unknown",
    "horizontal rgb",
    "horizontal bgr",
    "vertical rgb",
    "vertical bgr",
    "no subpixels"};

static const struct {
    const char	    *string;
    unsigned long   flag;
} mode_flags[] = {
    { "+HSync", RR_HSyncPositive },
    { "-HSync", RR_HSyncNegative },
    { "+VSync", RR_VSyncPositive },
    { "-VSync", RR_VSyncNegative },
    { "Interlace", RR_Interlace },
    { "DoubleScan", RR_DoubleScan },
    { "CSync",	    RR_CSync },
    { "+CSync",	    RR_CSyncPositive },
    { "-CSync",	    RR_CSyncNegative },
    { NULL,	    0 }
};

static void _X_NORETURN
usage(void)
{
    fprintf(stderr, "usage: %s [options]\n", program_name);
    fprintf(stderr, "  where options are:\n");
    fprintf(stderr, "  -display <display> or -d <display>\n");
    fprintf(stderr, "  -help\n");
    fprintf(stderr, "  -o <normal,inverted,left,right,0,1,2,3>\n");
    fprintf(stderr, "            or --orientation <normal,inverted,left,right,0,1,2,3>\n");
    fprintf(stderr, "  -q        or --query\n");
    fprintf(stderr, "  -s <size>/<width>x<height> or --size <size>/<width>x<height>\n");
    fprintf(stderr, "  -r <rate> or --rate <rate> or --refresh <rate>\n");
    fprintf(stderr, "  -v        or --version\n");
    fprintf(stderr, "  -x        (reflect in x)\n");
    fprintf(stderr, "  -y        (reflect in y)\n");
    fprintf(stderr, "  --screen <screen>\n");
    fprintf(stderr, "  --verbose\n");
    fprintf(stderr, "  --current\n");
    fprintf(stderr, "  --dryrun\n");
    fprintf(stderr, "  --nograb\n");
    fprintf(stderr, "  --prop or --properties\n");
    fprintf(stderr, "  --fb <width>x<height>\n");
    fprintf(stderr, "  --fbmm <width>x<height>\n");
    fprintf(stderr, "  --dpi <dpi>/<output>\n");
    fprintf(stderr, "  --output <output>\n");
    fprintf(stderr, "      --auto\n");
    fprintf(stderr, "      --mode <mode>\n");
    fprintf(stderr, "      --preferred\n");
    fprintf(stderr, "      --pos <x>x<y>\n");
    fprintf(stderr, "      --rate <rate> or --refresh <rate>\n");
    fprintf(stderr, "      --reflect normal,x,y,xy\n");
    fprintf(stderr, "      --rotate normal,inverted,left,right\n");
    fprintf(stderr, "      --left-of <output>\n");
    fprintf(stderr, "      --right-of <output>\n");
    fprintf(stderr, "      --above <output>\n");
    fprintf(stderr, "      --below <output>\n");
    fprintf(stderr, "      --same-as <output>\n");
    fprintf(stderr, "      --set <property> <value>\n");
    fprintf(stderr, "      --scale <x>x<y>\n");
    fprintf(stderr, "      --scale-from <w>x<h>\n");
    fprintf(stderr, "      --transform <a>,<b>,<c>,<d>,<e>,<f>,<g>,<h>,<i>\n");
    fprintf(stderr, "      --off\n");
    fprintf(stderr, "      --crtc <crtc>\n");
    fprintf(stderr, "      --panning <w>x<h>[+<x>+<y>[/<track:w>x<h>+<x>+<y>[/<border:l>/<t>/<r>/<b>]]]\n");
    fprintf(stderr, "      --gamma <r>:<g>:<b>\n");
    fprintf(stderr, "      --primary\n");
    fprintf(stderr, "  --noprimary\n");
    fprintf(stderr, "  --newmode <name> <clock MHz>\n");
    fprintf(stderr, "            <hdisp> <hsync-start> <hsync-end> <htotal>\n");
    fprintf(stderr, "            <vdisp> <vsync-start> <vsync-end> <vtotal>\n");
    fprintf(stderr, "            [flags...]\n");
    fprintf(stderr, "            Valid flags: +HSync -HSync +VSync -VSync\n");
    fprintf(stderr, "                         +CSync -CSync CSync Interlace DoubleScan\n");
    fprintf(stderr, "  --rmmode <name>\n");
    fprintf(stderr, "  --addmode <output> <name>\n");
    fprintf(stderr, "  --delmode <output> <name>\n");
    fprintf(stderr, "  --listproviders\n");
    fprintf(stderr, "  --setprovideroutputsource <prov-xid> <source-xid>\n");
    fprintf(stderr, "  --setprovideroffloadsink <prov-xid> <sink-xid>\n");

    exit(1);
    /*NOTREACHED*/
}

static void _X_NORETURN
fatal (const char *format, ...)
{
    va_list ap;
    
    va_start (ap, format);
    fprintf (stderr, "%s: ", program_name);
    vfprintf (stderr, format, ap);
    va_end (ap);
    exit (1);
    /*NOTREACHED*/
}

static void
warning (const char *format, ...)
{
    va_list ap;
    
    va_start (ap, format);
    fprintf (stderr, "%s: ", program_name);
    vfprintf (stderr, format, ap);
    va_end (ap);
}

/* Because fmin requires C99 suppport */
static inline double dmin (double x, double y)
{
    return x < y ? x : y;
}

static const char *
rotation_name (Rotation rotation)
{
    int	i;

    if ((rotation & 0xf) == 0)
	return "normal";
    for (i = 0; i < 4; i++)
	if (rotation & (1 << i))
	    return direction[i];
    return "invalid rotation";
}

static const char *
reflection_name (Rotation rotation)
{
    rotation &= (RR_Reflect_X|RR_Reflect_Y);
    switch (rotation) {
    case 0:
	return "none";
    case RR_Reflect_X:
	return "X axis";
    case RR_Reflect_Y:
	return "Y axis";
    case RR_Reflect_X|RR_Reflect_Y:
	return "X and Y axis";
    }
    return "invalid reflection";
}

static const char *
capability_name (int cap_bit)
{
    switch (cap_bit) {
    case RR_Capability_SourceOutput:
	return "Source Output";
    case RR_Capability_SinkOutput:
	return "Sink Output";
    case RR_Capability_SourceOffload:
	return "Source Offload";
    case RR_Capability_SinkOffload:
	return "Sink Offload";
    }
    return "invalid capability";
}

typedef enum _relation {
    relation_left_of,
    relation_right_of,
    relation_above,
    relation_below,
    relation_same_as,
} relation_t;

typedef struct {
    int	    x, y, width, height;
} rectangle_t;

typedef struct {
    int	    x1, y1, x2, y2;
} box_t;

typedef struct {
    int	    x, y;
} point_t;

typedef enum _changes {
    changes_none = 0,
    changes_crtc = (1 << 0),
    changes_mode = (1 << 1),
    changes_relation = (1 << 2),
    changes_position = (1 << 3),
    changes_rotation = (1 << 4),
    changes_reflection = (1 << 5),
    changes_automatic = (1 << 6),
    changes_refresh = (1 << 7),
    changes_property = (1 << 8),
    changes_transform = (1 << 9),
    changes_panning = (1 << 10),
    changes_gamma = (1 << 11),
    changes_primary = (1 << 12),
} changes_t;

typedef enum _name_kind {
    name_none = 0,
    name_string = (1 << 0),
    name_xid = (1 << 1),
    name_index = (1 << 2),
    name_preferred = (1 << 3),
} name_kind_t;

typedef struct {
    name_kind_t	    kind;
    char    	    *string;
    XID	    	    xid;
    int		    index;
} name_t;

typedef struct _crtc crtc_t;
typedef struct _output	output_t;
typedef struct _transform transform_t;
typedef struct _umode	umode_t;
typedef struct _output_prop output_prop_t;

struct _transform {
    XTransform	    transform;
    const char	    *filter;
    int		    nparams;
    XFixed	    *params;
};

struct _crtc {
    name_t	    crtc;
    Bool	    changing;
    XRRCrtcInfo	    *crtc_info;

    XRRModeInfo	    *mode_info;
    XRRPanning      *panning_info;
    int		    x;
    int		    y;
    Rotation	    rotation;
    output_t	    **outputs;
    int		    noutput;
    transform_t	    current_transform, pending_transform;
};

struct _output_prop {
    struct _output_prop	*next;
    char		*name;
    char		*value;
};

struct _output {
    struct _output   *next;
    
    changes_t	    changes;
    
    output_prop_t   *props;

    name_t	    output;
    XRROutputInfo   *output_info;
    
    name_t	    crtc;
    crtc_t	    *crtc_info;
    crtc_t	    *current_crtc_info;
    
    name_t	    mode;
    double	    refresh;
    XRRModeInfo	    *mode_info;
    
    name_t	    addmode;

    relation_t	    relation;
    char	    *relative_to;

    int		    x, y;
    Rotation	    rotation;

    XRRPanning      panning;

    Bool    	    automatic;
    int     	    scale_from_w, scale_from_h;
    transform_t	    transform;

    struct {
	float red;
	float green;
	float blue;
    } gamma;

    float	    brightness;

    Bool	    primary;

    Bool	    found;
};

typedef enum _umode_action {
    umode_create, umode_destroy, umode_add, umode_delete
} umode_action_t;


struct _umode {
    struct _umode   *next;
    
    umode_action_t  action;
    XRRModeInfo	    mode;
    name_t	    output;
    name_t	    name;
};

static const char *connection[3] = {
    "connected",
    "disconnected",
    "unknown connection"};

#define OUTPUT_NAME 1

#define CRTC_OFF    2
#define CRTC_UNSET  3
#define CRTC_INDEX  0x40000000

#define MODE_NAME   1
#define MODE_OFF    2
#define MODE_UNSET  3
#define MODE_PREF   4

#define POS_UNSET   -1

static output_t	*outputs = NULL;
static output_t	**outputs_tail = &outputs;
static crtc_t	*crtcs;
static umode_t	*umodes;
static int	num_crtcs;
static XRRScreenResources  *res;
static int	fb_width = 0, fb_height = 0;
static int	fb_width_mm = 0, fb_height_mm = 0;
static double	dpi = 0;
static char	*dpi_output = NULL;
static Bool	dryrun = False;
static int	minWidth, maxWidth, minHeight, maxHeight;
static Bool    	has_1_2 = False;
static Bool    	has_1_3 = False;
static int      provider_xid, output_source_provider_xid, offload_sink_provider_xid;

static int
mode_height (XRRModeInfo *mode_info, Rotation rotation)
{
    switch (rotation & 0xf) {
    case RR_Rotate_0:
    case RR_Rotate_180:
	return mode_info->height;
    case RR_Rotate_90:
    case RR_Rotate_270:
	return mode_info->width;
    default:
	return 0;
    }
}

static int
mode_width (XRRModeInfo *mode_info, Rotation rotation)
{
    switch (rotation & 0xf) {
    case RR_Rotate_0:
    case RR_Rotate_180:
	return mode_info->width;
    case RR_Rotate_90:
    case RR_Rotate_270:
	return mode_info->height;
    default:
	return 0;
    }
}

static Bool
transform_point (XTransform *transform, double *xp, double *yp)
{
    double  vector[3];
    double  result[3];
    int	    i, j;
    double  v;

    vector[0] = *xp;
    vector[1] = *yp;
    vector[2] = 1;
    for (j = 0; j < 3; j++)
    {
	v = 0;
	for (i = 0; i < 3; i++)
	    v += (XFixedToDouble (transform->matrix[j][i]) * vector[i]);
	result[j] = v;
    }
    if (!result[2])
	return False;
    for (j = 0; j < 2; j++) {
	vector[j] = result[j] / result[2];
	if (vector[j] > 32767 || vector[j] < -32767)
	    return False;
    }
    *xp = vector[0];
    *yp = vector[1];
    return True;
}

static void
path_bounds (XTransform *transform, point_t *points, int npoints, box_t *box)
{
    int	    i;
    box_t   point;

    for (i = 0; i < npoints; i++) {
	double	x, y;
	x = points[i].x;
	y = points[i].y;
	transform_point (transform, &x, &y);
	point.x1 = floor (x);
	point.y1 = floor (y);
	point.x2 = ceil (x);
	point.y2 = ceil (y);
	if (i == 0)
	    *box = point;
	else {
	    if (point.x1 < box->x1) box->x1 = point.x1;
	    if (point.y1 < box->y1) box->y1 = point.y1;
	    if (point.x2 > box->x2) box->x2 = point.x2;
	    if (point.y2 > box->y2) box->y2 = point.y2;
	}
    }
}

static void
mode_geometry (XRRModeInfo *mode_info, Rotation rotation,
	       XTransform *transform,
	       box_t *bounds)
{
    point_t rect[4];
    int	width = mode_width (mode_info, rotation);
    int height = mode_height (mode_info, rotation);

    rect[0].x = 0;
    rect[0].y = 0;
    rect[1].x = width;
    rect[1].y = 0;
    rect[2].x = width;
    rect[2].y = height;
    rect[3].x = 0;
    rect[3].y = height;
    path_bounds (transform, rect, 4, bounds);
}

/* v refresh frequency in Hz */
static double
mode_refresh (XRRModeInfo *mode_info)
{
    double rate;
    
    if (mode_info->hTotal && mode_info->vTotal)
	rate = ((double) mode_info->dotClock /
		((double) mode_info->hTotal * (double) mode_info->vTotal));
    else
    	rate = 0;
    return rate;
}

/* h sync frequency in Hz */
static double
mode_hsync (XRRModeInfo *mode_info)
{
    double rate;
    
    if (mode_info->hTotal)
	rate = (double) mode_info->dotClock / (double) mode_info->hTotal;
    else
    	rate = 0;
    return rate;
}

static void
init_name (name_t *name)
{
    name->kind = name_none;
}

static void
set_name_string (name_t *name, char *string)
{
    name->kind |= name_string;
    name->string = string;
}

static void
set_name_xid (name_t *name, XID xid)
{
    name->kind |= name_xid;
    name->xid = xid;
}

static void
set_name_index (name_t *name, int index)
{
    name->kind |= name_index;
    name->index = index;
}

static void
set_name_preferred (name_t *name)
{
    name->kind |= name_preferred;
}

static void
set_name_all (name_t *name, name_t *old)
{
    if (old->kind & name_xid)
	name->xid = old->xid;
    if (old->kind & name_string)
	name->string = old->string;
    if (old->kind & name_index)
	name->index = old->index;
    name->kind |= old->kind;
}

static void
set_name (name_t *name, char *string, name_kind_t valid)
{
    unsigned int xid; /* don't make it XID (which is unsigned long):
			 scanf() takes unsigned int */
    int index;

    if ((valid & name_xid) && sscanf (string, "0x%x", &xid) == 1)
	set_name_xid (name, xid);
    else if ((valid & name_index) && sscanf (string, "%d", &index) == 1)
	set_name_index (name, index);
    else if (valid & name_string)
	set_name_string (name, string);
    else
	usage ();
}

static void
init_transform (transform_t *transform)
{
    int x;
    memset (&transform->transform, '\0', sizeof (transform->transform));
    for (x = 0; x < 3; x++)
	transform->transform.matrix[x][x] = XDoubleToFixed (1.0);
    transform->filter = "";
    transform->nparams = 0;
    transform->params = NULL;
}

static void
set_transform (transform_t  *dest,
	       XTransform   *transform,
	       const char   *filter,
	       XFixed	    *params,
	       int	    nparams)
{
    dest->transform = *transform;
    /* note: this string is leaked */
    dest->filter = strdup (filter);
    dest->nparams = nparams;
    dest->params = malloc (nparams * sizeof (XFixed));
    memcpy (dest->params, params, nparams * sizeof (XFixed));
}

static void
copy_transform (transform_t *dest, transform_t *src)
{
    set_transform (dest, &src->transform,
		   src->filter, src->params, src->nparams);
}

static Bool
equal_transform (transform_t *a, transform_t *b)
{
    if (memcmp (&a->transform, &b->transform, sizeof (XTransform)) != 0)
	return False;
    if (strcmp (a->filter, b->filter) != 0)
	return False;
    if (a->nparams != b->nparams)
	return False;
    if (memcmp (a->params, b->params, a->nparams * sizeof (XFixed)) != 0)
	return False;
    return True;
}

static output_t *
add_output (void)
{
    output_t *output = calloc (1, sizeof (output_t));

    if (!output)
	fatal ("out of memory\n");
    output->next = NULL;
    output->found = False;
    output->brightness = 1.0;
    *outputs_tail = output;
    outputs_tail = &output->next;
    return output;
}

static output_t *
find_output (name_t *name)
{
    output_t *output;

    for (output = outputs; output; output = output->next)
    {
	name_kind_t common = name->kind & output->output.kind;
	
	if ((common & name_xid) && name->xid == output->output.xid)
	    break;
	if ((common & name_string) && !strcmp (name->string, output->output.string))
	    break;
	if ((common & name_index) && name->index == output->output.index)
	    break;
    }
    return output;
}

static output_t *
find_output_by_xid (RROutput output)
{
    name_t  output_name;

    init_name (&output_name);
    set_name_xid (&output_name, output);
    return find_output (&output_name);
}

static output_t *
find_output_by_name (char *name)
{
    name_t  output_name;

    init_name (&output_name);
    set_name_string (&output_name, name);
    return find_output (&output_name);
}

static crtc_t *
find_crtc (name_t *name)
{
    int	    c;
    crtc_t  *crtc = NULL;

    for (c = 0; c < num_crtcs; c++)
    {
	name_kind_t common;
	
	crtc = &crtcs[c];
	common = name->kind & crtc->crtc.kind;
	
	if ((common & name_xid) && name->xid == crtc->crtc.xid)
	    break;
	if ((common & name_string) && !strcmp (name->string, crtc->crtc.string))
	    break;
	if ((common & name_index) && name->index == crtc->crtc.index)
	    break;
	crtc = NULL;
    }
    return crtc;
}

static crtc_t *
find_crtc_by_xid (RRCrtc crtc)
{
    name_t  crtc_name;

    init_name (&crtc_name);
    set_name_xid (&crtc_name, crtc);
    return find_crtc (&crtc_name);
}

static XRRModeInfo *
find_mode (name_t *name, double refresh)
{
    int		m;
    XRRModeInfo	*best = NULL;
    double	bestDist = 0;

    for (m = 0; m < res->nmode; m++)
    {
	XRRModeInfo *mode = &res->modes[m];
	if ((name->kind & name_xid) && name->xid == mode->id)
	{
	    best = mode;
	    break;
	}
	if ((name->kind & name_string) && !strcmp (name->string, mode->name))
	{
	    double   dist;
	    
	    if (refresh)
		dist = fabs (mode_refresh (mode) - refresh);
	    else
		dist = 0;
	    if (!best || dist < bestDist)
	    {
		bestDist = dist;
		best = mode;
	    }
	}
    }
    return best;
}

static XRRModeInfo *
find_mode_by_xid (RRMode mode)
{
    name_t  mode_name;

    init_name (&mode_name);
    set_name_xid (&mode_name, mode);
    return find_mode (&mode_name, 0);
}

static
XRRModeInfo *
find_mode_for_output (output_t *output, name_t *name)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;
    XRRModeInfo	    *best = NULL;
    double	    bestDist = 0;

    for (m = 0; m < output_info->nmode; m++)
    {
	XRRModeInfo	    *mode;

	mode = find_mode_by_xid (output_info->modes[m]);
	if (!mode) continue;
	if ((name->kind & name_xid) && name->xid == mode->id)
	{
	    best = mode;
	    break;
	}
	if ((name->kind & name_string) && !strcmp (name->string, mode->name))
	{
	    double   dist;

	    /* Stay away from doublescan modes unless refresh rate is specified. */
	    if (!output->refresh && (mode->modeFlags & RR_DoubleScan))
		continue;

	    if (output->refresh)
		dist = fabs (mode_refresh (mode) - output->refresh);
	    else
		dist = 0;
	    if (!best || dist < bestDist)
	    {
		bestDist = dist;
		best = mode;
	    }
	}
    }
    return best;
}

static XRRModeInfo *
preferred_mode (output_t *output)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;
    XRRModeInfo	    *best;
    int		    bestDist;
    
    best = NULL;
    bestDist = 0;
    for (m = 0; m < output_info->nmode; m++)
    {
	XRRModeInfo *mode_info = find_mode_by_xid (output_info->modes[m]);
	int	    dist;
	
	if (m < output_info->npreferred)
	    dist = 0;
	else if (output_info->mm_height)
	    dist = (1000 * DisplayHeight(dpy, screen) / DisplayHeightMM(dpy, screen) -
		    1000 * mode_info->height / output_info->mm_height);
	else
	    dist = DisplayHeight(dpy, screen) - mode_info->height;

        if (dist < 0) dist = -dist;
	if (!best || dist < bestDist)
	{
	    best = mode_info;
	    bestDist = dist;
	}
    }
    return best;
}

static Bool
output_can_use_crtc (output_t *output, crtc_t *crtc)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    c;

    for (c = 0; c < output_info->ncrtc; c++)
	if (output_info->crtcs[c] == crtc->crtc.xid)
	    return True;
    return False;
}

static Bool
output_can_use_mode (output_t *output, XRRModeInfo *mode)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;

    for (m = 0; m < output_info->nmode; m++)
	if (output_info->modes[m] == mode->id)
	    return True;
    return False;
}

static Bool
crtc_can_use_rotation (crtc_t *crtc, Rotation rotation)
{
    Rotation	rotations = crtc->crtc_info->rotations;
    Rotation	dir = rotation & (RR_Rotate_0|RR_Rotate_90|RR_Rotate_180|RR_Rotate_270);
    Rotation	reflect = rotation & (RR_Reflect_X|RR_Reflect_Y);
    if (((rotations & dir) != 0) && ((rotations & reflect) == reflect))
	return True;
    return False;
}

/*
 * Report only rotations that are supported by all crtcs
 */
static Rotation
output_rotations (output_t *output)
{
    Bool	    found = False;
    Rotation	    rotation = RR_Rotate_0;
    XRROutputInfo   *output_info = output->output_info;
    int		    c;
    
    for (c = 0; c < output_info->ncrtc; c++)
    {
	crtc_t	*crtc = find_crtc_by_xid (output_info->crtcs[c]);
	if (crtc)
	{
	    if (!found) {
		rotation = crtc->crtc_info->rotations;
		found = True;
	    } else
		rotation &= crtc->crtc_info->rotations;
	}
    }
    return rotation;
}

static Bool
output_can_use_rotation (output_t *output, Rotation rotation)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    c;

    /* make sure all of the crtcs can use this rotation.
     * yes, this is not strictly necessary, but it is 
     * simpler,and we expect most drivers to either
     * support rotation everywhere or nowhere
     */
    for (c = 0; c < output_info->ncrtc; c++)
    {
	crtc_t	*crtc = find_crtc_by_xid (output_info->crtcs[c]);
	if (crtc && !crtc_can_use_rotation (crtc, rotation))
	    return False;
    }
    return True;
}

static Bool
output_is_primary(output_t *output)
{
    if (has_1_3)
	    return XRRGetOutputPrimary(dpy, root) == output->output.xid;
    return False;
}

/* Returns the index of the last value in an array < 0xffff */
static int
find_last_non_clamped(CARD16 array[], int size) {
    int i;
    for (i = size - 1; i > 0; i--) {
        if (array[i] < 0xffff)
	    return i;
    }
    return 0;
}

static void
set_gamma_info(output_t *output)
{
    XRRCrtcGamma *gamma;
    double i1, v1, i2, v2;
    int size, middle, last_best, last_red, last_green, last_blue;
    CARD16 *best_array;

    if (!output->crtc_info)
	return;

    size = XRRGetCrtcGammaSize(dpy, output->crtc_info->crtc.xid);
    if (!size) {
	warning("Failed to get size of gamma for output %s\n", output->output.string);
	return;
    }

    gamma = XRRGetCrtcGamma(dpy, output->crtc_info->crtc.xid);
    if (!gamma) {
	warning("Failed to get gamma for output %s\n", output->output.string);
	return;
    }

    /*
     * Here is a bit tricky because gamma is a whole curve for each
     * color.  So, typically, we need to represent 3 * 256 values as 3 + 1
     * values.  Therefore, we approximate the gamma curve (v) by supposing
     * it always follows the way we set it: a power function (i^g)
     * multiplied by a brightness (b).
     * v = i^g * b
     * so g = (ln(v) - ln(b))/ln(i)
     * and b can be found using two points (v1,i1) and (v2, i2):
     * b = e^((ln(v2)*ln(i1) - ln(v1)*ln(i2))/ln(i1/i2))
     * For the best resolution, we select i2 at the highest place not
     * clamped and i1 at i2/2. Note that if i2 = 1 (as in most normal
     * cases), then b = v2.
     */
    last_red = find_last_non_clamped(gamma->red, size);
    last_green = find_last_non_clamped(gamma->green, size);
    last_blue = find_last_non_clamped(gamma->blue, size);
    best_array = gamma->red;
    last_best = last_red;
    if (last_green > last_best) {
	last_best = last_green;
	best_array = gamma->green;
    }
    if (last_blue > last_best) {
	last_best = last_blue;
	best_array = gamma->blue;
    }
    if (last_best == 0)
	last_best = 1;

    middle = last_best / 2;
    i1 = (double)(middle + 1) / size;
    v1 = (double)(best_array[middle]) / 65535;
    i2 = (double)(last_best + 1) / size;
    v2 = (double)(best_array[last_best]) / 65535;
    if (v2 < 0.0001) { /* The screen is black */
	output->brightness = 0;
	output->gamma.red = 1;
	output->gamma.green = 1;
	output->gamma.blue = 1;
    } else {
	if ((last_best + 1) == size)
	    output->brightness = v2;
	else
	    output->brightness = exp((log(v2)*log(i1) - log(v1)*log(i2))/log(i1/i2));
	output->gamma.red = log((double)(gamma->red[last_red / 2]) / output->brightness
				/ 65535) / log((double)((last_red / 2) + 1) / size);
	output->gamma.green = log((double)(gamma->green[last_green / 2]) / output->brightness
				  / 65535) / log((double)((last_green / 2) + 1) / size);
	output->gamma.blue = log((double)(gamma->blue[last_blue / 2]) / output->brightness
				 / 65535) / log((double)((last_blue / 2) + 1) / size);
    }

    XRRFreeGamma(gamma);
}

static void
set_output_info (output_t *output, RROutput xid, XRROutputInfo *output_info)
{
    /* sanity check output info */
    if (output_info->connection != RR_Disconnected && !output_info->nmode)
	warning ("Output %s is not disconnected but has no modes\n",
		 output_info->name);
    
    /* set output name and info */
    if (!(output->output.kind & name_xid))
	set_name_xid (&output->output, xid);
    if (!(output->output.kind & name_string))
	set_name_string (&output->output, output_info->name);
    output->output_info = output_info;
    
    /* set crtc name and info */
    if (!(output->changes & changes_crtc))
	set_name_xid (&output->crtc, output_info->crtc);
    
    if (output->crtc.kind == name_xid && output->crtc.xid == None)
	output->crtc_info = NULL;
    else
    {
	output->crtc_info = find_crtc (&output->crtc);
	if (!output->crtc_info)
	{
	    if (output->crtc.kind & name_xid)
		fatal ("cannot find crtc 0x%x\n", output->crtc.xid);
	    if (output->crtc.kind & name_index)
		fatal ("cannot find crtc %d\n", output->crtc.index);
	}
	if (!output_can_use_crtc (output, output->crtc_info))
	    fatal ("output %s cannot use crtc 0x%x\n", output->output.string,
		   output->crtc_info->crtc.xid);
    }

    /* set mode name and info */
    if (!(output->changes & changes_mode))
    {
	crtc_t	*crtc = NULL;
	
	if (output_info->crtc)
	    crtc = find_crtc_by_xid(output_info->crtc);
	if (crtc && crtc->crtc_info)
	    set_name_xid (&output->mode, crtc->crtc_info->mode);
	else if (output->crtc_info)
	    set_name_xid (&output->mode, output->crtc_info->crtc_info->mode);
	else
	    set_name_xid (&output->mode, None);
	if (output->mode.xid)
	{
	    output->mode_info = find_mode_by_xid (output->mode.xid);
	    if (!output->mode_info)
		fatal ("server did not report mode 0x%x for output %s\n",
		       output->mode.xid, output->output.string);
	}
	else
	    output->mode_info = NULL;
    }
    else if (output->mode.kind == name_xid && output->mode.xid == None)
	output->mode_info = NULL;
    else
    {
	if (output->mode.kind == name_preferred)
	    output->mode_info = preferred_mode (output);
	else
	    output->mode_info = find_mode_for_output (output, &output->mode);
	if (!output->mode_info)
	{
	    if (output->mode.kind & name_preferred)
		fatal ("cannot find preferred mode\n");
	    if (output->mode.kind & name_string)
		fatal ("cannot find mode %s\n", output->mode.string);
	    if (output->mode.kind & name_xid)
		fatal ("cannot find mode 0x%x\n", output->mode.xid);
	}
	if (!output_can_use_mode (output, output->mode_info))
	    fatal ("output %s cannot use mode %s\n", output->output.string,
		   output->mode_info->name);
    }

    /* set position */
    if (!(output->changes & changes_position))
    {
	if (output->crtc_info)
	{
	    output->x = output->crtc_info->crtc_info->x;
	    output->y = output->crtc_info->crtc_info->y;
	}
	else
	{
	    output->x = 0;
	    output->y = 0;
	}
    }

    /* set rotation */
    if (!(output->changes & changes_rotation))
    {
	output->rotation &= ~0xf;
	if (output->crtc_info)
	    output->rotation |= (output->crtc_info->crtc_info->rotation & 0xf);
	else
	    output->rotation = RR_Rotate_0;
    }
    if (!(output->changes & changes_reflection))
    {
	output->rotation &= ~(RR_Reflect_X|RR_Reflect_Y);
	if (output->crtc_info)
	    output->rotation |= (output->crtc_info->crtc_info->rotation &
				 (RR_Reflect_X|RR_Reflect_Y));
    }
    if (!output_can_use_rotation (output, output->rotation))
	fatal ("output %s cannot use rotation \"%s\" reflection \"%s\"\n",
	       output->output.string,
	       rotation_name (output->rotation),
	       reflection_name (output->rotation));

    /* set gamma */
    if (!(output->changes & changes_gamma))
	    set_gamma_info(output);

    /* set transformation */
    if (!(output->changes & changes_transform))
    {
	if (output->crtc_info)
	    copy_transform (&output->transform, &output->crtc_info->current_transform);
	else
	    init_transform (&output->transform);
    } else {
	/* transform was already set for --scale or --transform */

	/* for --scale-from, figure out the mode size and compute the transform
	 * for the target framebuffer area */
	if (output->scale_from_w > 0 && output->mode_info) {
	    double sx = (double)output->scale_from_w /
				output->mode_info->width;
	    double sy = (double)output->scale_from_h /
				output->mode_info->height;
	    if (verbose)
		printf("scaling %s by %lfx%lf\n", output->output.string, sx,
		       sy);
	    init_transform (&output->transform);
	    output->transform.transform.matrix[0][0] = XDoubleToFixed (sx);
	    output->transform.transform.matrix[1][1] = XDoubleToFixed (sy);
	    output->transform.transform.matrix[2][2] = XDoubleToFixed (1.0);
	    if (sx != 1 || sy != 1)
		output->transform.filter = "bilinear";
	    else
		output->transform.filter = "nearest";
	    output->transform.nparams = 0;
	    output->transform.params = NULL;
	}
    }

    /* set primary */
    if (!(output->changes & changes_primary))
	output->primary = output_is_primary(output);
}
    
static void
get_screen (Bool current)
{
    XRRGetScreenSizeRange (dpy, root, &minWidth, &minHeight,
			   &maxWidth, &maxHeight);
    
    if (current)
	res = XRRGetScreenResourcesCurrent (dpy, root);
    else
	res = XRRGetScreenResources (dpy, root);
    if (!res) fatal ("could not get screen resources");
}

static void
get_crtcs (void)
{
    int		c;

    num_crtcs = res->ncrtc;
    crtcs = calloc (num_crtcs, sizeof (crtc_t));
    if (!crtcs) fatal ("out of memory\n");
    
    for (c = 0; c < res->ncrtc; c++)
    {
	XRRCrtcInfo *crtc_info = XRRGetCrtcInfo (dpy, res, res->crtcs[c]);
	XRRCrtcTransformAttributes  *attr;
	XRRPanning  *panning_info = NULL;

#if 1
	{
	    XRRPanning zero;
	    memset(&zero, 0, sizeof(zero));
	    panning_info = XRRGetPanning  (dpy, res, res->crtcs[c]);
	    zero.timestamp = panning_info->timestamp;
	    if (!memcmp(panning_info, &zero, sizeof(zero))) {
		Xfree(panning_info);
		panning_info = NULL;
	    }
	}
#endif

	set_name_xid (&crtcs[c].crtc, res->crtcs[c]);
	set_name_index (&crtcs[c].crtc, c);
	if (!crtc_info) fatal ("could not get crtc 0x%x information\n", res->crtcs[c]);
	crtcs[c].crtc_info = crtc_info;
	crtcs[c].panning_info = panning_info;
	if (crtc_info->mode == None)
	{
	    crtcs[c].mode_info = NULL;
	    crtcs[c].x = 0;
	    crtcs[c].y = 0;
	    crtcs[c].rotation = RR_Rotate_0;
	}
	if (XRRGetCrtcTransform (dpy, res->crtcs[c], &attr) && attr) {
	    set_transform (&crtcs[c].current_transform,
			   &attr->currentTransform,
			   attr->currentFilter,
			   attr->currentParams,
			   attr->currentNparams);
	    XFree (attr);
	}
	else
	{
	    init_transform (&crtcs[c].current_transform);
	}
	copy_transform (&crtcs[c].pending_transform, &crtcs[c].current_transform);
   }
}

static void
crtc_add_output (crtc_t *crtc, output_t *output)
{
    if (crtc->outputs)
	crtc->outputs = realloc (crtc->outputs, (crtc->noutput + 1) * sizeof (output_t *));
    else
    {
	crtc->outputs = malloc (sizeof (output_t *));
	crtc->x = output->x;
	crtc->y = output->y;
	crtc->rotation = output->rotation;
	crtc->mode_info = output->mode_info;
	copy_transform (&crtc->pending_transform, &output->transform);
   }
    if (!crtc->outputs) fatal ("out of memory\n");
    crtc->outputs[crtc->noutput++] = output;
}

static void
set_crtcs (void)
{
    output_t	*output;

    for (output = outputs; output; output = output->next)
    {
	if (!output->mode_info) continue;
	crtc_add_output (output->crtc_info, output);
    }
}

static void
set_panning (void)
{
    output_t	*output;

    for (output = outputs; output; output = output->next)
    {
	if (! output->crtc_info)
	    continue;
	if (! (output->changes & changes_panning))
	    continue;
	if (! output->crtc_info->panning_info)
	    output->crtc_info->panning_info = malloc (sizeof(XRRPanning));
	memcpy (output->crtc_info->panning_info, &output->panning, sizeof(XRRPanning));
	output->crtc_info->changing = 1;
    }
}

static void
set_gamma(void)
{
    output_t	*output;

    for (output = outputs; output; output = output->next) {
	int i, size, shift;
	crtc_t *crtc;
	XRRCrtcGamma *gamma;
	float gammaRed;
	float gammaGreen;
	float gammaBlue;

	if (!(output->changes & changes_gamma))
	    continue;

	if (!output->crtc_info) {
	    fatal("Need crtc to set gamma on.\n");
	    continue;
	}

	crtc = output->crtc_info;

	size = XRRGetCrtcGammaSize(dpy, crtc->crtc.xid);

	if (!size) {
	    fatal("Gamma size is 0.\n");
	    continue;
	}

	/*
	 * The gamma-correction lookup table managed through XRR[GS]etCrtcGamma
	 * is 2^n in size, where 'n' is the number of significant bits in
	 * the X Color.  Because an X Color is 16 bits, size cannot be larger
	 * than 2^16.
	 */
	if (size > 65536) {
	    fatal("Gamma correction table is impossibly large.\n");
	    continue;
	}

	/*
	 * The hardware color lookup table has a number of significant
	 * bits equal to ffs(size) - 1; compute all values so that
	 * they are in the range [0,size) then shift the values so
	 * that they occupy the MSBs of the 16-bit X Color.
	 */
	shift = 16 - (ffs(size) - 1);

	gamma = XRRAllocGamma(size);
	if (!gamma) {
	    fatal("Gamma allocation failed.\n");
	    continue;
	}

	if (output->gamma.red == 0.0)
	    output->gamma.red = 1.0;
	if (output->gamma.green == 0.0)
	    output->gamma.green = 1.0;
	if (output->gamma.blue == 0.0)
	    output->gamma.blue = 1.0;

	gammaRed = 1.0 / output->gamma.red;
	gammaGreen = 1.0 / output->gamma.green;
	gammaBlue = 1.0 / output->gamma.blue;

	for (i = 0; i < size; i++) {
	    if (gammaRed == 1.0 && output->brightness == 1.0)
		gamma->red[i] = i;
	    else
		gamma->red[i] = dmin(pow((double)i/(double)(size - 1),
					 gammaRed) * output->brightness,
				     1.0) * (double)(size - 1);
	    gamma->red[i] <<= shift;

	    if (gammaGreen == 1.0 && output->brightness == 1.0)
		gamma->green[i] = i;
	    else
		gamma->green[i] = dmin(pow((double)i/(double)(size - 1),
					   gammaGreen) * output->brightness,
				       1.0) * (double)(size - 1);
	    gamma->green[i] <<= shift;

	    if (gammaBlue == 1.0 && output->brightness == 1.0)
		gamma->blue[i] = i;
	    else
		gamma->blue[i] = dmin(pow((double)i/(double)(size - 1),
					  gammaBlue) * output->brightness,
				      1.0) * (double)(size - 1);
	    gamma->blue[i] <<= shift;
	}

	XRRSetCrtcGamma(dpy, crtc->crtc.xid, gamma);

	free(gamma);
    }
}

static void
set_primary(void)
{
    output_t *output;

    if (no_primary) {
	XRRSetOutputPrimary(dpy, root, None);
    } else {
	for (output = outputs; output; output = output->next) {
	    if (!(output->changes & changes_primary))
		continue;
	    if (output->primary)
		XRRSetOutputPrimary(dpy, root, output->output.xid);
	}
    }
}

static Status
crtc_disable (crtc_t *crtc)
{
    if (verbose)
    	printf ("crtc %d: disable\n", crtc->crtc.index);
	
    if (dryrun)
	return RRSetConfigSuccess;
    return XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			     0, 0, None, RR_Rotate_0, NULL, 0);
}

static void
crtc_set_transform (crtc_t *crtc, transform_t *transform)
{
    int	major, minor;

    XRRQueryVersion (dpy, &major, &minor);
    if (major > 1 || (major == 1 && minor >= 3))
	XRRSetCrtcTransform (dpy, crtc->crtc.xid,
			     &transform->transform,
			     transform->filter,
			     transform->params,
			     transform->nparams);
}

static Status
crtc_revert (crtc_t *crtc)
{
    XRRCrtcInfo	*crtc_info = crtc->crtc_info;
    
    if (verbose)
    	printf ("crtc %d: revert\n", crtc->crtc.index);
	
    if (dryrun)
	return RRSetConfigSuccess;

    if (!equal_transform (&crtc->current_transform, &crtc->pending_transform))
	crtc_set_transform (crtc, &crtc->current_transform);
    return XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			    crtc_info->x, crtc_info->y,
			    crtc_info->mode, crtc_info->rotation,
			    crtc_info->outputs, crtc_info->noutput);
}

static Status
crtc_apply (crtc_t *crtc)
{
    RROutput	*rr_outputs;
    int		o;
    Status	s;
    RRMode	mode = None;

    if (!crtc->changing || !crtc->mode_info)
	return RRSetConfigSuccess;

    rr_outputs = calloc (crtc->noutput, sizeof (RROutput));
    if (!rr_outputs)
	return BadAlloc;
    for (o = 0; o < crtc->noutput; o++)
	rr_outputs[o] = crtc->outputs[o]->output.xid;
    mode = crtc->mode_info->id;
    if (verbose) {
	printf ("crtc %d: %12s %6.1f +%d+%d", crtc->crtc.index,
		crtc->mode_info->name, mode_refresh (crtc->mode_info),
		crtc->x, crtc->y);
	for (o = 0; o < crtc->noutput; o++)
	    printf (" \"%s\"", crtc->outputs[o]->output.string);
	printf ("\n");
    }
    
    if (dryrun)
	s = RRSetConfigSuccess;
    else
    {
	if (!equal_transform (&crtc->current_transform, &crtc->pending_transform))
	    crtc_set_transform (crtc, &crtc->pending_transform);
	s = XRRSetCrtcConfig (dpy, res, crtc->crtc.xid, CurrentTime,
			      crtc->x, crtc->y, mode, crtc->rotation,
			      rr_outputs, crtc->noutput);
	if (s == RRSetConfigSuccess && crtc->panning_info) {
	    if (has_1_3)
		s = XRRSetPanning (dpy, res, crtc->crtc.xid, crtc->panning_info);
	    else
		fatal ("panning needs RandR 1.3\n");
	}
    }
    free (rr_outputs);
    return s;
}

static void
screen_revert (void)
{
    if (verbose)
	printf ("screen %d: revert\n", screen);

    if (dryrun)
	return;
    XRRSetScreenSize (dpy, root,
		      DisplayWidth (dpy, screen),
		      DisplayHeight (dpy, screen),
		      DisplayWidthMM (dpy, screen),
		      DisplayHeightMM (dpy, screen));
}

static void
screen_apply (void)
{
    if (fb_width == DisplayWidth (dpy, screen) &&
	fb_height == DisplayHeight (dpy, screen) &&
	fb_width_mm == DisplayWidthMM (dpy, screen) &&
	fb_height_mm == DisplayHeightMM (dpy, screen))
    {
	return;
    }
    if (verbose)
	printf ("screen %d: %dx%d %dx%d mm %6.2fdpi\n", screen,
		fb_width, fb_height, fb_width_mm, fb_height_mm, dpi);
    if (dryrun)
	return;
    XRRSetScreenSize (dpy, root, fb_width, fb_height,
		      fb_width_mm, fb_height_mm);
}

static void
revert (void)
{
    int	c;

    /* first disable all crtcs */
    for (c = 0; c < res->ncrtc; c++)
	crtc_disable (&crtcs[c]);
    /* next reset screen size */
    screen_revert ();
    /* now restore all crtcs */
    for (c = 0; c < res->ncrtc; c++)
	crtc_revert (&crtcs[c]);
}

/*
 * uh-oh, something bad happened in the middle of changing
 * the configuration. Revert to the previous configuration
 * and bail
 */
static void _X_NORETURN
panic (Status s, crtc_t *crtc)
{
    int	    c = crtc->crtc.index;
    const char *message;
    
    switch (s) {
    case RRSetConfigSuccess:		message = "succeeded";		    break;
    case BadAlloc:			message = "out of memory";	    break;
    case RRSetConfigFailed:		message = "failed";		    break;
    case RRSetConfigInvalidConfigTime:	message = "invalid config time";    break;
    case RRSetConfigInvalidTime:	message = "invalid time";	    break;
    default:				message = "unknown failure";	    break;
    }
    
    fprintf (stderr, "%s: Configure crtc %d %s\n", program_name, c, message);
    revert ();
    exit (1);
}

static void
apply (void)
{
    Status  s;
    int	    c;
    
    /*
     * Hold the server grabbed while messing with
     * the screen so that apps which notice the resize
     * event and ask for xinerama information from the server
     * receive up-to-date information
     */
    if (grab_server)
	XGrabServer (dpy);
    
    /*
     * Turn off any crtcs which are to be disabled or which are
     * larger than the target size
     */
    for (c = 0; c < res->ncrtc; c++)
    {
	crtc_t	    *crtc = &crtcs[c];
	XRRCrtcInfo *crtc_info = crtc->crtc_info;

	/* if this crtc is already disabled, skip it */
	if (crtc_info->mode == None) 
	    continue;
	
	/* 
	 * If this crtc is to be left enabled, make
	 * sure the old size fits then new screen
	 */
	if (crtc->mode_info) 
	{
	    XRRModeInfo	*old_mode = find_mode_by_xid (crtc_info->mode);
	    int x, y, w, h;
	    box_t bounds;

	    if (!old_mode) 
		panic (RRSetConfigFailed, crtc);
	    
	    /* old position and size information */
	    mode_geometry (old_mode, crtc_info->rotation,
			   &crtc->current_transform.transform,
			   &bounds);

	    x = crtc_info->x + bounds.x1;
	    y = crtc_info->y + bounds.y1;
	    w = bounds.x2 - bounds.x1;
	    h = bounds.y2 - bounds.y1;

	    /* if it fits, skip it */
	    if (x + w <= fb_width && y + h <= fb_height) 
		continue;
	    crtc->changing = True;
	}
	s = crtc_disable (crtc);
	if (s != RRSetConfigSuccess)
	    panic (s, crtc);
    }

    /*
     * Set the screen size
     */
    screen_apply ();
    
    /*
     * Set crtcs
     */

    for (c = 0; c < res->ncrtc; c++)
    {
	crtc_t	*crtc = &crtcs[c];
	
	s = crtc_apply (crtc);
	if (s != RRSetConfigSuccess)
	    panic (s, crtc);
    }

    set_primary ();

    /*
     * Release the server grab and let all clients
     * respond to the updated state
     */
    if (grab_server)
	XUngrabServer (dpy);
}

/*
 * Use current output state to complete the output list
 */
static void
get_outputs (void)
{
    int		o;
    output_t    *q;
    
    for (o = 0; o < res->noutput; o++)
    {
	XRROutputInfo	*output_info = XRRGetOutputInfo (dpy, res, res->outputs[o]);
	output_t	*output;
	name_t		output_name;
	if (!output_info) fatal ("could not get output 0x%x information\n", res->outputs[o]);
	set_name_xid (&output_name, res->outputs[o]);
	set_name_index (&output_name, o);
	set_name_string (&output_name, output_info->name);
	output = find_output (&output_name);
	if (!output)
	{
	    output = add_output ();
	    set_name_all (&output->output, &output_name);
	    /*
	     * When global --automatic mode is set, turn on connected but off
	     * outputs, turn off disconnected but on outputs
	     */
	    if (automatic)
	    {
		switch (output_info->connection) {
		case RR_Connected:
		    if (!output_info->crtc) {
			output->changes |= changes_automatic;
			output->automatic = True;
		    }
		    break;
		case RR_Disconnected:
		    if (output_info->crtc)
		    {
			output->changes |= changes_automatic;
			output->automatic = True;
		    }
		    break;
		}
	    }
	}
	output->found = True;

	/*
	 * Automatic mode -- track connection state and enable/disable outputs
	 * as necessary
	 */
	if (output->automatic)
	{
	    switch (output_info->connection) {
	    case RR_Connected:
	    case RR_UnknownConnection:
		if ((!(output->changes & changes_mode)))
		{
		    set_name_preferred (&output->mode);
		    output->changes |= changes_mode;
		}
		break;
	    case RR_Disconnected:
		if ((!(output->changes & changes_mode)))
		{
		    set_name_xid (&output->mode, None);
		    set_name_xid (&output->crtc, None);
		    output->changes |= changes_mode;
		    output->changes |= changes_crtc;
		}
		break;
	    }
	}

	set_output_info (output, res->outputs[o], output_info);
    }
    for (q = outputs; q; q = q->next)
    {
	if (!q->found)
	{
	    fprintf(stderr, "warning: output %s not found; ignoring\n",
		    q->output.string);
	}
    }
}

static void
mark_changing_crtcs (void)
{
    int	c;

    for (c = 0; c < num_crtcs; c++)
    {
	crtc_t	    *crtc = &crtcs[c];
	int	    o;
	output_t    *output;

	/* walk old output list (to catch disables) */
	for (o = 0; o < crtc->crtc_info->noutput; o++)
	{
	    output = find_output_by_xid (crtc->crtc_info->outputs[o]);
	    if (!output) fatal ("cannot find output 0x%x\n",
				crtc->crtc_info->outputs[o]);
	    if (output->changes)
		crtc->changing = True;
	}
	/* walk new output list */
	for (o = 0; o < crtc->noutput; o++)
	{
	    output = crtc->outputs[o];
	    if (output->changes)
		crtc->changing = True;
	}
    }
}

/*
 * Test whether 'crtc' can be used for 'output'
 */
static Bool
check_crtc_for_output (crtc_t *crtc, output_t *output)
{
    int		c;
    int		l;
    output_t    *other;
    
    for (c = 0; c < output->output_info->ncrtc; c++)
	if (output->output_info->crtcs[c] == crtc->crtc.xid)
	    break;
    if (c == output->output_info->ncrtc)
	return False;
    for (other = outputs; other; other = other->next)
    {
	if (other == output)
	    continue;

	if (other->mode_info == NULL)
	    continue;

	if (other->crtc_info != crtc)
	    continue;

	/* see if the output connected to the crtc can clone to this output */
	for (l = 0; l < output->output_info->nclone; l++)
	    if (output->output_info->clones[l] == other->output.xid)
		break;
	/* not on the list, can't clone */
	if (l == output->output_info->nclone) 
	    return False;
    }

    if (crtc->noutput)
    {
	/* make sure the state matches */
	if (crtc->mode_info != output->mode_info)
	    return False;
	if (crtc->x != output->x)
	    return False;
	if (crtc->y != output->y)
	    return False;
	if (crtc->rotation != output->rotation)
	    return False;
	if (!equal_transform (&crtc->current_transform, &output->transform))
	    return False;
    }
    return True;
}

static crtc_t *
find_crtc_for_output (output_t *output)
{
    int	    c;

    for (c = 0; c < output->output_info->ncrtc; c++)
    {
	crtc_t	    *crtc;

	crtc = find_crtc_by_xid (output->output_info->crtcs[c]);
	if (!crtc) fatal ("cannot find crtc 0x%x\n", output->output_info->crtcs[c]);

	if (check_crtc_for_output (crtc, output))
	    return crtc;
    }
    return NULL;
}

static void
disable_outputs (output_t *outputs)
{
    while (outputs)
    {
	outputs->crtc_info = NULL;
	outputs = outputs->next;
    }
}

static void
print_output_property_value(Bool is_edid,
                            int value_format, /* 8, 16, 32 */
                            Atom value_type,  /* XA_{ATOM,INTEGER,CARDINAL} */
                            const void *value_bytes)
{
    /* special-case the EDID */
    if (is_edid && value_format == 8)
    {
	const uint8_t *val = value_bytes;
	printf ("%02" PRIx8, *val);
	return;
    }

    if (value_type == XA_ATOM && value_format == 32)
    {
	const Atom *val = value_bytes;
	char *str = XGetAtomName (dpy, *val);
	if (str != NULL)
	{
	    printf ("%s", str);
	    XFree (str);
	    return;
	}
    }

    if (value_type == XA_INTEGER)
    {
	if (value_format == 8)
	{
	    const int8_t *val = value_bytes;
	    printf ("%" PRId8, *val);
	    return;
	}
	if (value_format == 16)
	{
	    const int16_t *val = value_bytes;
	    printf ("%" PRId16, *val);
	    return;
	}
	if (value_format == 32)
	{
	    const int32_t *val = value_bytes;
	    printf ("%" PRId32, *val);
	    return;
	}
    }

    if (value_type == XA_CARDINAL)
    {
	if (value_format == 8)
	{
	    const uint8_t *val = value_bytes;
	    printf ("%" PRIu8, *val);
	    return;
	}
	if (value_format == 16)
	{
	    const uint16_t *val = value_bytes;
	    printf ("%" PRIu16, *val);
	    return;
	}
	if (value_format == 32)
	{
	    const uint32_t *val = value_bytes;
	    printf ("%" PRIu32, *val);
	    return;
	}
    }

    printf ("?");
}



int
main (int argc, char **argv)
{
    XRRScreenSize *sizes;
    XRRScreenConfiguration *sc;
    int		nsize;
    int		nrate;
    int                query = False;
    short		*rates;
    char          *display_name = NULL;
    int 		i;
    Bool    	version = False;
    int		event_base, error_base;
    int		ret = 0;
    output_t	*output = NULL;
    int		major, minor;
    Bool	current = False;

    program_name = argv[0];
    query = True;

    dpy = XOpenDisplay (display_name);

    if (dpy == NULL) {
	fprintf (stderr, "Can't open display %s\n", XDisplayName(display_name));
	exit (1);
    }
    if (screen < 0)
	screen = DefaultScreen (dpy);
    if (screen >= ScreenCount (dpy)) {
	fprintf (stderr, "Invalid screen number %d (display has %d)\n",
		 screen, ScreenCount (dpy));
	exit (1);
    }

    root = RootWindow (dpy, screen);

    if (!XRRQueryExtension (dpy, &event_base, &error_base) ||
        !XRRQueryVersion (dpy, &major, &minor))
    {
	fprintf (stderr, "RandR extension missing\n");
	exit (1);
    }
	
    int	    m; 
#define ModeShown   0x80000000

    get_screen (current);
    get_crtcs ();
    get_outputs ();

    printf ("Screen %d: minimum %d x %d, current %d x %d, maximum %d x %d\n",
		    screen, minWidth, minHeight,
		    DisplayWidth (dpy, screen), DisplayHeight(dpy, screen),
		    maxWidth, maxHeight);

    for (output = outputs; output; output = output->next)
    {
	    XRROutputInfo   *output_info = output->output_info;
	    crtc_t	    *crtc = output->crtc_info;
	    XRRCrtcInfo	    *crtc_info = crtc ? crtc->crtc_info : NULL;
	    XRRModeInfo	    *mode = output->mode_info;
	    Atom	    *props;
	    int		    j, nprop;
	    Bool	    *mode_shown;
	    Rotation	    rotations = output_rotations (output);

	    printf ("%s %s", output_info->name, connection[output_info->connection]);
	    if (mode)
	    {
		    if (crtc_info) {
			    printf (" %dx%d+%d+%d",
					    crtc_info->width, crtc_info->height,
					    crtc_info->x, crtc_info->y);
		    } else {
			    printf (" %dx%d+%d+%d",
					    mode->width, mode->height, output->x, output->y);
		    }
		    if (verbose)
			    printf (" (0x%x)", (int)mode->id);
		    if (output->rotation != RR_Rotate_0 || verbose)
		    {
			    printf (" %s", 
					    rotation_name (output->rotation));
			    if (output->rotation & (RR_Reflect_X|RR_Reflect_Y))
				    printf (" %s", reflection_name (output->rotation));
		    }
	    }
	    if (rotations != RR_Rotate_0 || verbose)
	    {
		    Bool    first = True;
		    printf (" (");
		    for (i = 0; i < 4; i ++) {
			    if ((rotations >> i) & 1) {
				    if (!first) printf (" "); first = False;
				    printf("%s", direction[i]);
			    }
		    }
		    if (rotations & RR_Reflect_X)
		    {
			    if (!first) printf (" "); first = False;
			    printf ("x axis");
		    }
		    if (rotations & RR_Reflect_Y)
		    {
			    if (!first) printf (" ");
			    printf ("y axis");
		    }
		    printf (")");
	    }

	    if (mode)
	    {
		    printf (" %dmm x %dmm",
				    (int)output_info->mm_width, (int)output_info->mm_height);
	    }

	    if (crtc && crtc->panning_info && crtc->panning_info->width > 0)
	    {
		    XRRPanning *pan = crtc->panning_info;
		    printf (" panning %dx%d+%d+%d",
				    pan->width, pan->height, pan->left, pan->top);
		    if ((pan->track_width    != 0 &&
					    (pan->track_left    != pan->left		||
					     pan->track_width   != pan->width		||
					     pan->border_left   != 0			||
					     pan->border_right  != 0))			||
				    (pan->track_height   != 0 &&
				     (pan->track_top     != pan->top		||
				      pan->track_height  != pan->height		||
				      pan->border_top    != 0			||
				      pan->border_bottom != 0)))
			    printf (" tracking %dx%d+%d+%d border %d/%d/%d/%d",
					    pan->track_width,  pan->track_height,
					    pan->track_left,   pan->track_top,
					    pan->border_left,  pan->border_top,
					    pan->border_right, pan->border_bottom);
	    }
	    printf ("\n");

	    if (verbose)
	    {
		    printf ("\tIdentifier: 0x%x\n", (int)output->output.xid);
		    printf ("\tTimestamp:  %d\n", (int)output_info->timestamp);
		    printf ("\tSubpixel:   %s\n", order[output_info->subpixel_order]);
		    if (output->gamma.red != 0.0 && output->gamma.green != 0.0 && output->gamma.blue != 0.0) {
			    printf ("\tGamma:      %#.2g:%#.2g:%#.2g\n",
					    output->gamma.red, output->gamma.green, output->gamma.blue);
			    printf ("\tBrightness: %#.2g\n", output->brightness);
		    }
		    printf ("\tClones:    ");
		    for (j = 0; j < output_info->nclone; j++)
		    {
			    output_t	*clone = find_output_by_xid (output_info->clones[j]);

			    if (clone) printf (" %s", clone->output.string);
		    }
		    printf ("\n");
		    if (output->crtc_info)
			    printf ("\tCRTC:       %d\n", output->crtc_info->crtc.index);
		    printf ("\tCRTCs:     ");
		    for (j = 0; j < output_info->ncrtc; j++)
		    {
			    crtc_t	*crtc = find_crtc_by_xid (output_info->crtcs[j]);
			    if (crtc)
				    printf (" %d", crtc->crtc.index);
		    }
		    printf ("\n");
		    if (output->crtc_info && output->crtc_info->panning_info) {
			    XRRPanning *pan = output->crtc_info->panning_info;
			    printf ("\tPanning:    %dx%d+%d+%d\n",
					    pan->width, pan->height, pan->left, pan->top);
			    printf ("\tTracking:   %dx%d+%d+%d\n",
					    pan->track_width,  pan->track_height,
					    pan->track_left,   pan->track_top);
			    printf ("\tBorder:     %d/%d/%d/%d\n",
					    pan->border_left,  pan->border_top,
					    pan->border_right, pan->border_bottom);
		    }
	    }
	    if (verbose)
	    {
		    int x, y;

		    printf ("\tTransform: ");
		    for (y = 0; y < 3; y++)
		    {
			    for (x = 0; x < 3; x++)
				    printf (" %f", XFixedToDouble (output->transform.transform.matrix[y][x]));
			    if (y < 2)
				    printf ("\n\t           ");
		    }
		    if (output->transform.filter)
			    printf ("\n\t           filter: %s", output->transform.filter);
		    printf ("\n");
	    }
	    if (verbose || properties)
	    {
		    props = XRRListOutputProperties (dpy, output->output.xid,
				    &nprop);
		    for (j = 0; j < nprop; j++) {
			    unsigned char *prop;
			    int actual_format;
			    unsigned long nitems, bytes_after;
			    Atom actual_type;
			    XRRPropertyInfo *propinfo;
			    char *atom_name = XGetAtomName (dpy, props[j]);
			    Bool is_edid = strcmp (atom_name, "EDID") == 0;
			    int k, bytes_per_item;

			    XRRGetOutputProperty (dpy, output->output.xid, props[j],
					    0, 100, False, False,
					    AnyPropertyType,
					    &actual_type, &actual_format,
					    &nitems, &bytes_after, &prop);

			    propinfo = XRRQueryOutputProperty(dpy, output->output.xid,
					    props[j]);

			    bytes_per_item = actual_format / 8;

			    printf ("\t%s: ", atom_name);

			    if (is_edid)
			    {
				    printf ("\n\t\t");
			    }

			    for (k = 0; k < nitems; k++)
			    {
				    if (k != 0)
				    {
					    if ((k % 16) == 0)
					    {
						    printf ("\n\t\t");
					    }
				    }
				    print_output_property_value (is_edid, actual_format,
						    actual_type,
						    prop + (k * bytes_per_item));
				    if (!is_edid)
				    {
					    printf (" ");
				    }
			    }
			    printf ("\n");

			    if (propinfo->range && propinfo->num_values > 0)
			    {
				    printf ("\t\trange%s: ",
						    (propinfo->num_values == 2) ? "" : "s");
				    for (k = 0; k < propinfo->num_values / 2; k++)
				    {
					    printf ("(");
					    print_output_property_value (False, 32, actual_type,
							    (unsigned char *) &(propinfo->values[k * 2]));
					    printf (", ");
					    print_output_property_value (False, 32, actual_type,
							    (unsigned char *) &(propinfo->values[k * 2 + 1]));
					    printf (")");
				    }
				    printf ("\n");
			    }
			    if (!propinfo->range && propinfo->num_values > 0)
			    {
				    printf ("\t\tsupported: ");
				    for (k = 0; k < propinfo->num_values; k++)
				    {
					    print_output_property_value (False, 32, actual_type,
							    (unsigned char *) &(propinfo->values[k]));
				    }
				    printf ("\n");
			    }

			    free(propinfo);
		    }
	    }

	    if (verbose)
	    {
		    for (j = 0; j < output_info->nmode; j++)
		    {
			    XRRModeInfo	*mode = find_mode_by_xid (output_info->modes[j]);
			    int		f;

			    printf ("  %s (0x%x) %6.1fMHz",
					    mode->name, (int)mode->id,
					    (double)mode->dotClock / 1000000.0);
			    for (f = 0; mode_flags[f].flag; f++)
				    if (mode->modeFlags & mode_flags[f].flag)
					    printf (" %s", mode_flags[f].string);
			    if (mode == output->mode_info)
				    printf (" *current");
			    if (j < output_info->npreferred)
				    printf (" +preferred");
			    printf ("\n");
			    printf ("        h: width  %4d start %4d end %4d total %4d skew %4d clock %6.1fKHz\n",
					    mode->width, mode->hSyncStart, mode->hSyncEnd,
					    mode->hTotal, mode->hSkew, mode_hsync (mode) / 1000);
			    printf ("        v: height %4d start %4d end %4d total %4d           clock %6.1fHz\n",
					    mode->height, mode->vSyncStart, mode->vSyncEnd, mode->vTotal,
					    mode_refresh (mode));
			    mode->modeFlags |= ModeShown;
		    }
	    }
	    else
	    {
		    mode_shown = calloc (output_info->nmode, sizeof (Bool));
		    if (!mode_shown) fatal ("out of memory\n");
		    for (j = 0; j < output_info->nmode; j++)
		    {
			    int k;
			    XRRModeInfo *jmode, *kmode;

			    if (mode_shown[j]) continue;

			    jmode = find_mode_by_xid (output_info->modes[j]);
			    printf (" ");
			    printf ("  %-12s", jmode->name);
			    for (k = j; k < output_info->nmode; k++)
			    {
				    if (mode_shown[k]) continue;
				    kmode = find_mode_by_xid (output_info->modes[k]);
				    if (strcmp (jmode->name, kmode->name) != 0) continue;
				    mode_shown[k] = True;
				    kmode->modeFlags |= ModeShown;
				    printf (" %6.1f", mode_refresh (kmode));
				    if (kmode == output->mode_info)
					    printf ("*");
				    else
					    printf (" ");
				    if (k < output_info->npreferred)
					    printf ("+");
				    else
					    printf (" ");
			    }
			    printf ("\n");
		    }
		    free (mode_shown);
	    }
    }
    for (m = 0; m < res->nmode; m++)
    {
	    XRRModeInfo	*mode = &res->modes[m];

	    if (!(mode->modeFlags & ModeShown))
	    {
		    printf ("  %s (0x%x) %6.1fMHz\n",
				    mode->name, (int)mode->id,
				    (double)mode->dotClock / 1000000.0);
		    printf ("        h: width  %4d start %4d end %4d total %4d skew %4d clock %6.1fKHz\n",
				    mode->width, mode->hSyncStart, mode->hSyncEnd,
				    mode->hTotal, mode->hSkew, mode_hsync (mode) / 1000);
		    printf ("        v: height %4d start %4d end %4d total %4d           clock %6.1fHz\n",
				    mode->height, mode->vSyncStart, mode->vSyncEnd, mode->vTotal,
				    mode_refresh (mode));
	    }
    }

    return(ret);
}
