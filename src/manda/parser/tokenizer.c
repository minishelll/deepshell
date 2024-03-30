/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/03/30 15:50:39 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parse_quote(char *command);
t_list	*parse_space(t_list *quote_parsed_list);

void	foo(){
	system("leaks minishell");
}

t_list  *tokenizer(char *command)
{
	t_list	*quote_parsed_list;
	t_list	*paren_parsed_list;

	atexit(foo);
	quote_parsed_list = parse_quote(command);
	paren_parsed_list = parse_paren(quote_parsed_list);

	//ft_lstclear(&(quote_parsed_list -> next), (void *)free_token);
	free(quote_parsed_list);
	//ft_lstclear(&(paren_parsed_list), (void *)free_token);
	return (paren_parsed_list);
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
