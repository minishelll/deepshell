/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:20:26 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/27 23:13:25 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"


bool	expand_redirection(t_list *redilist)
{

}

int	_count_more_space(char *cmd)
{
	int	split;

	//ㅇㅣ거 parser가 진짜 빈문자열 넘겨주면 편한데 ㅋ


}

char	**expand_command(char **cmds)
{
	char	**new;
	int		split;
	int		i;

	split = 0;
	i = 0;
	while (cmds[i] != NULL)
	{
		i++;
	}
	if (split == 0)
		return (cmds);
	new = (char **)ft_calloc(sizeof(char) * (i + split + 1));
	return (new);
}