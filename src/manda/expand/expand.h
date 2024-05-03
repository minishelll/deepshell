/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/03 14:02:38 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "tokenizer.h"
# include "syntax_tree.h"
# include "envlist.h"
# include "libft.h"

typedef enum e_ex_status
{
	keep_going,
	not_more,
	finish,
	find
}	t_ex_status;

typedef enum e_quote
{
	q_not,
	q_single,
	q_double
}	t_quote;

int		expand(t_syntax_tree *command, t_env *env);
t_list	*expand_one_word(char *str, t_env *env);
void	expand_variable(t_token *token, t_env *env);
void	_set_type_word(t_list *token);

#endif