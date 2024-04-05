/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/01 20:03:04 by taerankim        ###   ########.fr       */
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
	while (child_cnt < 3 && grammar.after[child_cnt][KIND] != none)
		child_cnt++;
	new = (t_parse_tree *)ft_calloc(sizeof(t_parse_tree), 1);
	new->type = grammar.before;
	i = 0;
	while (i < 3)
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
		i++;
	}
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
			exit(EXIT_FAILURE);
		//	ft_error(SYNTAX_ERROR, input->word);
	}
	return (parse_tree);
}
