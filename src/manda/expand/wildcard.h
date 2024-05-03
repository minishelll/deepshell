/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:28:44 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/03 20:28:58 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "libft.h"
# include <stdbool.h>

/* ******************************** LITERAL ********************************* */

/* ********************************* STRUCT ********************************* */

/* ******************************** FUNCTION ******************************** */
bool	check_word(char *str1, char *str2);
// bool	match_and_collect(char *word, t_list *dir_lst, t_list **matched);
// bool	match_wildcard(t_list *token_prev, t_list **token_cur, t_list *dir_lst);
// void	process_wildcard_tokens(t_list *token, t_list *dir_lst);
/* wildcard_utils */
void	attach_head_node(t_list **token);
t_list	*get_dir_lst(void);
void	wildcard_add_back(t_list **token_list, char *str);
bool	**make_word_table(char *str1, char *str2);
bool	match_and_collect(char *word, t_list *dir_lst, t_list **matched, bool flag);
void	expand_wildcard(t_list **head, t_list **curr);
#endif