/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:12:36 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/03 14:59:13 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "expand.h"

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
		value = find_env(env->envlist, name);
	*word = _replace_to_value(*word, pivot, value);
	value_len = ft_strlen(value);
	if (name[0] == '?')
		free(value);
	free(name);
	return (value_len);
}

static t_ex_status	_set_two_pivot(char* word, int *pivot, int curr)
{
	int	specific;

	pivot[0] = ft_strchr(&word[curr], '$') - word;
	if (pivot[0] < 0)
		return (not_more);
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
	if (word[pivot[1]] == '?')
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
	while (token->word[i + 1] != '\0')//word자체가 바뀌면서 segfault
	{
		i++;
		status = _set_two_pivot(token->word, pivot, i);
		if (status == find || status == finish)
			i += _handle_dollar_sign(&token->word, pivot, env);
		if (status == not_more || status == finish)
			break ;
	}
}
