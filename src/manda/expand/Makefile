ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := expand.a
HEAD := expand.h \
		wildcard.h \
		
SRCS := expand.c \
		expand_word.c \
		expand_variable.c \
		wildcard.c \
		wildcard_utils.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk