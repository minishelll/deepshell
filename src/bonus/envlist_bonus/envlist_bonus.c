/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:43:28 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "envlist_bonus.h"
#include "libft.h"

char	**init_envlist(char **envp)
{
	char		**new;
	const int	size = _get_size(envp);
	int			i;

	if (size == 0)
		new = (char **)ft_malloc(sizeof(char *) * 2);
	else
		new = (char **)ft_malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (envp != NULL && envp[i] != NULL)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	if (size == 0)
	{
		new[0] = ft_strdup("");
		new[1] = NULL;
	}
	return (new);
}

char	**add_envlist(char **envlist, char *add)
{
	char		**newlist;
	const int	empty = _find_empty_space(envlist);
	const int	size = _get_size(envlist);
	int			i;

	if (empty != -1)
	{
		envlist[empty] = add;
		return (envlist);
	}
	else
	{
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
}

bool	delete_envlist(char **envlist, char *target)
{
	const int	len = ft_strlen(target);
	int			i;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (ft_strncmp(target, envlist[i], len) == 0 \
		&& envlist[i][len] == '=')
		{
			free(envlist[i]);
			envlist[i] = "";
			return (true);
		}
		i++;
	}
	return (false);
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
