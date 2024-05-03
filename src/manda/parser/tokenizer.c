/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/05/02 22:20:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include<stdio.h>
//tokenize를 하는 main 함수
t_list	*tokenizer(char *command)
{
	t_list	*quote_parsed_list;
	t_list	*op_parsed_list;

	quote_parsed_list = parse_quote(command);
	op_parsed_list = parse_op(quote_parsed_list);
	add_end_token(op_parsed_list);
	//t_list *curr;
	// for(curr = op_parsed_list; ((t_token *)curr->content)->type != dollar_sign; curr = curr->next)
	// {
	// 	printf("token[%d]: ", ((t_token *)curr->content)->type);
	// 	if (((t_token *)curr->content)->type == word)
	// 		printf("%s\n", ((t_token *)curr->content)->word);
	// 	else
	// 		printf("\n");
	// }
	merge_word_nodes(&op_parsed_list);
	free(quote_parsed_list);
	return (op_parsed_list);
}
