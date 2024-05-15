/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:04:51 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/14 15:13:36 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "wildcard.h"

void	match_word(char *word, t_list *dir_lst, t_list **matched, bool dot_flag)
{
	t_list	*dir_cur;

	dir_cur = dir_lst;
	while (dir_cur)
	{
		if (!(!dot_flag && *(char *)(dir_cur->content) == '.') && \
			check_word(word, (char *)(dir_cur->content)))
		{
			wildcard_add_back(matched, dir_cur->content, false);
			break ;
		}
		dir_cur = dir_cur->next;
	}
	if (dir_cur == NULL)
		return ;
	while (dir_cur ->next)
	{
		dir_cur = dir_cur->next;
		if (!(!dot_flag && *(char *)(dir_cur->content) == '.') && \
			check_word(word, (char *)(dir_cur->content)))
		{
			wildcard_add_back(matched, NULL, true);
			wildcard_add_back(matched, dir_cur->content, false);
		}
	}
}

bool	check_char(char *str1, int len1, int len2, bool **arr)
{
	if (len1 == 1 && len2 == 1 && arr[len1][len2] == true)
		return (true);
	if (arr[len1][len2] != true)
		return (false);
	if (len1 == 1)
		return (check_char(str1, len1, len2 - 1, arr));
	return (check_char(str1, len1 -1, len2 -1, arr) || \
	((str1[len1 - 1] == '*') && check_char(str1, len1, len2 - 1, arr)) || \
	((str1[len1 - 1] == '*') && check_char(str1, len1 - 1, len2, arr)));
}

bool	check_word(char *str1, char *str2)
{
	const int	len1 = ft_strlen(str1);
	const int	len2 = ft_strlen(str2);
	bool		result;
	bool		**arr;
	int			idx;

	idx = -1;
	arr = make_word_table(str1, str2);
	result = check_char(str1, len1, len2, arr);
	while (++idx < len1 + 1)
		free(arr[idx]);
	free(arr);
	return (result);
}

t_list	*wildcard(t_token *token)
{
	t_list	*dir_lst;
	t_list	*ret_lst;

	ret_lst = NULL;
	dir_lst = get_dir_lst();
	if (*(token->word) == '.')
		match_word(token->word, dir_lst, &ret_lst, true);
	else
		match_word(token->word, dir_lst, &ret_lst, false);
	if (ret_lst == NULL)
		ft_lstadd_back(&ret_lst, ft_lstnew(token));
	else
		free_token(token);
	ft_lstclear(&dir_lst, free);
	return (ret_lst);
}

void	expand_wildcard(t_list **head, t_list **curr)
{
	t_list	*tmpprev;
	t_list	*tmpnext;
	t_list	*result;

	if (*head == *curr)
		tmpprev = NULL;
	else
	{
		tmpprev = *head;
		while (tmpprev->next != *curr)
			tmpprev = tmpprev->next;
	}
	tmpnext = (*curr)->next;
	result = wildcard((*curr)->content);
	free(*curr);
	if (tmpprev == NULL)
		*head = result;
	else
		tmpprev->next = result;
	*curr = ft_lstlast(result);
	(*curr)->next = tmpnext;
}
