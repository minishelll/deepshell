/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/04/01 17:28:09 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*parse_quote(char *command);
t_list	*parse_space(t_list *quote_parsed_list);
void	add_end_token(t_list *parsed_list);

//tokenize를 하는 main 함수
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

//t_token을 free합니다.
void	free_token(t_token *token)
{
	free(token->word);
	free(token);
}

//Tokenize가 완료된 리스트 끝에 end_token을 추가합니다.
void	add_end_token(t_list *parsed_list)
{
	t_token	*end_token;

	end_token = (t_token *)ft_malloc(sizeof(t_token));
	end_token -> word = ft_strdup("$");
	end_token -> type = dollar_sign;
	ft_lstadd_back(&parsed_list, ft_lstnew(end_token));
	return ;
}
// #include <stdio.h>
// int main(){
// 	t_list	*op_parsed_list;

// 	char *str = "echo -e \"a\"\'b\' && (cat -e)";
// 	op_parsed_list = tokenizer(str);
// 	while (op_parsed_list){
// 		printf("%-10s   :   %10u?\n",((t_token *)op_parsed_list->content)->word,((t_token *)op_parsed_list->content)->type);
// 		op_parsed_list = op_parsed_list->next;
// 	}
// }