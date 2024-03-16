CC?=gcc
PKG_CONFIG?=pkg-config

CFLAGS?=-g -O2 -Wall
LDFLAGS?=-L. soundlib.c -lm

PREFIX?=/usr/local
DESTDIR?=

# arch hardening
#CPPFLAGS+=-D_FORTIFY_SOURCE=2
#CFLAGS+=-march=x86-64 -mtune=generic -O2 -pipe -fno-plt
#LDFLAGS+=-Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now

# arch & debian hardening workaround
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
        LDFLAGS+=-Wl,--no-as-needed
endif


CFLAGS+=$(shell $(PKG_CONFIG) sdl2 --cflags)
LDFLAGS+=$(shell $(PKG_CONFIG) sdl2 --libs)

CFLAGS+=$(shell $(PKG_CONFIG) glut --cflags)
LDFLAGS+=$(shell $(PKG_CONFIG) glut --libs)

CFLAGS+=$(shell $(PKG_CONFIG) glu --cflags)
LDFLAGS+=$(shell $(PKG_CONFIG) glu --libs)

all: main

