ifndef TOPDIR
	TOPDIR = $(abspath ../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ./)
endif

NAME := minishell
SRCS := main_syntax_analyzer_print.c \

# SRCS(in SRCDIR) ------
DIRS := parser \

SUBS := $(addsuffix .a,$(DIRS))

# LIBRARYS -------------
LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_src.mk