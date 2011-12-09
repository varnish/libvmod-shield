#include <stdlib.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

void
vmod_conn_reset(struct sess *sp)
{
	if (sp->step != STP_RECV)
		return;
	if (sp->fd < 0)
		return;

	/* Force a path to vcl_error */
	sp->restarts = params->max_restarts;
	/* Set SO_LINGER with zero timeout before closing, to force a
	 * RST */
	VTCP_linger(sp->fd, 1);
	/* Close the connection */
	vca_close_session(sp, "vmod_shield conn_reset");
}
