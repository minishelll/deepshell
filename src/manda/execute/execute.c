/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/07 17:42:57 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "syntax_tree.h"
#include "libft.h"
#include <sys/wait.h>//wait define
#include <fcntl.h>//open option

int	handle_subshell(t_syntax_tree *curr, int *left_pipe, int *right_pipe)
{
	int	result;
	int	redi[2];

	if (curr->child[R] != NULL)
		open_file(curr->child[R], redi);
	if (left_pipe != NULL)
	{
		close(left_pipe[1]);
		dup2(left_pipe[0], STDIN_FILENO);
	}
	if (right_pipe != NULL)
	{
		close(right_pipe[0]);
		dup2(right_pipe[1], STDOUT_FILENO);
	}
	result = execute(curr->child[L]);
	if (left_pipe != NULL)
		close(left_pipe[0]);
	if (right_pipe != NULL)
		close(right_pipe[1]);
	dup2(STDIN_FILENO, STDIN_FILENO);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
	return (result);
}

int	execute(t_syntax_tree *root)
{
	int	result;
	int	*pipe_fd;

	pipe_fd = NULL;
	if (root->type == sym_command)
		result = execute_cmd(root->child[L], NULL, 0);
	else if (root->type == sym_pipe)
		result = execute_pipe(root, &pipe_fd, 1);
	else if (root->type == sym_subshell)
		result = handle_subshell(root->child[L], NULL, NULL);
	else
	{
 		result = execute(root->child[L]);
		if (root->type + result == 1)
			result = execute(root->child[R]);
	}
	return (result);
}

int	execute_pipe(t_syntax_tree *curr, int **pipe_fd, int pipe_cnt)
{
	int	curr_pipe[2];
	int	result;

	if (pipe(curr_pipe) == -1)
		exit(EXIT_FAILURE);
	*pipe_fd = pipe_join(*pipe_fd, curr_pipe, pipe_cnt);
	if (((t_syntax_tree *)curr->child[L])->type == sym_command)
		execute_start_cmd(curr->child[L], pipe_cnt);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_pipe)
		result = execute_pipe(curr->child[L], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[L])->type == sym_subshell)
		result = handle_subshell(curr->child[L], NULL, curr_pipe);
	if (((t_syntax_tree *)curr->child[R])->type == sym_command \
		&& pipe_cnt == 1)
		result = execute_end_cmd(curr->child[R], pipe_cnt - 1);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_command)
		execute_mid_cmd(curr->child[R], pipe_cnt - 1);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_pipe)
		result = execute_pipe(curr->child[R], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[R])->type == sym_subshell)
		result = handle_subshell(curr->child[R], curr_pipe, NULL);
	return (result);
}

int	*pipe_join(int *org, int *new, int pipe_cnt)
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
	res[i] = new[0];
	res[i + 1] = new[1];
	res[i + 2] = END;
	free(org);
	return (res);
}

void	wait_process(int last_child, int *pipe_fd)
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
	i = 0;
	while (pipe_fd[i] != END)
		i++;
	pipe_cnt = i / 2;
	i = 0;
	while (i < pipe_cnt - 1)
	{
		wait(0);
		i++;
	}
	return (exit_code);
}
