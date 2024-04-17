/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:43:28 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 20:55:18 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	_get_size(char **envlist)
{
	int	i;

	i = 0;
	while (envlist[i] != NULL)
		i++;
	return (i);
}

char	**set_envlist(char **envlist, char *add)
{
	char		**new;
	const int	size = _get_size(envlist);
	int			i;

	if (add != NULL)
		new = (char **)ft_malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (envlist[i] != NULL)
	{
		new[i] = envlist[i];
		i++;
	}
	new[i] = add;
	new[i + 1] = NULL;
	if (add != NULL)
		free(envlist);
	return (new);
}

char	**delete_envlist(char **org, char *target)
{
	char		**new;
	const int	size = _get_size(org);
	const int	len = ft_strlen(target);
	int			loca;
	int			i;

	loca = 0;
	while (org[loca] != NULL)
	{
		if (ft_strncmp(target, org[loca], len) == 0 && org[loca][len] == '=')
		{
			new = (char **)ft_malloc(sizeof(char *) * size);
			i = -1;
			while (++i < loca)
				new[i] = org[i];
			while (++i < size)
				new[i - 1] = org[i];
			new[i] = NULL;
		}
		loca++;
	}
}
