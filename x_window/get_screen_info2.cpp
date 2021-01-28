#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <stdlib.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>

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

typedef struct _crtc crtc_t;
typedef struct _output  output_t;
typedef struct _transform transform_t;

struct _transform {
    XTransform      transform;
    const char      *filter;
    int       nparams;
    XFixed      *params;
};

struct _crtc {
    name_t      crtc;
    Bool      changing;
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

static Display *dpy;
static Window root;
static int screen = -1;

static crtc_t   *crtcs;
static int  num_crtcs;
static XRRScreenResources  *res;
static int  minWidth, maxWidth, minHeight, maxHeight;

static void fatal(const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
    exit(1);
    /*NOTREACHED*/
}

static void set_name_xid (name_t *name, XID xid)
{
    int kind = name->kind;
    kind |= name_xid;
    name->kind = static_cast<name_kind_t>(kind);
    name->xid = xid;
}

static void set_name_index (name_t *name, int index)
{
    int kind = name->kind;
    kind |= name_index;
    name->kind = static_cast<name_kind_t>(kind);
    name->index = index;
}

static void init_transform (transform_t *transform)
{
    int x; 
    memset (&transform->transform, '\0', sizeof (transform->transform));
    for (x = 0; x < 3; x++)
        transform->transform.matrix[x][x] = XDoubleToFixed (1.0);
    transform->filter = "";
    transform->nparams = 0;
    transform->params = NULL;
}

static void set_transform (transform_t  *dest,
        XTransform   *transform,
        const char   *filter,
        XFixed      *params,
        int     nparams)
{
    dest->transform = *transform;
    /* note: this string is leaked */
    dest->filter = strdup (filter);
    dest->nparams = nparams;
    dest->params = static_cast<XFixed *> (malloc (nparams * sizeof (XFixed)));
    memcpy (dest->params, params, nparams * sizeof (XFixed));
}

static void copy_transform (transform_t *dest, transform_t *src)
{
    set_transform (dest, &src->transform,
            src->filter, src->params, src->nparams);
}


static void get_screen (bool current)
{
    XRRGetScreenSizeRange (dpy, root, &minWidth, &minHeight, &maxWidth, &maxHeight);

    if (current)
        res = XRRGetScreenResourcesCurrent (dpy, root);
    else 
        res = XRRGetScreenResources (dpy, root);
    if (!res) fatal ("could not get screen resources");
}

static void get_crtcs()
{
    int		c;

    num_crtcs = res->ncrtc;
    crtcs = static_cast<crtc_t *>(calloc (num_crtcs, sizeof (crtc_t)));
    if (!crtcs) fatal ("out of memory\n");

    for (c = 0; c < res->ncrtc; c++)
    {
        XRRCrtcInfo *crtc_info = XRRGetCrtcInfo (dpy, res, res->crtcs[c]);
        XRRCrtcTransformAttributes  *attr;
        XRRPanning  *panning_info = NULL;

#if 0
        XRRPanning zero;
        memset(&zero, 0, sizeof(zero));
        panning_info = XRRGetPanning  (dpy, res, res->crtcs[c]);
        zero.timestamp = panning_info->timestamp;
        if (!memcmp(panning_info, &zero, sizeof(zero))) {
            Xfree(panning_info);
            panning_info = NULL;
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

int main(int argc, char *agrv[])
{
    const char *display_name = NULL;

    dpy = XOpenDisplay(display_name);
    std::cout << "ScreenCount: " << ScreenCount(dpy) << std::endl;

    screen = DefaultScreen(dpy);

    root = RootWindow(dpy, screen);

    get_screen(true);
    printf ("Screen %d: minimum %d x %d, current %d x %d, maximum %d x %d\n",
            screen, minWidth, minHeight,
            DisplayWidth (dpy, screen), DisplayHeight(dpy, screen),
            maxWidth, maxHeight);


    return 0;
}

