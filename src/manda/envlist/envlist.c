/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:43:28 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 13:45:44 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "libft.h"

static int	_get_size(char **envlist)
{
	int	i;

	i = 0;
	while (envlist[i] != NULL)
		i++;
	return (i);
}

char	**init_envlist(char **envp)
{
	char		**new;
	const int	size = _get_size(envp);
	int			i;

	new = (char **)ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**add_envlist(char **envlist, char *add)
{
	char		**newlist;
	const int	size = _get_size(envlist);
	int			i;

	newlist = (char **)ft_malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (envlist[i] != NULL)
	{
		newlist[i] = envlist[i];
		i++;
	}
	newlist[i] = add;
	newlist[i + 1] = NULL;
	free(envlist);
	return (newlist);
}

char	**delete_envlist(char **envlist, char *target)
{
	char		**newlist;
	const int	size = _get_size(envlist);
	const int	len = ft_strlen(target);
	int			find;
	int			i;

	find = 0;
	while (envlist[find] != NULL)
	{
		if (ft_strncmp(target, envlist[find], len) == 0 \
		&& envlist[find][len] == '=')
		{
			newlist = (char **)ft_malloc(sizeof(char *) * size);
			i = -1;
			while (++i < find)
				newlist[i] = envlist[i];
			while (++i < size)
				newlist[i - 1] = envlist[i];
			newlist[i] = NULL;
		}
		find++;
	}
	return (NULL);
}

bool	update_envlist(char **envlist, char *target, char *data)
{
	char		*tmp;
	const int	len = ft_strlen(target);
	int			i;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (ft_strncmp(target, envlist[i], len) == 0 \
		&& envlist[i][len] == '=')
		{
			free(envlist[i]);
			tmp = ft_strjoin(target, "=");
			envlist[i] = ft_strjoin(tmp, data);
			free(tmp);
			return (true);
		}
		i++;
	}
	return (false);
}

char	*find_env(char **envlist, char *name)
{
	const int	len = ft_strlen(name);
	int			i;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (ft_strncmp(name, envlist[i], len) == 0 \
		&& envlist[i][len] == '=')
			return (&envlist[i][len + 1]);
		i++;
	}
	return (NULL);
}
