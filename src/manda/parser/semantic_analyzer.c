/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:09 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/08 17:51:10 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "semantic_analyzer.h"

void traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree);


t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree)
{
	t_syntax_tree	*syntax_tree;
	//int				idx;

	//idx = 0;
	syntax_tree = (t_syntax_tree *)ft_malloc(sizeof(t_syntax_tree));
	syntax_tree = make_syntax_tree(parse_tree);
	return (syntax_tree);
}

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
	if(is_subshell(parse_tree))
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

void	traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree)
{
	if (parse_tree->type == io_redirect)
	{
		make_redi_list(redi_list, parse_tree);
		return ;
	}
	if (parse_tree->child_type[0] == terminal)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(((t_token *)parse_tree->child[0])->word));
		return ;
	}
	traversal_words(cmd_list, redi_list, parse_tree->child[0]);
	if (parse_tree->child_type[1] == terminal)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(((t_token *)parse_tree->child[1])->word));
		return ;
	}
	if (parse_tree->child[1] != NULL)
		traversal_words(cmd_list, redi_list, parse_tree->child[1]);
}

void	make_redi_list(t_list **redi_list, t_parse_tree *parse_tree)
{

	if (parse_tree->type == io_redirect)
	{
		ft_lstadd_back(redi_list, ft_lstnew(make_redi_node(parse_tree)));
		return ;
	}
	make_redi_list(redi_list, parse_tree->child[0]);
	if (parse_tree->child[1] != NULL)
		make_redi_list(redi_list, parse_tree->child[1]);
}
