/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:54 by taerankim         #+#    #+#             */
/*   Updated: 2024/03/27 13:05:01 by taerankim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_DATA_H
# define INSERT_DATA_H

/* ******************************** LR_TABLE ******************************** */
# define ROW_STATE 40
# define COL_ACT 11
# define COL_GOTO 14

typedef enum e_act_type
{
	init = 0,
	shift,
	reduce,
	accept,
	grammar
}	t_act_type;

typedef struct s_action
{
	t_act_type	act;
	int			num;
}				t_action;

typedef struct s_lr_table
{
	t_action	**action;
	t_action	**go_to;
}				t_lr_table;

/* ******************************** GRAMMAR ********************************* */
# define GRAMMAR 30

typedef enum e_kind
{
	none = -1,
	terminal,
	non_terminal
}	t_kind;

typedef struct s_grammar
{
	t_kind	kind[3];
	int		type[3];
}			t_grammar;

/* ******************************* FUNCTIONS ******************************** */
t_lr_table	*insert_lr_table(void);
t_grammar	*insert_grammar(void);
void	free_words(char **dst);

#endif