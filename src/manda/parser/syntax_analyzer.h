/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:31 by taerakim          #+#    #+#             */
/*   Updated: 2024/03/29 11:57:39 by taerankim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYSNTAX_ANALYZER_H
# define SYSNTAX_ANALYZER_H

#include "parser.h"
#include "insert_data.h"
#include "libft.h"

typedef struct s_stack
{
	t_kind	kind;
	int		state;
	void	*ptr;
}	t_stack;

/* ******************************** LR_STACK ******************************** */
t_stack			*pop(t_list **top);
void			push(t_list **top, t_kind kind, void *content);
t_stack			*create_state(int state_num);
int				get_state(t_list *top);

/* ********************************* DOING ********************************* */
t_parse_tree	*lexer(t_list *input);
t_parse_tree	*create_parse_tree(t_list **lr_stack, t_grammar grammar);
void			reduce(t_list **lr_stack, t_grammar *grammar \
					, t_action act, t_lr_table *lr_table);
void			shift(t_list **lr_stack, t_list **input, t_action act);
t_action		get_key_action(t_action **dst, int state, t_termi type);
int				get_key_goto(t_action **dst, int state, t_ntermi type);

#endif