ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := built_in_bonus.a
HEAD := built_in_bonus.h
SRCS := built_in_bonus.c \
		built_in_env_bonus.c \
		built_in_envedit_bonus.c \
		built_in_other_bonus.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk