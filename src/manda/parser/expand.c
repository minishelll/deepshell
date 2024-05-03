/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:39:13 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/10 19:40:35 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

static void	_split_after_expand(t_list *token)
{
	t_list	*orgnext;
	t_list	*curr;
	char	**split;
	int		i;

	if (ft_strchr(((t_token *)token->content)->word, ' ') == NULL)
		return ;
	split = ft_split(((t_token *)token->content)->word, ' ');
	free(((t_token *)token->content)->word);
	((t_token *)token->content)->word = split[0];
	orgnext = token->next;
	curr = token;
	i = 1;
	while (split[i + 1] != NULL)
	{
		curr->next = ft_lstnew(new_token(ft_strdup(""), undefined));
		curr->next->next = ft_lstnew(new_token(split[i], word));
		curr = curr->next->next;
		i++;
	}
	curr->next = ft_lstnew(new_token(ft_strdup(""), undefined));
	curr->next->next = ft_lstnew(new_token(split[i], word));
	curr->next->next->next = orgnext;
	free(split);
}

static char	*_replace_to_value(char *word, int *idx, char *value)
{
	char		*result;
	const int	value_size = ft_strlen(value);
	int			total;
	int			i;
	int			k;

	i = -1;
	total = idx[0] + value_size + ft_strlen(word) - idx[1] + 1;
	result = (char *)ft_calloc(sizeof(char), total);
	while (++i < idx[0])
		result[i] = word[i];
	k = -1;
	while (++k < value_size)
		result[i + k] = value[k];
	while (total != 1 && word[idx[1]] != '\0')
	{
		result[i + k] = word[idx[1] + i];
		i++;
	}
	free(word);
	return (result);
}

static char	*_handle_dollar_sign(char *word, int *pivot, t_env *env)
{
	char	*result;
	char	*name;
	char	*value;
	
	name = ft_substr(word, pivot[0] + 1, pivot[1] - pivot[0]);
	if (ft_strncmp("?", name, 2) == 0)
		value = ft_itoa(env->exit_code);
	else
		value = find_env(env->envlist, name);
		result = _replace_to_value(word, pivot, value);
	if (ft_strncmp("?", name, 2) == 0)
		free(value);
	free(name);
	return (result);
}

static void	expand_one_token(t_list *token, char *word, t_env *env)
{
	int	pivot[2];
	int	i;

	pivot[1] = 0;
	i = -1;
	while (word[i + 1] != '\0'/* && ft_strchr(&word[i + 1], '$') != NULL*/)
	{
		i++;
		pivot[0] = ft_strchr(&word[pivot[1]], '$') - word;// strchr NULL일때 //pivot
		if (pivot[0] < 0)
		{
			pivot[0] = i;
			pivot[1] = ft_strlen(word);
			break ;
		}
		pivot[1] = _find_specific_char(&word[pivot[0] + 1]);
		if (pivot[1] == NO_SPECIFIC_CHAR || word[pivot[1] + 1] == '?')
			pivot[1] = ft_strlen(word);
		else
			pivot[1] += 1;
		if (pivot[1] - pivot[0] != 1)//pivot이 셋팅됐다는 점
		{
			word = _handle_dollar_sign(word, pivot, env);
			break ;
		}
		if (pivot[1] - pivot[0] == 1)
			continue ;
		word = _handle_dollar_sign(word, pivot, env);
	}
	((t_token *)token->content)->word = word;
	_split_after_expand(token);
}

void	expand(t_list *token, t_env *env)
{
	t_token	*cur;

	while (((t_token *)token->content)->type != dollar_sign)
	{
		cur = (t_token *)token->content;
		if (cur->type == word)
		{
			if (cur->word[0] == '\'' \
			&& cur->word[ft_strlen(cur->word) - 1] == '\'')
				cur->word = ft_substr(cur->word, 1, ft_strlen(cur->word) - 2);
			else if (cur->word[0] == '"' \
			&& cur->word[ft_strlen(cur->word) - 1] == '"')
			{
				cur->word = ft_substr(cur->word, 1, ft_strlen(cur->word) - 2);
				if (ft_strchr(cur->word, '$') != NULL)
					expand_one_token(token, cur->word, env);
			}
			else if (ft_strchr(cur->word, '$') != NULL)
				expand_one_token(token, cur->word, env);
		}
		token = token->next;
	}
}
