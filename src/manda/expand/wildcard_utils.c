/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:21:10 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/08 17:39:04 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "wildcard.h"

#define PATH_MAX	4096

t_list	*get_dir_lst(void)
{
	DIR				*dp;
	t_list			*lst;
	struct dirent	*entry;
	char			*cur_path;

	lst = NULL;
	cur_path = getcwd(NULL, PATH_MAX);
	if (cur_path == NULL)
		exit(1);
	dp = opendir(cur_path);
	if (dp == NULL)
		exit(1);
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dp);
	free(cur_path);
	ft_lstsort(&lst, &ft_strncmp);
	return (lst);
}

//토큰의 메모리를 할당하고, 타입과 문자열을 초기화하는 함수
void	wildcard_add_back(t_list **token_list, char *str)
{
	t_token		*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	token->word = ft_strdup(str);
	token->type = word;
	ft_lstadd_back(token_list, ft_lstnew(token));
}

bool	**make_word_table(char *str1, char *str2)
{
	const int	len1 = ft_strlen(str1);
	const int	len2 = ft_strlen(str2);
	bool		**arr;
	int			i;
	int			j;

	i = -1;
	arr = (bool **)ft_calloc(len1 + 1, sizeof(bool *));
	while (++i < len1 + 1)
		arr[i] = (bool *)ft_calloc(len2 + 1, sizeof(bool));
	i = 1;
	while (i <= len1)
	{
		j = 1;
		while (j <= len2)
		{
			if (str1[i - 1] == '*' || str1[i - 1] == str2[j - 1])
				arr[i][j] = true;
			j++;
		}
		i++;
	}
	return (arr);
}

void	dummy_add_back(t_list **token_list)
{
	t_token		*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	token->word = ft_strdup(" ");
	token->type = undefined;
	ft_lstadd_back(token_list, ft_lstnew(token));
}

void ft_lstswap(t_list *a, t_list *b)
{
    void *temp = a->content;
    a->content = b->content;
    b->content = temp;
}

void ft_lstsort(t_list **lst, int (*sort)(const char *, const char *, size_t n))
{
	bool	swapped;
	t_list	*ptr;
	t_list	*end_ptr;

	swapped = true;
	end_ptr = NULL;
	if (lst == NULL || *lst == NULL || (*lst)->next == NULL)
		return ;
	while (swapped != false)
	{
		swapped = false;
		ptr = *lst;
		while (ptr->next != end_ptr)
		{
			if (sort(ptr->content, ptr->next->content, PATH_MAX) > 0)
			{
				ft_lstswap(ptr, ptr->next);
				swapped = true;
			}
			ptr = ptr->next;
		}
		end_ptr = ptr;
	}
}
