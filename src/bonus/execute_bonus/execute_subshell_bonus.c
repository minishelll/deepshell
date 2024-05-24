/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:45:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute_bonus.h"
#include "ft_error_bonus.h"

static void	_handle_io(int *redi, t_pipe *pipeinfo, t_pipe_order order)
{
	int	*use_pipe;

	use_pipe = NULL;
	if (pipeinfo != NULL && pipeinfo->pipelist != NULL)
		use_pipe = handle_pipe(pipeinfo, order);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else if (use_pipe != NULL)
	{
		if (order == middle)
			dup2(use_pipe[1], STDIN_FILENO);
		if (order == end)
			dup2(use_pipe[0], STDIN_FILENO);
	}
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else if (use_pipe != NULL)
	{
		if (order == middle)
			dup2(use_pipe[0], STDOUT_FILENO);
		if (order == start)
			dup2(use_pipe[0], STDOUT_FILENO);
	}
}

int	execute_subshell(t_syntax_tree *curr, t_env *env
						, t_pipe *pipeinfo, t_pipe_order order)
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
		_handle_io(redi, pipeinfo, order);
		result = execute(curr->child[L], env);
		close_redirect_file(redi);
		exit(result);
	}
	close_redirect_file(redi);
	if (order == parent || order == end)
	{
		if (order == end)
			handle_pipe(pipeinfo, parent);
		return (wait_process(pid, pipeinfo));
	}
	else
		return (CONTINUE);
}
