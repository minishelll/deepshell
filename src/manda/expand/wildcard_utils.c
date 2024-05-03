/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:21:10 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/03 21:50:03 by sehwjang         ###   ########.fr       */
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

void	attach_head_node(t_list **token)
{
	t_list	*head;

	head = ft_lstnew(NULL);
	head->next = *token;
	token = &head;
}

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
	{
		printf("%s를 열 수 없습니다.", cur_path);
		free(cur_path);
		exit(1);
	}
	//entry = readdir(dp);
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(entry->d_name)));
	}
	closedir(dp);
	free(cur_path);
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

bool	match_and_collect(char *word, t_list *dir_lst, t_list **matched, bool dot_flag)
{
	t_list	*dir_cur;
	bool	flag;

	dir_cur = dir_lst;
	flag = false;
	while (dir_cur)
	{
		if (!dot_flag && *word == '.')
		{
			dir_cur = dir_cur->next;
			continue;
		}
		if (check_word(word, (char *)(dir_cur->content)))
		{
			wildcard_add_back(matched, dir_cur->content);
			flag = true;
			break ;
		}
		dir_cur = dir_cur->next;
	}
	dir_cur = dir_cur->next;
	while (dir_cur)
	{
		if (dot_flag && *word == '.')
		{
			dir_cur = dir_cur->next;
			continue;
		}
		if (check_word(word, (char *)(dir_cur->content)))
		{
			dummy_add_back(matched);
			wildcard_add_back(matched, dir_cur->content);
			flag = true;
		}
		dir_cur = dir_cur->next;
	}
	return (flag);
}
