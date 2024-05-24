/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:41:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "input_type_bonus.h"
#include "semantic_analyzer_bonus.h"
#include "ft_error_bonus.h"

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
	free_parse_tree(parse_tree, free);
	return (ast);
}

void	free_redi(void *redi)
{
	t_redi	*ptr;

	ptr = (t_redi *)redi;
	free(ptr->file);
	free(ptr);
}

void	free_syntax_tree(t_syntax_tree *curr)
{
	t_list	*redi_list;

	if (curr->type == command)
	{
		free_words(curr->child[L]);
		if (curr->child[R] != NULL)
		{
			redi_list = curr->child[R];
			ft_lstclear(&redi_list, free_redi);
		}
		free(curr);
		return ;
	}
	free_syntax_tree(curr->child[L]);
	if (curr->child[R] != NULL)
	{
		if (curr->type == subshell)
		{
			redi_list = curr->child[R];
			ft_lstclear(&redi_list, free_redi);
		}
		else
			free_syntax_tree(curr->child[R]);
	}
	free(curr);
}
