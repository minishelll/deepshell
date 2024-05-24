ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := execute_bonus.a
HEAD := execute_bonus.h
SRCS := execute_bonus.c \
		execute_pipe_bonus.c \
		execute_subshell_bonus.c \
		execute_command_bonus.c \
		execute_child_process_bonus.c \
		execute_redirect_bonus.c \
		execute_utils_bonus.c \
		heredoc_bonus.c \
		heredoc_process_bonus.c \

LDLIBS := -lft -lreadline

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk