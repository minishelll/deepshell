/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:41:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/27 22:04:50 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_type.h"
#include "semantic_analyzer.h"

/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */
void	parse_tree_print(t_parse_tree *parse_tree, int depth, char *arrow);
void	print_syntax_tree(t_syntax_tree *node, int level);
void	print_parse_tree(t_parse_tree *parse_tree, int depth, char *arrow);
#include <stdio.h>
/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */

t_syntax_tree	*parser(t_data *data, char *input)
{
	t_list			*token;
	t_parse_tree	*parse_tree;
	t_syntax_tree	*ast;

	token = tokenizer(input, data->env);
	parse_tree = syntax_analyzer(data, token);
	if (parse_tree == NULL)
		return (NULL);
		//print_parse_tree(parse_tree, 0, NULL);
	
	ast = semantic_analyzer(parse_tree);
	
		//print_syntax_tree(ast, 0);
	free_parse_tree(parse_tree);
	return (ast);
}
