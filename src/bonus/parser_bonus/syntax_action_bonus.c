/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_action_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:04:21 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_analyzer_bonus.h"

void	act_reduce(t_list **lr_stack, t_action act, t_grammar *grammar
													, t_lr_table *lr_table)
{
	t_parse_tree	*new;
	int				go_to_state;

	new = create_parse_tree(lr_stack, grammar[act.num]);
	go_to_state = get_key_goto(lr_table->go_to \
								, get_state(*lr_stack), new->type);
	push(lr_stack, non_terminal, new);
	push(lr_stack, state, create_state(go_to_state));
}

void	act_shift(t_list **lr_stack, t_list **input, t_action act)
{
	t_stack	*move;

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
