/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:28:44 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_BONUS_H
# define WILDCARD_BONUS_H

# include "libft.h"
# include <stdbool.h>

# define PATH_MAX 4096

/* ******************************** FUNCTION ******************************** */
bool	check_word(char *str1, char *str2);
/* wildcard_utils */
t_list	*get_dir_lst(void);
void	wildcard_add_back(t_list **token_list, char *str, bool isdummy);
bool	**make_word_table(char *str1, char *str2);
void	match_word(char *word, t_list *dir_lst, t_list **matched, bool flag);
void	expand_wildcard(t_list **head, t_list **curr);
void	ft_lstsort(t_list **lst, \
					int (*sort)(const char *, const char *, size_t n));
void	ft_lstswap(t_list *a, t_list *b);

#endif