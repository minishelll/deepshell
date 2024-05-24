/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:19:47 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envlist_bonus.h"
#include "libft.h"

int	_get_size(char **envlist)
{
	int	i;

	i = 0;
	while (envlist != NULL && envlist[i] != NULL)
		i++;
	return (i);
}

int	_find_empty_space(char **envlist)
{
	int	i;

	i = 0;
	while (envlist[i] != NULL)
	{
		if (envlist[i][0] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

int	_find_specific_char(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (i);
		i++;
	}
	return (NO_SPECIFIC_CHAR);
}
