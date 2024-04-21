/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:04:51 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/21 21:28:06 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "tokenizer.h"

# define PATH_MAX	4096

bool arr[25001][25001];

bool	check_char(char *str1, char *str2, int len1, int len2)
{
	if (len1 == 1 && len2 == 1 && arr[len1][len2] == true)
		return (true);
	if (arr[len1][len2] != true)
		return (false);
	return (check_char(str1, str2, len1 -1, len2 -1) || \
	((str1[len1 - 1] == '*') && check_char(str1, str2, len1, len2 - 1)) || \
	((str1[len1 - 1] == '*') && check_char(str1, str2, len1 - 1, len2)));
}

bool	check_word(char *str1, char *str2)
{
	const int	len1 = ft_strlen(str1);
	const int	len2 = ft_strlen(str2);

	for (int i = 1; i <= len1; i++){
		for (int j = 1; j <= len2; j++){
			if (str1[i-1] == '*' || str1[i - 1] == str2[j - 1])
				arr[i][j] = true;
		}
	}
	return (check_char(str1, str2, len1, len2));
}

// int	main(void)
// {
// 	char	*str1;
// 	char	*str2;
// 	int		len1;
// 	int		len2;

// 	str1 = "*s*g*";
// 	str2 = "asdfg";
// 	if (check_word(str1, str2))
// 		printf("OK");
// 	else
// 		printf("KO");
// }

t_list	*get_dir_lst(void)
{
	DIR				*dp;
	t_list			*lst;
	struct dirent	*entry;
	char			cur_path[PATH_MAX];

	lst = NULL;
	if (getcwd(cur_path, PATH_MAX) == NULL)
		exit(1);
	//printf("Current Directory : %s\n", cur_path);
	dp = opendir(cur_path);
	if (dp == NULL)
	{
		printf("%s를 열 수 없습니다.",cur_path);
		exit(1);
	}
	entry = readdir(dp);
	while (entry != NULL)
	{
		ft_lstadd_back(&lst, ft_lstnew(entry->d_name));
		//printf("%s\n", entry->d_name);
		entry = readdir(dp);
	}
	return (lst);
}

void	wildcard(t_list **token)
{
	char	*word;
	t_list	*dir_lst;
	t_list	*token_next;
	t_list	*dir_cur;
	t_list	*matched;
	t_list	*return_token;

	return_token = *token;
	dir_lst = get_dir_lst();
	dir_cur = dir_lst;
	matched = NULL;
	while (*token)
	{
		word = ((t_token *)(*token)->content)->word;
		if (ft_strchr(word, '*'))
		{
			while (dir_cur)
			{
				if (check_word(word, dir_cur->content))
					ft_lstadd_back(&matched, ft_lstnew(dir_cur->content));
				dir_cur = dir_cur->next;
			}
		}
		token_next = (*token)->next;
		(*token)->next = matched;
		ft_lstadd_back(&return_token, token_next);
		*token = token_next;
	}
	*token = return_token;
}
