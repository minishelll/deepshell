/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 13:20:27 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

static int	*_pipe_join(int *org, int *new, int cnt)
{
	int	*res;
	int	i;

	res = (int *)ft_malloc(sizeof(int) * (cnt * 2 + 1));
	i = 0;
	while (i < (cnt - 1) * 2)
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

int	execute_pipe(t_syntax_tree *curr, int **pipe_fd, int cnt)
{
	int	curr_pipe[2];
	int	result;

	if (pipe(curr_pipe) == -1)
		ft_error(error_systemcall, errno, NULL);
	*pipe_fd = _pipe_join(*pipe_fd, curr_pipe, cnt);
	if (((t_syntax_tree *)curr->child[L])->type == sym_command)
		result = execute_command(curr->child[L], *pipe_fd, cnt + 1, start);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_pipe)
		result = execute_pipe(curr->child[L], pipe_fd, cnt + 1);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_subshell)
		result = execute_subshell(curr->child[L], *pipe_fd, cnt + 1, start);
	if (((t_syntax_tree *)curr->child[R])->type == sym_command
	&& cnt == 1)
		result = execute_command(curr->child[R], *pipe_fd, cnt, end);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_command)
		result = execute_command(curr->child[R], *pipe_fd, cnt, middle);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_pipe)
		result = execute_pipe(curr->child[R], pipe_fd, cnt + 1);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_subshell \
	&& cnt == 1)
		result = execute_subshell(curr->child[R], *pipe_fd, cnt, end);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_subshell)
		result = execute_subshell(curr->child[R], *pipe_fd, cnt, middle);
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
		result = execute_subshell(root, NULL, 0, parent);
	else
	{
 		result = execute(root->child[L]);
		if ((root->type == sym_and && result == 0) \
		|| (root->type == sym_or && result != 0))
			result = execute(root->child[R]);
	}
	return (result);
}
