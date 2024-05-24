/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quote_parser_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:35:12 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer_bonus.h"

static void	split_quote(t_list **list, char *cmd);
static void	join_token(t_list **node);
static void	token_add_back(t_list **token_list, char *str);

//quote를 기준으로 파싱하여 list로 반환하는 main 함수
t_list	*parse_quote(char *cmd)
{
	t_list	*list;

	list = NULL;
	split_quote(&list, cmd);
	return (list);
}

//quote를 기준으로 나누어진 문자열을 token으로 만드는 함수
static void	token_add_back(t_list **token_list, char *str)
{
	t_token	*token;

	if (*str == '\0')
	{
		free(str);
		return ;
	}
	token = (t_token *)ft_malloc(sizeof(t_token));
	if (*str == '\'' || *str == '\"')
		token->type = word;
	token->word = ft_strdup(str);
	if (*(token->word) != '\0')
		ft_lstadd_back(token_list, ft_lstnew(token));
	else
		free_token(token);
	free(str);
}

//quote구문이 연속되어 있다면 t_token을 합치는 함수
void	merge_word_nodes(t_list **list)
{
	t_list	*cur;
	t_list	*temp;

	cur = *list;
	if (cur == NULL)
		return ;
	while (cur->next)
	{
		if ((((t_token *)cur->content)->type == word) \
		&& (((t_token *)cur->next->content)->type == word))
		{
			join_token(&cur);
			continue ;
		}
		while (((t_token *)cur->next->content)->type == undefined)
		{
			temp = cur -> next;
			cur->next = cur->next->next;
			ft_lstdelone(temp, (void *)free_token);
		}
		cur = cur->next;
	}
}

//t_token 구조체의 word를 join하는 함수
void	join_token(t_list **node)
{
	t_list	*tmp;
	t_token	*cur_token;
	t_token	*next_token;
	t_token	*new_token;

	cur_token = (*node)->content;
	next_token = ((*node)->next)->content;
	new_token = (t_token *)ft_malloc(sizeof(t_token));
	new_token->word = ft_strjoin(cur_token->word, next_token->word);
	new_token->type = word;
	(*node)->content = new_token;
	free_token(cur_token);
	free_token(next_token);
	tmp = (*node)->next;
	(*node)->next = (*node)->next->next;
	free(tmp);
}

//quote를 기준으로 문자열을 잘라 리스트를 만들어 반환
void	split_quote(t_list **list, char *cmd)
{
	char	state;
	int		idx;
	int		prev_idx;

	idx = -1;
	prev_idx = 0;
	*list = ft_lstnew(NULL);
	while (cmd[++idx])
	{
		if (cmd[idx] == '\"' || cmd[idx] == '\'')
		{
			token_add_back(list, ft_substr(cmd, prev_idx, idx - prev_idx));
			state = cmd[idx];
			prev_idx = idx++;
			while (cmd[idx] != state)
			{
				if (cmd[idx++] == '\0')
					idx = prev_idx;
			}
			token_add_back(list, ft_substr(cmd, prev_idx, idx - prev_idx + 1));
			prev_idx = idx + 1;
		}
	}
	token_add_back(list, ft_substr(cmd, prev_idx, idx - prev_idx + 1));
}
