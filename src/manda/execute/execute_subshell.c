/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:45:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 13:32:20 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "execute.h"
#include "ft_error.h"

static void	_handle_io(int *redi, int *pipe_fd, int cnt, t_pipe_order order)
{
	int	*frontpipe;
	int	*backpipe;

	frontpipe = NULL;
	backpipe = NULL;
	if (pipe_fd != NULL)
	{
		close_rest_pipe(pipe_fd, cnt);
		if (order == end || order == middle)
			frontpipe = &pipe_fd[(cnt - 1) * 2];
		if (order == start || order == middle)
			backpipe = &pipe_fd[(cnt - 2) * 2];
	}
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else if (frontpipe != NULL)
	{
		close(frontpipe[WRITE]);
		dup2(frontpipe[READ], STDIN_FILENO);
	}
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else if (backpipe != NULL)
		dup2(backpipe[WRITE], STDOUT_FILENO);
}

int	execute_subshell(t_syntax_tree *curr, int *pipe_fd, int cnt, 
														t_pipe_order order)
{
	int	pid;
	int	result;
	int	redi[2];

	open_file(curr->child[R], redi);
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		_handle_io(redi, pipe_fd, cnt, order);
		result = execute(curr->child[L]);
		close_redirect_file(redi);
		exit(result);
	}
	close_redirect_file(redi);
	if (order == parent || order == end)
	{
		if (order == end)
			close_rest_pipe(pipe_fd, PIPE_ALL);
		return (wait_process(pid, pipe_fd));
	}
	else
		return (CONTINUE);
}
