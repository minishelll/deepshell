/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_lr_stack_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 16:43:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "syntax_analyzer_bonus.h"

t_stack	*pop(t_list **top)
{
	t_list	*tmp;
	t_stack	*stack;

	if (*top == NULL)
		return (NULL);
	tmp = *top;
	*top = (*top)->next;
	stack = tmp->content;
	free(tmp);
	return (stack);
}

void	push(t_list **top, t_kind kind, void *content)
{
	t_stack	*new;

	if (kind != state)
	{
		new = (t_stack *)ft_malloc(sizeof(t_stack));
		new->kind = kind;
		new->state = -1;
		new->ptr = content;
	}
	else
		new = content;
	if (*top == NULL)
		*top = ft_lstnew(new);
	else
		ft_lstadd_front(top, ft_lstnew(new));
}

t_stack	*create_state(int state_num)
{
	t_stack	*new;

	new = (t_stack *)ft_malloc(sizeof(t_stack));
	new->kind = state;
	new->state = state_num;
	new->ptr = NULL;
	return (new);
}

int	get_state(t_list *top)
{
	t_stack	*tmp;

	tmp = (t_stack *)top->content;
	if (tmp->kind == state)
		return (tmp->state);
	tmp = (t_stack *)top->next->content;
	if (tmp->kind == state)
		return (tmp->state);
	return (-1);
}
