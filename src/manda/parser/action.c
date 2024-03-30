/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:04:21 by taerakim          #+#    #+#             */
/*   Updated: 2024/03/29 11:44:38 by taerankim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_analyzer.h"

void	reduce(t_list **lr_stack, t_grammar *grammar \
				, t_action act, t_lr_table *lr_table)
{
	t_parse_tree	*new;
	int				go_to_state;

	new = create_parse_tree(lr_stack, grammar[act.num]);
	go_to_state = get_key_goto(lr_table->go_to \
								, get_state(lr_stack), new->type);
	push(lr_stack, non_terminal, new);
	push(lr_stack, state, create_state(go_to_state));
}

void	shift(t_list **lr_stack, t_list **input, t_action act)
{
	t_list	*move;

	move = pop(input);
	push(lr_stack, terminal, move);
	push(lr_stack, state, create_state(act.num));
}

t_action	get_key_action(t_action **dst, int state, t_termi type)
{
	return (dst[state][type]);
}

int	get_key_goto(t_action **dst, int state, t_ntermi type)
{
	return (dst[state][type].num);
}
