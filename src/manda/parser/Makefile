ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := parser.a
HEAD := parser.h \
		syntax_tree.h \

SRCS := parser.c \
		tokenizer.c\
		tokenizer_quote_parser.c\
		tokenizer_op_parser.c\
		tokenizer_utils.c\
		expand.c \
		syntax_analyzer.c \
		syntax_action.c \
		syntax_lr_stack.c \
		syntax_analyzer_util.c \
		semantic_analyzer.c	\
		semantic_analyzer_utils.c \
		
LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk