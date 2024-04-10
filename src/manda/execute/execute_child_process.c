/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:25 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 16:17:33 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "execute.h"

int	wait_process(int last_child, int *pipe_fd)
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
	if (pipe_fd != NULL)
	{
		i = 0;
		while (pipe_fd[i] != PIPE_END)
			i++;
		pipe_cnt = i / 2;
		i = 0;
		while (i++ < pipe_cnt - 1)
			wait(0);
		free(pipe_fd);
	}
	return (exit_code);
}

void	start_process(char **cmds, int *pipe_fd, int cnt, int *redi)
{
	//char	*program;
	int		*backpipe;

	backpipe = &pipe_fd[(cnt - 2) * 2];
	close_rest_pipe(pipe_fd, cnt);
	//program = matching_path(path, cmds[0]);
	//if (program == NULL)
	//	ft_error(error_access, cmds[0]);
	close(backpipe[0]);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(backpipe[1], STDOUT_FILENO);
	execve(cmds[0], cmds, NULL);
	exit(2);
}

void	mid_process(char **cmds, int *pipe_fd, int cnt, int *redi)
{
	//char	*program;
	int		*frontpipe;
	int		*backpipe;

	frontpipe = &pipe_fd[(cnt - 1) * 2];
	backpipe = &pipe_fd[cnt * 2];
	close_rest_pipe(pipe_fd, cnt);
	//program = matching_path(path, cmds[0]);
	//if (program == NULL)
	//	ft_error(ACCESS_ERROR, cmds[0]);
	close(frontpipe[1]);
	close(backpipe[0]);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(frontpipe[0], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(backpipe[1], STDOUT_FILENO);
	execve(cmds[0], cmds, NULL);
	exit(2);
}

void	end_process(char **cmds, int *pipe_fd, int *redi)
{
	//char	*program;
	int		*frontpipe;

	frontpipe = &pipe_fd[0];
	close_rest_pipe(pipe_fd, 1);
	//program = matching_path(path, cmds[0]);
	//if (program == NULL)
	//	ft_error(ACCESS_ERROR, cmds[0]);
	
	//close(frontpipe[1]);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(frontpipe[0], STDIN_FILENO);
	execve(cmds[0], cmds, NULL);
	exit(2);
}
