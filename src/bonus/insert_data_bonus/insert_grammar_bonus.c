/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_grammar_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:13:12 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "insert_data_bonus.h"
#include "insert_grammar_bonus.h"
#include "libft.h"

static t_ntermi	get_nontermi_type(char *data)
{
	int			i;
	const char	*non_termi[14] = {"complete_command", "and_or", "pipeline" \
				, "command", "subshell", "simple_command", "cmd_word" \
				, "cmd_suffix", "redirect_list", "io_redirect", "io_file" \
				, "filename", "io_here", "here_end"};

	i = 0;
	while (i < 14)
	{
		if (ft_strncmp(data, non_termi[i], 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static t_termi	get_termi_type(char *data)
{
	int			i;
	const char	*termi[10] = {"AND_IF", "OR_IF", "PIPE", "LPAREN", "RPAREN" \
						, "WORD", "LESS", "GREAT", "DGREAT", "DLESS"};

	i = 0;
	while (i < 10)
	{
		if (ft_strncmp(data, termi[i], 2) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static void	parse_data(t_grammar *grammar, char **data)
{
	int	i;

	i = 0;
	while (data[i] != NULL)
	{
		if ('A' <= data[i][0] && data[i][0] <= 'Z')
		{
			grammar->after[i][KIND] = terminal;
			grammar->after[i][TYPE] = get_termi_type(data[i]);
		}
		else if ('a' <= data[i][0] && data[i][0] <= 'z')
		{
			grammar->after[i][KIND] = non_terminal;
			grammar->after[i][TYPE] = get_nontermi_type(data[i]);
		}
		i++;
	}
	while (i < 3)
	{
		grammar->after[i][KIND] = none;
		i++;
	}
}

t_grammar	*insert_grammar(void)
{
	const char	*grammar[GRAMMAR] = {GRAMMAR_0, GRAMMAR_1, GRAMMAR_2 \
				, GRAMMAR_3, GRAMMAR_4, GRAMMAR_5, GRAMMAR_6, GRAMMAR_7 \
				, GRAMMAR_8, GRAMMAR_9, GRAMMAR_10, GRAMMAR_11, GRAMMAR_12 \
				, GRAMMAR_13, GRAMMAR_14, GRAMMAR_15, GRAMMAR_16, GRAMMAR_17 \
				, GRAMMAR_18, GRAMMAR_19, GRAMMAR_20, GRAMMAR_21, GRAMMAR_22 \
				, GRAMMAR_23, GRAMMAR_24, GRAMMAR_25, GRAMMAR_26, GRAMMAR_27 \
				, GRAMMAR_28, GRAMMAR_29};
	t_grammar	*new;
	char		**after;
	int			i;

	new = (t_grammar *)ft_calloc(sizeof(t_grammar), GRAMMAR);
	i = 0;
	while (i < GRAMMAR)
	{
		new[i].before = get_nontermi_type((char *)grammar[i]);
		after = ft_split(ft_strchr(grammar[i], '>') + 2, ' ');
		parse_data(&new[i], after);
		free_words(after);
		i++;
	}
	return (new);
}
