ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := envlist.a
HEAD := envlist.h
SRCS := envlist.c \
		envlist_util.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk