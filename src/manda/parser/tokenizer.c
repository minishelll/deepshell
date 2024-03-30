/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/03/30 17:11:39 by sehwjang         ###   ########.fr       */
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
	// while (op_parsed_list){
	// 	printf("%s$\n",((t_token *)op_parsed_list->content)->word);
	// 	op_parsed_list = op_parsed_list->next;
	// }
	return (op_parsed_list);
}

int	main(void)
{
	char	*str = "echo|||echo -e \"a\"\"b\" | cat           \"a\"\'c\'";

	printf("%s\n", str);
	tokenizer(str);
}

void	free_token(t_token *token)
{
	free(token->word);
	free(token);
}

void	add_end_token(t_list *parsed_list)
{
	t_token	*end_token;

	end_token = (t_token *)malloc(sizeof(t_token));
	end_token -> word = "$";
	end_token -> type = dollar_sign;
	ft_lstadd_back(&parsed_list, ft_lstnew(end_token));
	return ;
}
