/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:54 by taerankim         #+#    #+#             */
/*   Updated: 2024/03/26 14:26:31 by taerankim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_DATA_H
# define INSERT_DATA_H

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

/*
//---ACT
AND_IF
OR_IF
PIPE
LPAREN
RPAREN
cmd_word
WORD
LESS
GREAT
DGREAT
DLESS
$
//---GOTO
complete_command
and_or
pipeline
command
subshell
simple_command
cmd_suffix
redirect_list
io_redirect
io_file
filename
io_here	here_end
*/

#endif