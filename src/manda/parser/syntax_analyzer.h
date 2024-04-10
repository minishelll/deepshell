/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:31 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 19:44:44 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYZER_H
# define SYNTAX_ANALYZER_H

# include "tokenizer.h"
# include "insert_data.h"
# include "libft.h"

/* ********************************* STRUCT ********************************* */
# define LEFT 0
# define MID 1
# define RIGHT 2

typedef struct s_parse_tree
{
	t_ntermi	type;
	t_kind		child_type[3];
	void		*child[3];
}				t_parse_tree;

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

/* ********************************* DOING ********************************** */
t_parse_tree	*syntax_analyzer(t_list *input \
								, t_grammar *grammar, t_lr_table *lr_table);
t_parse_tree	*create_parse_tree(t_list **lr_stack, t_grammar grammar);
void			act_reduce(t_list **lr_stack, t_action act, t_grammar *grammar \
												, t_lr_table *lr_table);
void			act_shift(t_list **lr_stack, t_list **input, t_action act);
t_action		get_key_action(t_action **dst, int state, t_termi type);
int				get_key_goto(t_action **dst, int state, t_ntermi type);

#endif