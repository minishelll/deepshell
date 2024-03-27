/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_grammar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerankim <taerankim@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:13:12 by taerankim         #+#    #+#             */
/*   Updated: 2024/03/27 13:06:03 by taerankim        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "insert_data.h"
#include "grammar.h"
#include "libft.h"

int	get_nontermi_type(char *data)
{
	int			i;
	const char	*non_termi[14] = {"complete_command", "and_or", "pipeline" \
				, "command", "subshell", "simple_command", "cmd_word" \
				, "cmd_suffix" , "redirect_list", "io_redirect", "io_file" \
				, "filename", "io_here", "here_end"};

	i = 0;
	while (i < 14)
	{
		if (ft_strncmp(data, non_termi[i], 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	get_termi_type(char *data)
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

void	parse_data(t_grammar *grammar, char **data)
{
	int	i;

	i = 0;
	while (data[i] != NULL)
	{
		if ('A' <= data[i][0] && data[i][0] <= 'Z')
		{
			grammar->kind[i] = terminal;
			grammar->type[i] = get_termi_type(data[i]);
		}
		else if ('a' <= data[i][0] && data[i][0] <= 'z')
		{
			grammar->kind[i] = non_terminal;
			grammar->type[i] = get_nontermi_type(data[i]);
		}
		i++;
	}
	while (i < 3)
	{
		grammar->kind[i] = none;
		grammar->type[i] = -1;
		i++;
	}
}

t_grammar	*insert_grammar(void)
{
	const char	*grammar[GRAMMAR] = {GRAMMAR_0, GRAMMAR_1, GRAMMAR_2 \
				, GRAMMAR_3 , GRAMMAR_4, GRAMMAR_5, GRAMMAR_6, GRAMMAR_7 \
				, GRAMMAR_8 , GRAMMAR_9, GRAMMAR_10, GRAMMAR_11, GRAMMAR_12 \
				, GRAMMAR_13, GRAMMAR_14, GRAMMAR_15, GRAMMAR_16, GRAMMAR_17 \
				, GRAMMAR_18, GRAMMAR_19, GRAMMAR_20, GRAMMAR_21, GRAMMAR_22 \
				, GRAMMAR_23, GRAMMAR_24, GRAMMAR_25, GRAMMAR_26, GRAMMAR_27 \
				, GRAMMAR_28, GRAMMAR_29};
	t_grammar	*new;
	char		**data;
	int			i;

	new = (t_grammar *)ft_calloc(sizeof(t_grammar), GRAMMAR);
	i = 0;
	while (i < GRAMMAR)
	{
		data = ft_split(ft_strchr(grammar[i], '>') + 2, ' ');
		parse_data(&new[i], data);
		free_words(data);
		i++;
	}
	return (new);
}
