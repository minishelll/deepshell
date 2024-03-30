/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:45:39 by sehwjang          #+#    #+#             */
/*   Updated: 2024/03/30 17:27:42 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void					parse_token(t_list **list, char *str);
static void				token_add_back(t_list **token_list, char *str);
static enum e_terminal	get_token_type(char *str);

//토큰을 공백 기준으로 나누어 파싱하는 함수
static void	split_token(t_list **list, char *str)
{
	char	**words;
	char	**temp;
	int		idx;

	idx = -1;
	words = ft_split(str, ' ');
	temp = words;
	while (words && *words)
	{
		parse_token(list, *(words));
		words++;
	}
	while (temp[++idx] != NULL)
		free(temp[idx]);
	free(temp);
}

//토큰의 문자열을 공백과 연산자로 파싱하는 함수
t_list	*parse_op(t_list *quote_parsed_list)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*temp_list;

	temp_list = NULL;
	prev = quote_parsed_list;
	cur = quote_parsed_list->next;
	while (cur)
	{
		if (((t_token *)cur->content)->type == undefined)
		{
			split_token(&temp_list, ((t_token *)cur->content)->word);
			free_token((prev->next)->content);
			free(prev->next);
			prev->next = temp_list;
			prev = ft_lstlast(temp_list);
			ft_lstadd_back(&temp_list, cur->next);
			temp_list = NULL;
		}
		else
			prev = cur;
		cur = cur->next;
	}
	return (quote_parsed_list->next);
}

//토큰의 문자열을 연산자를 기준으로 파싱하는 함수 
void	parse_token(t_list **temp, char *str)
{
	int			i;
	int			prev_i;

	i = -1;
	prev_i = 0;
	while (str[++i])
	{
		if (str[i] == '&' || str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (str[i + 1] == str[i])
			{
				token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
				token_add_back(temp, ft_substr(str, i++, 2));
				prev_i = i + 1;
			}
			else if (str[i] != '&')
			{
				token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
				token_add_back(temp, ft_substr(str, i, 1));
				prev_i = i + 1;
			}
		}
	}
	token_add_back(temp, ft_substr(str, prev_i, i - prev_i));
}

//토큰의 메모리를 할당하고, 타입과 문자열을 초기화하는 함수
static void	token_add_back(t_list **token_list, char *str)
{
	t_token		*token;

	if (*str == '\0')
	{
		free(str);
		return ;
	}
	token = (t_token *)ft_malloc(sizeof(t_token));
	token->type = get_token_type(str);
	token->word = ft_strtrim(str, " ");
	ft_lstadd_back(token_list, ft_lstnew(token));
	free(str);
}

//문자를 비교해서 해당되는 토큰 타입이 있다면 반환하는 함수
enum e_terminal	get_token_type(char *str)
{
	const int	len = ft_strlen(str);

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
			return (pipe);
	}
	return (undefined);
}
