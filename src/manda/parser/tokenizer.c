/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:10:43 by sehwanii          #+#    #+#             */
/*   Updated: 2024/04/28 04:54:33 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#  include <stdio.h>
//tokenize를 하는 main 함수
t_list	*tokenizer(char *command)
{
	t_list	*quote_parsed_list;
	t_list	*op_parsed_list;

	quote_parsed_list = parse_quote(command);
	// quote_parsed_list = quote_parsed_list->next;
	// while (quote_parsed_list)
	// {
	// 	printf("%s$\n", ((t_token *)quote_parsed_list->content)->word);
	// 	quote_parsed_list = quote_parsed_list ->next;
	// }
	// exit(1);
	op_parsed_list = parse_op(quote_parsed_list);
	add_end_token(op_parsed_list);
	merge_word_nodes(&op_parsed_list);

	// while (op_parsed_list)
	// {
	// 	printf("%s$\n", ((t_token *)op_parsed_list->content)->word);
	// 	op_parsed_list = op_parsed_list ->next;
	// }

	free(quote_parsed_list);
	return (op_parsed_list);
}
