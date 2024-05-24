/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_lr_table_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:13:12 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "insert_data_bonus.h"
#include "insert_lr_table_bonus.h"
#include "libft.h"

static void	parse_goto_data(t_action *table, char **data)
{
	int	i;

	i = 0;
	while (i < COL_GOTO)
	{
		if (data[i][0] != ' ')
		{
			table[i].act = grammar;
			table[i].num = ft_atoi(data[i]);
		}
		i++;
	}
}

static void	insert_goto_table(t_action **table)
{
	int			i;
	char		**data;
	const char	*go_to[ROW_STATE] = {GOTO_0, GOTO_1, GOTO_2, GOTO_3, GOTO_4 \
								, GOTO_5, GOTO_6, GOTO_7, GOTO_8, GOTO_9 \
								, GOTO_10, GOTO_11, GOTO_12, GOTO_13, GOTO_14 \
								, GOTO_15, GOTO_16, GOTO_17, GOTO_18, GOTO_19 \
								, GOTO_20, GOTO_21, GOTO_22, GOTO_23, GOTO_24 \
								, GOTO_25, GOTO_26, GOTO_27, GOTO_28, GOTO_29 \
								, GOTO_30, GOTO_31, GOTO_32, GOTO_33, GOTO_34 \
								, GOTO_35, GOTO_36, GOTO_37, GOTO_38, GOTO_39};

	i = 0;
	while (i < ROW_STATE)
	{
		data = ft_split(go_to[i], '|');
		parse_goto_data(table[i], data);
		free_words(data);
		i++;
	}
}

static void	parse_act_data(t_action *table, char **data)
{
	int	i;

	i = 0;
	while (i < COL_ACT)
	{
		if (data[i][0] == 'r')
		{
			table[i].act = reduce;
			table[i].num = ft_atoi(&data[i][1]);
		}
		else if (data[i][0] == 's')
		{
			table[i].act = shift;
			table[i].num = ft_atoi(&data[i][1]);
		}
		else if (data[i][0] == 'a')
			table[i].act = accept;
		i++;
	}
}

static void	insert_action_table(t_action **table)
{
	int			i;
	char		**data;
	const char	*action[ROW_STATE] = {ACT_0, ACT_1, ACT_2, ACT_3, ACT_4 \
								, ACT_5, ACT_6, ACT_7, ACT_8, ACT_9 \
								, ACT_10, ACT_11, ACT_12, ACT_13, ACT_14 \
								, ACT_15, ACT_16, ACT_17, ACT_18, ACT_19 \
								, ACT_20, ACT_21, ACT_22, ACT_23, ACT_24 \
								, ACT_25, ACT_26, ACT_27, ACT_28, ACT_29 \
								, ACT_30, ACT_31, ACT_32, ACT_33, ACT_34 \
								, ACT_35, ACT_36, ACT_37, ACT_38, ACT_39};

	i = 0;
	while (i < ROW_STATE)
	{
		data = ft_split(action[i], '|');
		parse_act_data(table[i], data);
		free_words(data);
		i++;
	}
}

t_lr_table	*insert_lr_table(void)
{
	t_lr_table	*new;
	int			i;

	new = (t_lr_table *)ft_malloc(sizeof(t_lr_table));
	new->action = (t_action **)ft_calloc(sizeof(t_action *), ROW_STATE + 1);
	new->go_to = (t_action **)ft_calloc(sizeof(t_action *), ROW_STATE + 1);
	i = 0;
	while (i < ROW_STATE)
	{
		new->action[i] = (t_action *)ft_calloc(sizeof(t_action), COL_ACT);
		new->go_to[i] = (t_action *)ft_calloc(sizeof(t_action), COL_GOTO);
		i++;
	}
	insert_action_table(new->action);
	insert_goto_table(new->go_to);
	return (new);
}
