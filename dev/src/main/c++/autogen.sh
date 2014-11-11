#!/bin/sh

if test ! -d build-aux; then
	mkdir build-aux
fi
if test ! -d m4; then
	mkdir m4
fi
autoreconf --force --install --verbose -I build-aux -I m4
