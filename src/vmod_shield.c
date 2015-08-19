#include <stdlib.h>

#include "vcl.h"
#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

VCL_VOID
vmod_conn_reset(const struct vrt_ctx *ctx)
{
	struct linger lin;

	if (ctx->method != VCL_MET_RECV) {
		VSLb(ctx->vsl, SLT_VCL_Error,
		    "This function is only available in vcl_recv");
		return;
	}

	if (ctx->req->sp->fd < 0)
		return;

	/* Force a path to vcl_error */
	ctx->req->restarts = cache_param->max_restarts;
	/* Set SO_LINGER with zero timeout before closing, to force a
	 * RST */
        memset(&lin, 0, sizeof lin);
        lin.l_onoff = 1;
	setsockopt(ctx->req->sp->fd, SOL_SOCKET, SO_LINGER, &lin, sizeof lin);
      	/* Close the connection */
	SES_Close(ctx->req->sp, SC_RESP_CLOSE);
}
