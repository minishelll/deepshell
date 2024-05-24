/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:08:31 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_ANALYZER_BONUS_H
# define SYNTAX_ANALYZER_BONUS_H

# include "minishell_bonus.h"
# include "tokenizer_bonus.h"
# include "insert_data_bonus.h"
# include "libft.h"

/* ********************************* STRUCT ********************************* */
# define LEFT 0
# define MID 1
# define RIGHT 2

typedef enum e_status
{
	none_status,
	complete,
	syntax_error,
}	t_status;

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

# define SYNTAX_ERRNUM 258

/* ******************************** LR_STACK ******************************** */
t_stack			*pop(t_list **top);
void			push(t_list **top, t_kind kind, void *content);
t_stack			*create_state(int state_num);
int				get_state(t_list *top);

/* ********************************* DOING ********************************** */
t_parse_tree	*syntax_analyzer(t_data *data, t_list *input);
/* table */
void			act_reduce(t_list **lr_stack, t_action act, t_grammar *grammar \
												, t_lr_table *lr_table);
void			act_shift(t_list **lr_stack, t_list **input, t_action act);
t_action		get_key_action(t_action **dst, int state, t_termi type);
int				get_key_goto(t_action **dst, int state, t_ntermi type);
/* util */
t_parse_tree	*create_parse_tree(t_list **lr_stack, t_grammar grammar);
void			free_parse_tree(t_parse_tree *parse_tree, void (*del)(void *));
void			free_lr_stack(t_list *lr_stack);

#endif