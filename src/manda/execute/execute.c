/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/07 15:00:34 by taerakim         ###   ########.fr       */
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

	if (curr->child[RIGHT] != NULL)
		open_file(curr->child[RIGHT], redi);
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
	//close는 여기서는 해야겠다. 밖에서는 close안했을테니
	result = execute(curr->child[LEFT]);
	dup2(STDIN_FILENO, STDIN_FILENO);
	dup2(STDOUT_FILENO, STDOUT_FILENO);
	return (result);
}

int	execute(t_syntax_tree *root)//결국 기존에는 좌우를 시키는 애였는데,.. 논리연산자만 그런 동작을 하고... 
{
	int	result;
	int	*pipe_fd;

	pipe_fd = NULL;
	if (root->type == sym_command)
		result = execute_cmd(root->child[LEFT], NULL, 0);
	else if (root->type == sym_pipe)
		result = execute_pipe(root, &pipe_fd, 1);
	else
	{
		result = execute(root->child[LEFT]);
		if (root->type + result == 1)
			result = execute(root->child[RIGHT]);
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
	if (((t_syntax_tree *)curr->child[LEFT])->type == sym_command)
		result = execute_cmd(curr->child[LEFT], pipe_cnt);
	else if (((t_syntax_tree *)curr->child[LEFT])->type == sym_pipe)
		result = execute_pipe(curr->child[LEFT], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[LEFT])->type == sym_subshell)
	{
		result = handle_subshell(curr->child[LEFT], NULL, curr_pipe);
		close(curr_pipe[1]);
	}
	if (((t_syntax_tree *)curr->child[RIGHT])->type == sym_command)
		result = execute_cmd(curr->child[RIGHT], pipe_cnt - 1);
	else if (((t_syntax_tree *)curr->child[RIGHT])->type == sym_pipe)
		result = execute_pipe(curr->child[RIGHT], pipe_fd, pipe_cnt + 1);
	else if (((t_syntax_tree *)curr->child[RIGHT])->type == sym_subshell)
	{
		result = handle_subshell(curr->child[RIGHT], curr_pipe, NULL);
		close(curr_pipe[0]);//양쪽이 서브쉘이라면?
	}
	//if (depth == 0)
	//	return (wait_process());

	return (result);
	//return (wait_process()); 보류보류
}

int	*pipe_join(int *org, int *new, int pipe_cnt)
{
	int	*res;
	int	i;

	res = (int *)ft_malloc(sizeof(char) * (pipe_cnt * 2));
	i = 0;
	while (i < (pipe_cnt - 1) * 2)
	{
		res[i] = org[i];
		i++;
	}
	res[i] = new[0];
	res[i + 1] = new[1];
	free(org);
	return (res);
}

void	wait_process(int last_child, int child_cnt)
{
	int	statloc;
	int	exit_code;
	int	i;

	exit_code = 0;
	waitpid(last_child, &statloc, WUNTRACED);
	if (WIFEXITED(statloc))
		exit_code = WEXITSTATUS(statloc);
	else if (WIFSIGNALED(statloc))
		exit_code = WTERMSIG(statloc);
	i = 0;
	while (i < child_cnt - 1)
	{
		wait(0);
		i++;
	}
	return (exit_code);
}
