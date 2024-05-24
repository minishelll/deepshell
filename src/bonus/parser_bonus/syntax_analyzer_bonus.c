/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:34:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "syntax_analyzer_bonus.h"
#include "ft_error_bonus.h"

static int	_handle_syntax_error(t_token *token)
{
	if (token->type == and_if)
		ft_error(error_syntax, 0, S_AND_IF);
	else if (token->type == or_if)
		ft_error(error_syntax, 0, S_OR_IF);
	else if (token->type == pipe_term)
		ft_error(error_syntax, 0, S_PIPE);
	else if (token->type == lparen)
		ft_error(error_syntax, 0, S_LPAREN);
	else if (token->type == rparen)
		ft_error(error_syntax, 0, S_RPAREN);
	else if (token->type == less)
		ft_error(error_syntax, 0, S_LESS);
	else if (token->type == great)
		ft_error(error_syntax, 0, S_GREAT);
	else if (token->type == dgreat)
		ft_error(error_syntax, 0, S_DGREAT);
	else if (token->type == dless)
		ft_error(error_syntax, 0, S_DLESS);
	else if (token->type == dollar_sign)
		ft_error(error_syntax, 0, "newline");
	else if (token->type == word)
		ft_error(error_syntax, 0, token->word);
	return (SYNTAX_ERRNUM);
}

t_status	_action_once(t_data *data, t_list **lr_stack, t_list **curr)
{
	t_action	key;

	key = get_key_action(data->lr_table->action \
				, get_state(*lr_stack), ((t_token *)(*curr)->content)->type);
	if (key.act == shift)
		act_shift(lr_stack, curr, key);
	else if (key.act == reduce)
		act_reduce(lr_stack, key, data->grammar, data->lr_table);
	else if (key.act == accept)
		return (complete);
	else if (key.act == init)
	{
		data->env->exit_code = _handle_syntax_error((*curr)->content);
		return (syntax_error);
	}
	return (none_status);
}

t_parse_tree	*syntax_analyzer(t_data *data, t_list *input)
{
	t_parse_tree	*parse_tree;
	t_list			*lr_stack;
	t_status		status;

	status = none_status;
	parse_tree = NULL;
	lr_stack = NULL;
	push(&lr_stack, state, create_state(0));
	while (status == none_status)
		status = _action_once(data, &lr_stack, &input);
	if (status == complete)
	{
		parse_tree = create_parse_tree(&lr_stack, data->grammar[0]);
		ft_lstdelone(input, free);
		ft_lstdelone(lr_stack, free);
	}
	else if (status == syntax_error)
	{
		ft_lstclear(&input, free_token);
		free_lr_stack(lr_stack);
	}
	return (parse_tree);
}
