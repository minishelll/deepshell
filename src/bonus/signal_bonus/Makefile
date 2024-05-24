ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := signal_bonus.a
HEAD := mini_signal_bonus.h
SRCS := signal_handler_bonus.c \
		mini_terminal_bonus.c \
		do_signal_bonus.c \
		set_signal_bonus.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk