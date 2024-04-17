/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:15:19 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 13:26:13 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <unistd.h>

void	close_rest_pipe(int *pipe_fd, int cnt)
{
	const int	use_pipe = cnt * 2 - 3;
	int			i;

	i = 0;
	if (cnt != PIPE_ALL)
	{
		while (i < use_pipe)
		{
			close(pipe_fd[i]);
			i++;
		}
		i += 2;
	}
	if (pipe_fd[use_pipe + 1] != PIPE_ALL)
	{
		while (pipe_fd[i] != PIPE_END)
		{
			close(pipe_fd[i]);
			i++;
		}
	}
}

void	close_redirect_file(int *redi)
{
	if (redi[INFILE] != INIT)
		close(redi[INFILE]);
	if (redi[OUTFILE] != INIT)
		close(redi[OUTFILE]);
}
