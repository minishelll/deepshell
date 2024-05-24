/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:01:48 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_BONUS_H
# define TOKENIZER_BONUS_H

# include "input_type_bonus.h"
# include "libft.h"

/* ******************************** LITERAL ********************************* */
# define S_PIPE "|"
# define S_AND_IF "&&"
# define S_OR_IF "||"
# define S_LESS "<"
# define S_DLESS "<<"
# define S_GREAT ">"
# define S_DGREAT ">>"
# define S_LPAREN "("
# define S_RPAREN ")"

/* ********************************* STRUCT ********************************* */
typedef struct s_token
{
	t_termi	type;
	char	*word;
}			t_token;

/* ******************************** FUNCTION ******************************** */
t_list	*tokenizer(char *command);
t_list	*parse_quote(char *command);
t_list	*parse_op(t_list *quote_parsed_list);
void	merge_word_nodes(t_list **list);
/* tokenizer_utils */
t_termi	get_token_type(char *str, int len);
void	add_end_token(t_list *parsed_list);
void	free_token(void *token);
t_token	*new_token(char *word, t_termi type);
int		is_white_space(char c);

#endif