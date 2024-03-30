/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/03/30 16:09:34 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_analyzer.h"

t_parse_tree	*create_parse_tree(t_list **lr_stack, t_grammar grammar)
{
	t_parse_tree	*new;
	t_stack			*tmp[3];
	int				child_cnt;
	int				i;

	child_cnt = 0;
	while (grammar.after[child_cnt][KIND] != none)
		child_cnt++;
	new = (t_parse_tree *)ft_calloc(sizeof(t_parse_tree), 1);
	new->type = grammar.before;
	i = 0;
	while (i < child_cnt)
	{
		free(pop(lr_stack));
		tmp[i] = pop(lr_stack);
		i++;
	}
	new->child_type[LEFT] = tmp[LEFT]->kind;
	new->child_type[MID] = tmp[MID]->kind;
	new->child_type[RIGHT] = tmp[RIGHT]->kind;
	return (new);
}

t_parse_tree	*lexer(t_list *input)
{
	const t_grammar		*grammar = insert_grammar();
	const t_lr_table	*lr_table = insert_lr_table();
	t_parse_tree		*parse_tree;
	t_list				*lr_stack;
	t_action			key;

	push(&lr_stack, state, create_state(0));
	while (1)
	{
		key = get_key_action(lr_table->action \
				, get_state(lr_stack), ((t_token *)input->content)->type);
		if (key.act == shift)
			shift(lr_stack, input, key);
		else if (key.act == reduce)
			reduce(lr_stack, input, key, lr_table);
		else if (key.act == accept)
		{
			parse_tree = create_parse_tree(lr_stack, grammar[0]);
			break ;
		}
		// else if (key.act == init)
		//	ft_error(SYNTAX_ERROR, input->word);
	}
	return (parse_tree);
}
