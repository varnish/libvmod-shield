===========
vmod_shield
===========

---------------------
Varnish Shield Module
---------------------

:Author: Martin Blix Grydeland
:Date: 2011-12-09
:Version: 1.0
:Manual section: 3

SYNOPSIS
========

import shield;

DESCRIPTION
===========

This vmod contains some routines that may be useful in guarding
against malicious traffic on your Varnish server.

FUNCTIONS
=========

conn_reset
----------

Prototype

	::

		conn_reset()

Return value

	NONE

Description

	Sets SO_LINGER with a zero timeout on the client connection
	and closes the socket to force a TCP RST. Also sets the
	restarts counter to max_restarts, to force a vcl_error
	situation.

	Should only be called from vcl_recv{}, and will be a no-op if
	called anywhere else.

Example

	::

		sub vcl_recv {
			if (req.url ~ "i-am-an-attacker") {
				shield.conn_reset();
			}
		}


INSTALLATION
============

Usage

	::

		 ./configure VARNISHSRC=DIR [VMODDIR=DIR]

`VARNISHSRC` is the directory of the Varnish source tree for which to
compile your vmod. Both the `VARNISHSRC` and `VARNISHSRC/include`
will be added to the include search paths for your module.

Optionally you can also set the vmod install directory by adding
`VMODDIR=DIR` (defaults to the pkg-config discovered directory from your
Varnish installation).

Make targets:

* make - builds the vmod
* make install - installs your vmod in `VMODDIR`
* make check - runs the unit tests in ``src/tests/*.vtc``

In your VCL you could then use this vmod along the following lines:

	::

		import shield;

HISTORY
=======

This manual page was released as part of the libvmod-shield package.

COPYRIGHT
=========

This document is licensed under the same license as the
libvmod-shield project. See LICENSE for details.

* Copyright (c) 2011 Varnish Software
