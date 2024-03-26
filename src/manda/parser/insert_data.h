/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:54 by taerankim         #+#    #+#             */
/*   Updated: 2024/04/02 14:32:45 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_DATA_H
# define INSERT_DATA_H

# include "parser.h"

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

# define KIND 0
# define TYPE 1

typedef struct s_grammar
{
	t_ntermi	before;
	int			after[3][2];
}				t_grammar;

/* ******************************** FUNCTION ******************************** */
t_lr_table	*insert_lr_table(void);
t_grammar	*insert_grammar(void);
void		free_words(char **dst);

#endif