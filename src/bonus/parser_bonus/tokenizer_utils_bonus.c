/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:00:17 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer_bonus.h"

//문자를 비교해서 해당되는 토큰 타입이 있다면 반환하는 함수
t_termi	get_token_type(char *str, int len)
{
	if (len == 2)
	{
		if (*str == '<')
			return (dless);
		else if (*str == '>')
			return (dgreat);
		else if (*str == '|')
			return (or_if);
		else if (*str == '&')
			return (and_if);
	}
	else if (len == 1)
	{
		if (*str == '<')
			return (less);
		else if (*str == '>')
			return (great);
		else if (*str == '|')
			return (pipe_term);
		else if (*str == '(')
			return (lparen);
		else if (*str == ')')
			return (rparen);
	}
	return (word);
}

//Tokenize가 완료된 리스트 끝에 end_token을 추가합니다.
void	add_end_token(t_list *parsed_list)
{
	t_token	*end_token;

	end_token = new_token(NULL, dollar_sign);
	ft_lstadd_back(&parsed_list, ft_lstnew(end_token));
	return ;
}

//t_token을 free합니다.
void	free_token(void *token)
{
	if (((t_token *)token)->word)
		free(((t_token *)token)->word);
	free(token);
}

//t_token을 초기화합니다.
t_token	*new_token(char *word, t_termi type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_malloc(sizeof(t_token));
	new_token -> word = word;
	new_token -> type = type;
	return (new_token);
}

int	is_white_space(char c)
{
	if (9 <= c && c <= 13)
		return (1);
	if (c == 32)
		return (1);
	return (0);
}
