/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/03/30 17:30:39 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parse_quote(char *command);
t_list	*parse_space(t_list *quote_parsed_list);
void	add_end_token(t_list *parsed_list);

t_list	*tokenizer(char *command)
{
	t_list	*quote_parsed_list;
	t_list	*op_parsed_list;

	quote_parsed_list = parse_quote(command);
	op_parsed_list = parse_op(quote_parsed_list);
	add_end_token(op_parsed_list);
	free(quote_parsed_list);
	return (op_parsed_list);
}

void	free_token(t_token *token)
{
	free(token->word);
	free(token);
}

void	add_end_token(t_list *parsed_list)
{
	t_token	*end_token;

	end_token = (t_token *)ft_malloc(sizeof(t_token));
	end_token -> word = ft_strdup("$");
	end_token -> type = dollar_sign;
	ft_lstadd_back(&parsed_list, ft_lstnew(end_token));
	return ;
}
