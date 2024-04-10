#define INPUT "cat < in"

#include <stdio.h>
#include "parser/tokenizer.h"
#include "parser/syntax_analyzer.h"
#include "parser/syntax_tree.h"
#include "parser/semantic_analyzer.h"
#include "execute/execute.h"


void	parse_tree_print(t_parse_tree *parse_tree, int depth, char *arrow);
void	print_syntax_tree(t_syntax_tree *node, int level);
void	print_parse_tree(t_parse_tree *parse_tree, int depth, char *arrow);

 void	leak(void)
 {
 	system("leaks minishell");
 }

 int	main(void)
 {
 	t_grammar		*grammar;
 	t_lr_table		*lr_table;
 	t_list			*token;
 	t_parse_tree	*parse_tree;
 	t_syntax_tree	*syntax_tree;

 	//atexit(leak);
 	grammar = insert_grammar();
 	lr_table = insert_lr_table();
 	token = tokenizer(INPUT);

 	parse_tree = syntax_analyzer(token, grammar, lr_table);
	//print_parse_tree(parse_tree, 0, "└───");
 	syntax_tree = semantic_analyzer(parse_tree);
	//printf(BLUE "-----------print_syntax_tree\n" );
	//print_syntax_tree(syntax_tree, 0);
	printf("-----------exit: %d\n", execute(syntax_tree));
 	exit(0);
 }
