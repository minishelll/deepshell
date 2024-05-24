ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := execute.a
HEAD := execute.h
SRCS := execute.c \
		execute_pipe.c \
		execute_subshell.c \
		execute_command.c \
		execute_child_process.c \
		execute_redirect.c \
		execute_utils.c \
		heredoc.c \
		heredoc_process.c \

LDLIBS := -lft -lreadline

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk