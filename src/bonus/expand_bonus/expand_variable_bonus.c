/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:12:36 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand_bonus.h"

static char	*_replace_to_value(char *word, int *pivot, char *value)
{
	char		*result;
	const int	value_size = ft_strlen(value);
	int			total;
	int			i[3];

	total = pivot[0] + value_size + ft_strlen(word) - pivot[1] + 1;
	result = (char *)ft_calloc(sizeof(char), total);
	i[0] = -1;
	while (++i[0] < pivot[0])
		result[i[0]] = word[i[0]];
	i[1] = -1;
	while (++i[1] < value_size)
		result[i[0] + i[1]] = value[i[1]];
	i[2] = 0;
	while (total != 1 && word[pivot[1] + i[2]] != '\0')
	{
		result[i[0] + i[1] + i[2]] = word[pivot[1] + i[2]];
		i[2]++;
	}
	free(word);
	return (result);
}

static int	_handle_dollar_sign(char **word, int *pivot, t_env *env)
{
	char	*name;
	char	*value;
	int		value_len;

	name = ft_substr(*word, pivot[0] + 1, pivot[1] - pivot[0] - 1);
	if (name[0] == '?')
		value = ft_itoa(env->exit_code);
	else
	{
		value = find_env(env->envlist, name);
		if (value == NULL)
			value = "";
	}
	*word = _replace_to_value(*word, pivot, value);
	value_len = ft_strlen(value);
	if (name[0] == '?')
		free(value);
	free(name);
	return (value_len);
}

static t_ex_status	_set_two_pivot(char *word, int *pivot, int curr)
{
	char	*dollar;
	int		specific;

	dollar = ft_strchr(&word[curr], '$');
	if (dollar == NULL)
		return (not_more);
	pivot[0] = dollar - word;
	specific = _find_specific_char(&word[pivot[0] + 1]);
	if (word[pivot[0] + 1] == '\0' \
	|| (specific == 0 && word[pivot[0] + 1] != '?'))
		return (keep_going);
	if (specific == NO_SPECIFIC_CHAR)
	{
		pivot[1] = ft_strlen(word);
		return (finish);
	}
	pivot[1] = pivot[0] + specific + 1;
	if (word[pivot[1]] == '?' && pivot[1] - pivot[0] == 1)
		pivot[1] += 1;
	return (find);
}

void	expand_variable(t_token *token, t_env *env)
{
	t_ex_status	status;
	int			pivot[2];
	int			i;

	pivot[1] = 0;
	i = -1;
	while (token->word[i + 1] != '\0')
	{
		i++;
		status = _set_two_pivot(token->word, pivot, i);
		if (status == find || status == finish)
			i += _handle_dollar_sign(&token->word, pivot, env) - 1;
		if (status == not_more || status == finish)
			break ;
	}
}

void	_remove_quote(t_token *token)
{
	const int	orglen = ft_strlen(token->word);
	char		*tmp;

	tmp = token->word;
	token->word = ft_substr(token->word, 1, orglen - 2);
	free(tmp);
}
