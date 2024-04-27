/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:01:48 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/28 04:51:25 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include "libft.h"
# include "input_type.h"

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
void	free_token(t_token *token);
t_token	*new_token(char *word, t_termi type);
int		is_white_space(char c);
#endif