/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 18:15:45 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_analyzer.h"

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

t_parse_tree	*syntax_analyzer(t_list *input
								, t_grammar *grammar, t_lr_table *lr_table)
{
	t_parse_tree	*parse_tree;
	t_list			*lr_stack;
	t_action		key;

	lr_stack = NULL;
	push(&lr_stack, state, create_state(0));
	while (1)
	{
		key = get_key_action(lr_table->action \
				, get_state(lr_stack), ((t_token *)input->content)->type);
		if (key.act == shift)
			act_shift(&lr_stack, &input, key);
		else if (key.act == reduce)
			act_reduce(&lr_stack, key, grammar, lr_table);
		else if (key.act == accept)
		{
			parse_tree = create_parse_tree(&lr_stack, grammar[0]);
			break ;
		}
		else if (key.act == init)
			ft_error(error_syntax, input->word);
	}
	ft_lstdelone(input, free);
	ft_lstdelone(lr_stack, free);
	return (parse_tree);
}
