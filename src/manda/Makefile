ifndef TOPDIR
	TOPDIR = $(abspath ../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ./)
endif

NAME := minishell
SRCS := main.c \
		print_welcome_title.c \
		_print_parser_result.c \

# SRCS(in SRCDIR) ------
DIRS := ft_error \
		insert_data \
		parser \
		envlist \
		built_in \
		execute \

SUBS := $(addsuffix .a,$(DIRS))

# LIBRARYS -------------
LDLIBS := -lft -lreadline

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_src.mk