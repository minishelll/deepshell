/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:57:49 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/14 11:39:47 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_words(char **dst)
{
	int	i;

	if (dst == NULL)
		return ;
	i = 0;
	while (dst[i] != NULL)
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}
