ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := parser.a
HEAD := parser.h \
		insert_data.h \
		syntax_analyzer.h \

SRCS := insert_lr_table.c \
		insert_grammar.c \
		insert_util.c \
		tokenizer.c\
		quote_parser.c\
		op_parser.c\
		syntax_analyzer.c \
		action.c \
		lr_stack.c \

LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk