/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:15:19 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/27 10:31:54 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "execute.h"

int	*handle_pipe(t_pipe *pipeinfo, t_pipe_order order)
{
	int	use_pipe_idx;
	int	i;

	if (order == start)
		use_pipe_idx = pipeinfo->cnt * 2 - 1;
	else if (order == middle)
		use_pipe_idx = pipeinfo->cnt * 2 - 3;
	else
		use_pipe_idx = 0;
	i = 0;
	while (i < use_pipe_idx)
	{
		close(pipeinfo->pipelist[i]);
		i++;
	}
	if (order == start || order == end)
		i += 1;
	else if (order == middle)
		i += 2;
	while (pipeinfo->pipelist[i] != PIPE_END)
	{
		close(pipeinfo->pipelist[i]);
		i++;
	}
	return (&pipeinfo->pipelist[use_pipe_idx]);
}

void	close_redirect_file(int *redi)
{
	if (redi[INFILE] != INIT)
		close(redi[INFILE]);
	if (redi[OUTFILE] != INIT)
		close(redi[OUTFILE]);
}

int	wait_process(int last_child, t_pipe *pipeinfo)
{
	int	statloc;
	int	exit_code;
	int	pipe_cnt;
	int	i;

	exit_code = 0;
	waitpid(last_child, &statloc, WUNTRACED);
	if (WIFEXITED(statloc))
		exit_code = WEXITSTATUS(statloc);
	else if (WIFSIGNALED(statloc))
		exit_code = WTERMSIG(statloc);
	if (pipeinfo != NULL && pipeinfo->pipelist != NULL)
	{
		pipe_cnt = 0;
		while (pipeinfo->pipelist[pipe_cnt] != PIPE_END)
			pipe_cnt++;
		i = 0;
		while (i < pipe_cnt / 2)
		{
			wait(0);
			i++;
		}
		free(pipeinfo->pipelist);
	}
	return (exit_code);
}
