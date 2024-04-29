/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:04:51 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/29 23:28:18 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "wildcard.h"

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

void	process_wildcard_tokens(t_list *token, t_list *dir_lst)
{
	t_list	*token_prev;
	t_list	*token_cur;

	token_prev = token;
	token_cur = token_prev->next;
	while (token_cur)
	{
		if (!match_wildcard(token_prev, &token_cur, dir_lst))
			token_prev = token_cur;
		token_cur = token_cur->next;
	}
}

bool	match_wildcard(t_list *token_prev, t_list **token_cur, t_list *dir_lst)
{
	char	*word;
	char	*temp;
	t_list	*matched;
	t_list	*next;

	word = ((t_token *)(*token_cur)->content)->word;
	matched = NULL;
	if (word == NULL)
		return (false);
	temp = ft_strchr(word, '*');
	if (temp)
	{
		if (match_and_collect(word, dir_lst, &matched))
		{
			next = (*token_cur)->next;
			token_prev->next = matched;
			ft_lstlast(matched)->next = next;
			ft_lstdelone(*token_cur, (void *)free_token);
			*token_cur = next;
			return (true);
		}
	}
	free(temp);
	return (false);
}

t_list	*wildcard(t_list *token)
{
	t_list	*dir_lst;

	attach_head_node(&token);
	dir_lst = get_dir_lst();
	process_wildcard_tokens(token, dir_lst);
	ft_lstclear(&dir_lst, free);
	return (token);
}
