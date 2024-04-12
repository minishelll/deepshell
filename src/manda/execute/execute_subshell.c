/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:45:56 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/12 15:09:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "execute.h"

static void	_handle_io(int *redi, int *tmpstd, int *left_pipe, int *right_pipe)
{
	tmpstd[READ] = dup(STDIN_FILENO);
	tmpstd[WRITE] = dup(STDOUT_FILENO);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else if (left_pipe != NULL)
	{
		close(left_pipe[WRITE]);
		dup2(left_pipe[READ], STDIN_FILENO);
	}
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else if (right_pipe != NULL)
	{
		close(right_pipe[READ]);
		dup2(right_pipe[WRITE], STDOUT_FILENO);
	}
}

static void	_restore_io(int *redi, int *tmpstd)
{
	dup2(tmpstd[READ], STDIN_FILENO);
	dup2(tmpstd[WRITE], STDOUT_FILENO);
	close(tmpstd[READ]);
	close(tmpstd[WRITE]);
	if (redi[INFILE] != INIT)
		close(redi[INFILE]);
	if (redi[OUTFILE] != INIT)
		close(redi[OUTFILE]);
}

int	execute_subshell(t_syntax_tree *curr, int *left_pipe, int *right_pipe)
{
	int	result;
	int	tmpstd[2];
	int	redi[2];

	open_file(curr->child[R], redi);
	ft_putnbr_fd(redi[INFILE], 2);
	ft_putnbr_fd(redi[OUTFILE], 2);
	_handle_io(redi, tmpstd, left_pipe, right_pipe);
	result = execute(curr->child[L]);
	if (left_pipe != NULL)
		close(left_pipe[READ]);
	if (right_pipe != NULL)
		close(right_pipe[WRITE]);
	_restore_io(redi, tmpstd);
	return (result);
}
