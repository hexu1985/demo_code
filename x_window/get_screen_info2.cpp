#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <math.h>

static Display *dpy;
static Window root;
static int screen = -1;
static bool	verbose = false;
static bool	automatic = false;

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

inline void set_changes_t_flag(changes_t &changes, changes_t flag)
{
    uint32_t flag_bits = changes;
    flag_bits |= flag;
    changes = static_cast<changes_t>(flag_bits);
}

typedef enum _name_kind {
    name_none = 0,
    name_string = (1 << 0),
    name_xid = (1 << 1),
    name_index = (1 << 2),
    name_preferred = (1 << 3),
} name_kind_t;

typedef struct {
    name_kind_t     kind;
    char          *string;
    XID           xid;
    int       index;
} name_t;

inline void set_name_kind_t_flag(name_kind_t &kind, name_kind_t flag)
{
    uint32_t flag_bits = kind;
    flag_bits |= flag;
    kind = static_cast<name_kind_t>(flag_bits);
}

typedef struct _crtc crtc_t;
typedef struct _output  output_t;
typedef struct _transform transform_t;
typedef struct _umode	umode_t;
typedef struct _output_prop output_prop_t;

struct _transform {
    XTransform      transform;
    const char      *filter;
    int       nparams;
    XFixed      *params;
};

struct _crtc {
    name_t      crtc;
    bool      changing;
    XRRCrtcInfo     *crtc_info;

    XRRModeInfo     *mode_info;
    XRRPanning      *panning_info;
    int       x;
    int       y;
    Rotation      rotation;
    output_t      **outputs;
    int       noutput;
    transform_t     current_transform, pending_transform;
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

    bool    	    automatic;
    int     	    scale_from_w, scale_from_h;
    transform_t	    transform;

    struct {
        float red;
        float green;
        float blue;
    } gamma;

    float	    brightness;

    bool	    primary;

    bool	    found;
};

static const char *connection[3] = {
    "connected",
    "disconnected",
    "unknown connection"
};

static output_t *outputs = NULL;
static output_t **outputs_tail = &outputs;
static crtc_t   *crtcs;
static int  num_crtcs;
static XRRScreenResources  *res;
static int  minWidth, maxWidth, minHeight, maxHeight;

static void fatal(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fprintf(stderr, "fatal: ");
    vfprintf(stderr, format, ap);
    va_end(ap);
    exit(1);
    /*NOTREACHED*/
}

static void warning(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    fprintf(stderr, "warning: ");
    vfprintf(stderr, format, ap);
    va_end(ap);
}

static const char *rotation_name(Rotation rotation)
{
    int	i;

    if ((rotation & 0xf) == 0)
        return "normal";
    for (i = 0; i < 4; i++)
        if (rotation & (1 << i))
            return direction[i];
    return "invalid rotation";
}

static const char *reflection_name(Rotation rotation)
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

/* v refresh frequency in Hz */
static double mode_refresh(XRRModeInfo *mode_info)
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
static double mode_hsync(XRRModeInfo *mode_info)
{
    double rate;

    if (mode_info->hTotal)
        rate = (double) mode_info->dotClock / (double) mode_info->hTotal;
    else
        rate = 0;
    return rate;
}

static void init_name(name_t *name)
{
    name->kind = name_none;
}

static void set_name_string(name_t *name, char *string)
{
    set_name_kind_t_flag(name->kind, name_string);
    name->string = string;
}

static void set_name_xid(name_t *name, XID xid)
{
    set_name_kind_t_flag(name->kind, name_xid);
    name->xid = xid;
}

static void set_name_index(name_t *name, int index)
{
    set_name_kind_t_flag(name->kind, name_index);
    name->index = index;
}

static void set_name_preferred(name_t *name)
{
    set_name_kind_t_flag(name->kind, name_preferred);
}

static void set_name_all(name_t *name, name_t *old)
{
    if (old->kind & name_xid)
        name->xid = old->xid;
    if (old->kind & name_string)
        name->string = old->string;
    if (old->kind & name_index)
        name->index = old->index;
    uint32_t kind = name->kind;
    kind |= old->kind;
    name->kind = static_cast<name_kind_t>(kind);
}

static void init_transform(transform_t *transform)
{
    int x; 
    memset(&transform->transform, '\0', sizeof (transform->transform));
    for (x = 0; x < 3; x++)
        transform->transform.matrix[x][x] = XDoubleToFixed (1.0);
    transform->filter = "";
    transform->nparams = 0;
    transform->params = NULL;
}

static void set_transform(transform_t  *dest,
        XTransform   *transform,
        const char   *filter,
        XFixed      *params,
        int     nparams)
{
    dest->transform = *transform;
    /* note: this string is leaked */
    dest->filter = strdup(filter);
    dest->nparams = nparams;
    dest->params = static_cast<XFixed *>(malloc(nparams * sizeof (XFixed)));
    memcpy(dest->params, params, nparams * sizeof (XFixed));
}

static void copy_transform(transform_t *dest, transform_t *src)
{
    set_transform(dest, &src->transform,
            src->filter, src->params, src->nparams);
}


static void get_screen(bool current)
{
    XRRGetScreenSizeRange(dpy, root, &minWidth, &minHeight, &maxWidth, &maxHeight);

    if (current)
        res = XRRGetScreenResourcesCurrent(dpy, root);
    else 
        res = XRRGetScreenResources(dpy, root);
    if (!res) fatal("could not get screen resources");
}

static void get_crtcs()
{
    int		c;

    num_crtcs = res->ncrtc;
    crtcs = static_cast<crtc_t *>(calloc(num_crtcs, sizeof (crtc_t)));
    if (!crtcs) fatal("out of memory\n");

    for (c = 0; c < res->ncrtc; c++)
    {
        XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(dpy, res, res->crtcs[c]);
        XRRCrtcTransformAttributes  *attr;
        XRRPanning  *panning_info = NULL;

#if 0
        XRRPanning zero;
        memset(&zero, 0, sizeof(zero));
        panning_info = XRRGetPanning(dpy, res, res->crtcs[c]);
        zero.timestamp = panning_info->timestamp;
        if (!memcmp(panning_info, &zero, sizeof(zero))) {
            Xfree(panning_info);
            panning_info = NULL;
        }
#endif

        set_name_xid(&crtcs[c].crtc, res->crtcs[c]);
        set_name_index(&crtcs[c].crtc, c);
        if (!crtc_info) fatal("could not get crtc 0x%x information\n", res->crtcs[c]);
        crtcs[c].crtc_info = crtc_info;
        crtcs[c].panning_info = panning_info;
        if (crtc_info->mode == None)
        {
            crtcs[c].mode_info = NULL;
            crtcs[c].x = 0;
            crtcs[c].y = 0;
            crtcs[c].rotation = RR_Rotate_0;
        }
        if (XRRGetCrtcTransform(dpy, res->crtcs[c], &attr) && attr) {
            set_transform(&crtcs[c].current_transform,
                    &attr->currentTransform,
                    attr->currentFilter,
                    attr->currentParams,
                    attr->currentNparams);
            XFree(attr);
        }
        else
        {
            init_transform(&crtcs[c].current_transform);
        }
        copy_transform(&crtcs[c].pending_transform, &crtcs[c].current_transform);
    }
}

static output_t *add_output()
{
    output_t *output = static_cast<output_t *>(calloc(1, sizeof (output_t)));

    if (!output)
        fatal("out of memory\n");
    output->next = NULL;
    output->found = False;
    output->brightness = 1.0;
    *outputs_tail = output;
    outputs_tail = &output->next;
    return output;
}

static output_t *find_output(name_t *name)
{
    output_t *output;

    for (output = outputs; output; output = output->next)
    {
        name_kind_t common = (name_kind_t) ((uint32_t) name->kind & (uint32_t) output->output.kind);

        if ((common & name_xid) && name->xid == output->output.xid)
            break;
        if ((common & name_string) && !strcmp(name->string, output->output.string))
            break;
        if ((common & name_index) && name->index == output->output.index)
            break;
    }
    return output;
}

static crtc_t *find_crtc(name_t *name)
{
    int	    c;
    crtc_t  *crtc = NULL;

    for (c = 0; c < num_crtcs; c++)
    {
        name_kind_t common;

        crtc = &crtcs[c];
        common = static_cast<name_kind_t>(name->kind & crtc->crtc.kind);

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

static crtc_t *find_crtc_by_xid(RRCrtc crtc)
{
    name_t  crtc_name;

    init_name(&crtc_name);
    set_name_xid(&crtc_name, crtc);
    return find_crtc(&crtc_name);
}

static XRRModeInfo *find_mode(name_t *name, double refresh)
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

static XRRModeInfo *find_mode_by_xid(RRMode mode)
{
    name_t  mode_name;

    init_name(&mode_name);
    set_name_xid(&mode_name, mode);
    return find_mode(&mode_name, 0);
}

static XRRModeInfo *find_mode_for_output(output_t *output, name_t *name)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;
    XRRModeInfo	    *best = NULL;
    double	    bestDist = 0;

    for (m = 0; m < output_info->nmode; m++)
    {
        XRRModeInfo	    *mode;

        mode = find_mode_by_xid(output_info->modes[m]);
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
                dist = fabs(mode_refresh (mode) - output->refresh);
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

static XRRModeInfo *preferred_mode(output_t *output)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;
    XRRModeInfo	    *best;
    int		    bestDist;

    best = NULL;
    bestDist = 0;
    for (m = 0; m < output_info->nmode; m++)
    {
        XRRModeInfo *mode_info = find_mode_by_xid(output_info->modes[m]);
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

static bool output_can_use_crtc(output_t *output, crtc_t *crtc)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    c;

    for (c = 0; c < output_info->ncrtc; c++)
        if (output_info->crtcs[c] == crtc->crtc.xid)
            return true;
    return false;
}

static bool output_can_use_mode(output_t *output, XRRModeInfo *mode)
{
    XRROutputInfo   *output_info = output->output_info;
    int		    m;

    for (m = 0; m < output_info->nmode; m++)
        if (output_info->modes[m] == mode->id)
            return true;
    return false;
}

static bool crtc_can_use_rotation(crtc_t *crtc, Rotation rotation)
{
    Rotation	rotations = crtc->crtc_info->rotations;
    Rotation	dir = rotation & (RR_Rotate_0|RR_Rotate_90|RR_Rotate_180|RR_Rotate_270);
    Rotation	reflect = rotation & (RR_Reflect_X|RR_Reflect_Y);
    if (((rotations & dir) != 0) && ((rotations & reflect) == reflect))
        return true;
    return false;
}

/*
 * Report only rotations that are supported by all crtcs
 */
static Rotation output_rotations(output_t *output)
{
    bool	    found = false;
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

static bool output_can_use_rotation(output_t *output, Rotation rotation)
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

static bool output_is_primary(output_t *output)
{
#if 1
    return XRRGetOutputPrimary(dpy, root) == output->output.xid;
#else
    return false;
#endif
}

/* Returns the index of the last value in an array < 0xffff */
static int find_last_non_clamped(CARD16 array[], int size) {
    int i;
    for (i = size - 1; i > 0; i--) {
        if (array[i] < 0xffff)
            return i;
    }
    return 0;
}

static void set_gamma_info(output_t *output)
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

static void set_output_info(output_t *output, RROutput xid, XRROutputInfo *output_info)
{
    /* sanity check output info */
    if (output_info->connection != RR_Disconnected && !output_info->nmode)
        warning("Output %s is not disconnected but has no modes\n",
                output_info->name);

    /* set output name and info */
    if (!(output->output.kind & name_xid))
        set_name_xid(&output->output, xid);
    if (!(output->output.kind & name_string))
        set_name_string(&output->output, output_info->name);
    output->output_info = output_info;

    /* set crtc name and info */
    if (!(output->changes & changes_crtc))
        set_name_xid(&output->crtc, output_info->crtc);

    if (output->crtc.kind == name_xid && output->crtc.xid == None)
        output->crtc_info = NULL;
    else
    {
        output->crtc_info = find_crtc(&output->crtc);
        if (!output->crtc_info)
        {
            if (output->crtc.kind & name_xid)
                fatal("cannot find crtc 0x%x\n", output->crtc.xid);
            if (output->crtc.kind & name_index)
                fatal("cannot find crtc %d\n", output->crtc.index);
        }
        if (!output_can_use_crtc(output, output->crtc_info))
            fatal("output %s cannot use crtc 0x%x\n", output->output.string,
                    output->crtc_info->crtc.xid);
    }

    /* set mode name and info */
    if (!(output->changes & changes_mode))
    {
        crtc_t	*crtc = NULL;

        if (output_info->crtc)
            crtc = find_crtc_by_xid(output_info->crtc);
        if (crtc && crtc->crtc_info)
            set_name_xid(&output->mode, crtc->crtc_info->mode);
        else if (output->crtc_info)
            set_name_xid(&output->mode, output->crtc_info->crtc_info->mode);
        else
            set_name_xid(&output->mode, None);
        if (output->mode.xid)
        {
            output->mode_info = find_mode_by_xid(output->mode.xid);
            if (!output->mode_info)
                fatal("server did not report mode 0x%x for output %s\n",
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
            output->mode_info = preferred_mode(output);
        else
            output->mode_info = find_mode_for_output(output, &output->mode);
        if (!output->mode_info)
        {
            if (output->mode.kind & name_preferred)
                fatal("cannot find preferred mode\n");
            if (output->mode.kind & name_string)
                fatal("cannot find mode %s\n", output->mode.string);
            if (output->mode.kind & name_xid)
                fatal("cannot find mode 0x%x\n", output->mode.xid);
        }
        if (!output_can_use_mode(output, output->mode_info))
            fatal("output %s cannot use mode %s\n", output->output.string,
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
    if (!output_can_use_rotation(output, output->rotation))
        fatal("output %s cannot use rotation \"%s\" reflection \"%s\"\n",
                output->output.string,
                rotation_name(output->rotation),
                reflection_name(output->rotation));

    /* set gamma */
    if (!(output->changes & changes_gamma))
        set_gamma_info(output);

    /* set transformation */
    if (!(output->changes & changes_transform))
    {
        if (output->crtc_info)
            copy_transform(&output->transform, &output->crtc_info->current_transform);
        else
            init_transform(&output->transform);
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
                printf("scaling %s by %lfx%lf\n", output->output.string, sx, sy);
            init_transform(&output->transform);
            output->transform.transform.matrix[0][0] = XDoubleToFixed(sx);
            output->transform.transform.matrix[1][1] = XDoubleToFixed(sy);
            output->transform.transform.matrix[2][2] = XDoubleToFixed(1.0);
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

static void get_outputs()
{
    int		o;
    output_t    *q;

    for (o = 0; o < res->noutput; o++)
    {
        XRROutputInfo	*output_info = XRRGetOutputInfo(dpy, res, res->outputs[o]);
        output_t	*output;
        name_t		output_name;
        if (!output_info) fatal("could not get output 0x%x information\n", res->outputs[o]);
        set_name_xid(&output_name, res->outputs[o]);
        set_name_index(&output_name, o);
        set_name_string(&output_name, output_info->name);
        output = find_output(&output_name);
        if (!output)
        {
            output = add_output();
            set_name_all(&output->output, &output_name);
            /*
             * When global --automatic mode is set, turn on connected but off
             * outputs, turn off disconnected but on outputs
             */
            if (automatic)
            {
                switch (output_info->connection) {
                    case RR_Connected:
                        if (!output_info->crtc) {
                            set_changes_t_flag(output->changes, changes_automatic);
                            output->automatic = true;
                        }
                        break;
                    case RR_Disconnected:
                        if (output_info->crtc)
                        {
                            set_changes_t_flag(output->changes, changes_automatic);
                            output->automatic = true;
                        }
                        break;
                }
            }
        }
        output->found = true;

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
                        set_name_preferred(&output->mode);
                        set_changes_t_flag(output->changes, changes_mode);
                    }
                    break;
                case RR_Disconnected:
                    if ((!(output->changes & changes_mode)))
                    {
                        set_name_xid(&output->mode, None);
                        set_name_xid(&output->crtc, None);
                        set_changes_t_flag(output->changes, changes_mode);
                        set_changes_t_flag(output->changes, changes_crtc);
                    }
                    break;
            }
        }

        set_output_info(output, res->outputs[o], output_info);
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

int main(int argc, char *agrv[])
{
    const char *display_name = NULL;
    int		event_base, error_base;
    int		major, minor;

    dpy = XOpenDisplay(display_name);
    std::cout << "ScreenCount: " << ScreenCount(dpy) << std::endl;

    screen = DefaultScreen(dpy);

    root = RootWindow(dpy, screen);

    if (!XRRQueryExtension (dpy, &event_base, &error_base) ||
            !XRRQueryVersion (dpy, &major, &minor))
    {
        fprintf (stderr, "RandR extension missing\n");
        exit (1);
    }

    get_screen(true);
    printf("Screen %d: minimum %d x %d, current %d x %d, maximum %d x %d\n",
            screen, minWidth, minHeight,
            DisplayWidth(dpy, screen), DisplayHeight(dpy, screen),
            maxWidth, maxHeight);

    get_crtcs();
    get_outputs();

    for (output_t *output = outputs; output; output = output->next) {
        XRROutputInfo   *output_info = output->output_info;
        crtc_t	    *crtc = output->crtc_info;
        XRRCrtcInfo	    *crtc_info = crtc ? crtc->crtc_info : NULL;
        XRRModeInfo	    *mode = output->mode_info;
        Atom	    *props;
        int		    j, nprop;
        Bool	    *mode_shown;
        Rotation	    rotations = output_rotations (output);

        if (RR_Disconnected == output_info->connection) {
            printf("%s %s\n", output_info->name, connection[output_info->connection]);
            continue;
        } else {
            printf("%s %s", output_info->name, connection[output_info->connection]);
        }

        if (output_is_primary(output)) {
            printf(" primary");
        }

        if (mode)
        {
            if (crtc_info) {
                printf(" %dx%d+%d+%d",
                        crtc_info->width, crtc_info->height,
                        crtc_info->x, crtc_info->y);
            } else {
                printf(" %dx%d+%d+%d",
                        mode->width, mode->height, output->x, output->y);
            }
            if (verbose)
                printf(" (0x%x)", (int)mode->id);
            if (output->rotation != RR_Rotate_0 || verbose)
            {
                printf(" %s", 
                        rotation_name (output->rotation));
                if (output->rotation & (RR_Reflect_X|RR_Reflect_Y))
                    printf (" %s", reflection_name (output->rotation));
            }
        }

        printf("\n");
    }

    return 0;
}

