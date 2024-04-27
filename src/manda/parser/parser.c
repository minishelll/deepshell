/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:41:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/27 21:49:35 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_type.h"
#include "semantic_analyzer.h"

//free parse tree recursively
static void	free_parse_tree(t_parse_tree *parse_tree)
{
	int	idx;

	idx = 0;
	while (idx < 3)
	{
		if (parse_tree->child_type[idx] == terminal)
			free(parse_tree->child[idx]);
		else if (parse_tree->child_type[idx] == non_terminal)
			free_parse_tree(parse_tree->child[idx]);
		idx ++;
	}
	free(parse_tree);
	return ;
}

/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */
void	parse_tree_print(t_parse_tree *parse_tree, int depth, char *arrow);
void	print_syntax_tree(t_syntax_tree *node, int level);
void	print_parse_tree(t_parse_tree *parse_tree, int depth, char *arrow);
void	wildcard(t_list **token);
/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */

t_syntax_tree	*parser(t_lr_table *lr_table, t_grammar *grammar, char *input)
{
	t_list			*token;
	t_parse_tree	*parse_tree;
	t_syntax_tree	*ast;

	token = tokenizer(input);
	if (token == NULL)
		return (0);
	//wildcard(&token);
	parse_tree = syntax_analyzer(token, grammar, lr_table);
	ast = semantic_analyzer(parse_tree);
	
	//print_parse_tree(parse_tree, 0, NULL);
	//print_syntax_tree(ast, 0);
	
	free_parse_tree(parse_tree);
	return (ast);
}
