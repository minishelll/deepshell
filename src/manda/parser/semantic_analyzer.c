/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:09 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/10 19:42:56 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "semantic_analyzer.h"

t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree)
{
	t_syntax_tree	*new_node;

	if (parse_tree->child_type[MID] == terminal)
	{
		new_node = syntax_tree_new(((t_token *)parse_tree->child[MID])->type);
		new_node->child[L] = make_syntax_tree(parse_tree->child[LEFT]);
		new_node->child[R] = make_syntax_tree(parse_tree->child[RIGHT]);
		return (new_node);
	}
	if (is_subshell(parse_tree))
		return (make_subshell_node(parse_tree));
	else if (parse_tree->type == simple_command)
	{
		new_node = syntax_tree_new(word);
		make_cmd_node(new_node, parse_tree);
		return (new_node);
	}
	else if (parse_tree->child_type[MID] == none)
	{
		if (parse_tree->child_type[LEFT] == terminal)
			return (syntax_tree_new(((t_token *)parse_tree->child[MID])->type));
		else if (parse_tree->child_type[LEFT] == non_terminal)
			return (make_syntax_tree(parse_tree->child[LEFT]));
	}
	return (NULL);
}

void	make_redi_list(t_list **redi_list, t_parse_tree *parse_tree)
{
	if (parse_tree->type == io_redirect)
	{
		ft_lstadd_back(redi_list, ft_lstnew(make_redi_node(parse_tree)));
		return ;
	}
	make_redi_list(redi_list, parse_tree->child[LEFT]);
	if (parse_tree->child[MID] != NULL)
		make_redi_list(redi_list, parse_tree->child[MID]);
}

void	make_word_list(t_list **cmd, t_list **redi, t_parse_tree *parse_tree)
{
	t_list	*new_node;

	if (parse_tree->type == io_redirect)
	{
		make_redi_list(redi, parse_tree);
		return ;
	}
	if (parse_tree->child_type[LEFT] == terminal)
	{
		new_node = ft_lstnew(((t_token *)parse_tree->child[LEFT])->word);
		ft_lstadd_back(cmd, new_node);
		return ;
	}
	make_word_list(cmd, redi, parse_tree->child[LEFT]);
	if (parse_tree->child_type[MID] == terminal)
	{
		new_node = ft_lstnew(((t_token *)parse_tree->child[MID])->word);
		ft_lstadd_back(cmd, new_node);
		return ;
	}
	if (parse_tree->child[MID] != NULL)
		make_word_list(cmd, redi, parse_tree->child[1]);
}

void	free_parse_tree(t_parse_tree *parse_tree)
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

t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree)
{
	t_syntax_tree	*syntax_tree;

	syntax_tree = make_syntax_tree(parse_tree);
	free_parse_tree(parse_tree);
	return (syntax_tree);
}
