ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := parser_bonus.a
HEAD := parser_bonus.h \
		syntax_tree_bonus.h \
		tokenizer_bonus.h \

SRCS := parser_bonus.c \
		tokenizer_bonus.c\
		tokenizer_quote_parser_bonus.c\
		tokenizer_op_parser_bonus.c\
		tokenizer_utils_bonus.c\
		syntax_analyzer_bonus.c \
		syntax_action_bonus.c \
		syntax_lr_stack_bonus.c \
		syntax_analyzer_util_bonus.c \
		semantic_analyzer_bonus.c	\
		semantic_analyzer_utils_bonus.c \
		
LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk