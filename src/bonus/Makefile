ifndef TOPDIR
	TOPDIR = $(abspath ../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ./)
endif

NAME := minishell_bonus
SRCS := main_bonus.c \
		print_welcome_title_bonus.c \

# SRCS(in SRCDIR) ------
DIRS := ft_error_bonus \
		insert_data_bonus \
		envlist_bonus \
		signal_bonus \
		parser_bonus \
		expand_bonus \
		built_in_bonus \
		execute_bonus \

SUBS := $(addsuffix .a,$(DIRS))

# LIBRARYS -------------
LDLIBS := -lft -lreadline

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_src.mk

