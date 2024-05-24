ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := expand_bonus.a
HEAD := expand_bonus.h \
		wildcard_bonus.h \
		
SRCS := expand_bonus.c \
		expand_word_bonus.c \
		expand_variable_bonus.c \
		wildcard_bonus.c \
		wildcard_utils_bonus.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk