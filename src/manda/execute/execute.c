/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/12 15:04:43 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"

static int	*_pipe_join(int *org, int *new, int pipe_cnt)
{
	int	*res;
	int	i;

	res = (int *)ft_malloc(sizeof(char) * (pipe_cnt * 2 + 1));
	i = 0;
	while (i < (pipe_cnt - 1) * 2)
	{
		res[i] = org[i];
		i++;
	}
	res[i] = new[READ];
	res[i + 1] = new[WRITE];
	res[i + 2] = PIPE_END;
	free(org);
	return (res);
}

int	execute_pipe(t_syntax_tree *curr, int **pipe_fd, int pipe_cnt)
{
	int	curr_pipe[2];
	int	result;

	if (pipe(curr_pipe) == -1)
		exit(EXIT_FAILURE);
	*pipe_fd = _pipe_join(*pipe_fd, curr_pipe, pipe_cnt);
	if (((t_syntax_tree *)curr->child[L])->type == sym_command)
		result = execute_command(curr->child[L], *pipe_fd, pipe_cnt + 1, start);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_pipe)
		result = execute_pipe(curr->child[L], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_subshell)
		result = execute_subshell(curr->child[L], NULL, curr_pipe);
	if (((t_syntax_tree *)curr->child[R])->type == sym_command \
		&& pipe_cnt == 1)
		result = execute_command(curr->child[R], *pipe_fd, pipe_cnt, end);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_command)
		result = execute_command(curr->child[R], *pipe_fd, pipe_cnt, middle);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_pipe)
		result = execute_pipe(curr->child[R], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_subshell)
		result = execute_subshell(curr->child[R], curr_pipe, NULL);
	return (result);
}

int	execute(t_syntax_tree *root)
{
	int	result;
	int	*pipe_fd;

	pipe_fd = NULL;
	if (root->type == sym_command)
		result = execute_only_command(root);
	else if (root->type == sym_pipe)
		result = execute_pipe(root, &pipe_fd, 1);
	else if (root->type == sym_subshell)
		result = execute_subshell(root, NULL, NULL);
	else
	{
 		result = execute(root->child[L]);
		if ((root->type == sym_and && result == 0) \
		|| (root->type == sym_or && result != 0))
			result = execute(root->child[R]);
	}
	return (result);
}
