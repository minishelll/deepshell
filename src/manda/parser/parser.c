/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:41:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/02 22:21:24 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_type.h"
#include "semantic_analyzer.h"
#include "ft_error.h"

/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */
void	parse_tree_print(t_parse_tree *parse_tree, int depth, char *arrow);
void	print_syntax_tree(t_syntax_tree *node, int level);
void	print_parse_tree(t_parse_tree *parse_tree, int depth, char *arrow);
#include <stdio.h>
/* DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE DELETE */

static int	_count_heredoc(t_list *token)
{
	int	cnt;

	cnt = 0;
	while (token != NULL)
	{
		if (((t_token *)token->content)->type == dless)
			cnt++;
		token = token->next;
	}
	return (cnt);
}

t_syntax_tree	*parser(t_data *data, char *input)
{
	t_list			*token;
	t_parse_tree	*parse_tree;
	t_syntax_tree	*ast;
	int				heredoc;

	token = tokenizer(input);
	heredoc = _count_heredoc(token);
	parse_tree = syntax_analyzer(data, token);
	if (parse_tree == NULL)
		return (NULL);
	if (heredoc > 16)
		ft_error(error_max_heredoc, 0, NULL);
	ast = semantic_analyzer(parse_tree);
	free_parse_tree(parse_tree);
	return (ast);
}
