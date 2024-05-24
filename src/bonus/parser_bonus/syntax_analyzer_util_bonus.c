/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_util_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 01:30:54 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "syntax_analyzer_bonus.h"

static int	_get_child_cnt(t_grammar grammar)
{
	int	child_cnt;

	child_cnt = 0;
	while (child_cnt < 3 && grammar.after[child_cnt][KIND] != none)
		child_cnt++;
	return (child_cnt);
}

t_parse_tree	*create_parse_tree(t_list **lr_stack, t_grammar grammar)
{
	const int		child_cnt = _get_child_cnt(grammar);
	t_parse_tree	*new;
	t_stack			*tmp[3];
	int				i;

	new = (t_parse_tree *)ft_calloc(sizeof(t_parse_tree), 1);
	new->type = grammar.before;
	i = -1;
	while (++i < 3)
	{
		if (i < child_cnt)
		{
			free(pop(lr_stack));
			tmp[i] = pop(lr_stack);
			new->child_type[child_cnt - 1 - i] = tmp[i]->kind;
			new->child[child_cnt - 1 - i] = tmp[i]->ptr;
		}
		else
			new->child_type[i] = none;
	}
	i = -1;
	while (++i < child_cnt)
		free(tmp[i]);
	return (new);
}

void	free_parse_tree(t_parse_tree *parse_tree, void (*del)(void *))
{
	int	idx;

	idx = 0;
	while (idx < 3)
	{
		if (parse_tree->child_type[idx] == terminal)
			del(parse_tree->child[idx]);
		else if (parse_tree->child_type[idx] == non_terminal)
			free_parse_tree(parse_tree->child[idx], del);
		idx ++;
	}
	free(parse_tree);
	return ;
}

void	free_lr_stack(t_list *lr_stack)
{
	t_list	*tmp;

	if (lr_stack == NULL)
		return ;
	while (lr_stack != NULL)
	{
		tmp = lr_stack;
		lr_stack = lr_stack->next;
		if (((t_stack *)tmp->content)->kind == terminal)
			free_token(((t_stack *)tmp->content)->ptr);
		else if (((t_stack *)tmp->content)->kind == non_terminal)
			free_parse_tree(((t_stack *)tmp->content)->ptr, free_token);
		free(tmp->content);
		free(tmp);
	}
}
