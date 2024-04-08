ifndef TOPDIR
	TOPDIR = $(abspath ../../../)
endif
ifndef SRCDIR
	SRCDIR = $(abspath ../)
endif

NAME := parser.a
HEAD := #이후 semantic관련 외부 파일에서 사용할 헤더
SRCS := tokenizer.c\
		tokenizer_quote_parser.c\
		tokenizer_op_parser.c\
		tokenizer_utils.c\
		syntax_analyzer.c \
		syntax_action.c \
		syntax_lr_stack.c \
		semantic_analyzer.c	\
		semantic_analyzer_utils.c \
		
LDLIBS := -lft

include $(TOPDIR)/include_make/Variable.mk
include $(TOPDIR)/include_make/Link.mk
include $(TOPDIR)/include_make/Recipe_subsrc.mk