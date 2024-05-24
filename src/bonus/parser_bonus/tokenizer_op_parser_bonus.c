/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_op_parser_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:45:39 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer_bonus.h"

static void	parse_token(t_list **list, char *str);
static void	token_add_back(t_list **token_list, char *str);
static void	split_token(t_list **list, char *str);

//parsed_token_list를 기존 리스트에 붙여주는 함수
void	link_list(t_list **prev, t_list **cur, t_list **parsed_token_list)
{
	t_list	*temp;

	(*prev)->next = *parsed_token_list;
	(*prev) = ft_lstlast(*parsed_token_list);
	ft_lstadd_back(parsed_token_list, (*cur)->next);
	*parsed_token_list = NULL;
	temp = (*cur);
	(*cur) = (*cur)->next;
	ft_lstdelone(temp, (void *)free_token);
}

//토큰의 문자열을 공백과 연산자로 파싱하는 함수
t_list	*parse_op(t_list *quote_parsed_list)
{
	t_list	*prev;
	t_list	*cur;
	t_list	*parsed_token_list;

	parsed_token_list = NULL;
	prev = quote_parsed_list;
	cur = quote_parsed_list->next;
	while (cur)
	{
		if (((t_token *)cur->content)->type != word)
		{
			split_token(&parsed_token_list, ((t_token *)cur->content)->word);
			if (parsed_token_list == NULL)
			{
				prev = cur;
				cur = cur -> next;
			}
			else
				link_list(&prev, &cur, &parsed_token_list);
			continue ;
		}
			prev = cur;
			cur = cur->next;
	}
	return (quote_parsed_list->next);
}

//토큰을 공백 기준으로 나누어 파싱하는 함수
static void	split_token(t_list **list, char *str)
{
	char	**words;
	char	**temp;
	int		idx;

	idx = -1;
	words = ft_split(str, ' ');
	temp = words;
	if (is_white_space(str[0]))
		ft_lstadd_back(list, ft_lstnew(new_token(ft_strdup(" "), undefined)));
	if (words && *words)
		parse_token(list, *(words++));
	while (words && *words)
	{
		ft_lstadd_back(list, ft_lstnew(new_token(ft_strdup(" "), undefined)));
		parse_token(list, *(words++));
	}
	if (is_white_space(str[ft_strlen(str) - 1]))
		ft_lstadd_back(list, ft_lstnew(new_token(ft_strdup(" "), undefined)));
	while (temp && temp[++idx] != NULL)
		free(temp[idx]);
	free(temp);
}

//토큰의 문자열을 연산자를 기준으로 파싱하는 함수 
static void	parse_token(t_list **temp, char *str)
{
	int			i;
	int			prev_i;

	i = -1;
	prev_i = 0;
	while (str[++i])
	{
		if (str[i] == '&' || str[i] == '<' || str[i] == '>' \
		|| str[i] == '|' || str[i] == '(' || str[i] == ')')
		{
			if ((str[i] != '(' && str[i] != ')') && str[i + 1] == str[i])
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
	token_add_back(temp, ft_substr(str, prev_i, i - prev_i + 1));
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
	token->type = get_token_type(str, ft_strlen(str));
	if (token->type == word)
		token->word = ft_strtrim(str, " ");
	else
		token->word = NULL;
	ft_lstadd_back(token_list, ft_lstnew(token));
	free(str);
}
