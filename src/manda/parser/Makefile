ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := parser.a
HEAD := parser.h
SRCS := tokenizer.c\
		tokenizer_quote_parser.c\
		tokenizer_op_parser.c\
		tokenizer_utils.c\
		insert_lr_table.c \
		insert_grammar.c \
		insert_util.c \
		syntax_analyzer.c \
		syntax_action.c \
		syntax_lr_stack.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk