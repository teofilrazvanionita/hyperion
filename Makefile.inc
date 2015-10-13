# Makefile.inc - common definitions used by all makefiles

CPPC = g++
HYPERION_DIR = ../../
HYPERION_INCL_DIR = ${HYPERION_DIR}include/server

CPPFLAGS = -g -I${HYPERION_INCL_DIR} \
	   -I/usr/include/nacl \
	   -Wall \
	   -Wno-sign-compare \
	   -Wno-unused-parameter \
	   -Wextra

LDLIBS = -lnacl

RM = rm -f
