/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/07 17:50:22 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "syntax_tree.h"

//static char	*matching_path(char **path, char *cmd)
//{
//	char	*execute;
//	int		i;

//	if (access(cmd, X_OK) == 0)
//		return (cmd);
//	i = 0;
//	while (path[i] != NULL)
//	{
//		execute = ft_strjoin(path[i], cmd);
//		if (execute == NULL)
//			ft_error(SYSTEMCALL_FAILURE, NULL);
//		if (access(execute, X_OK) == 0)
//			return (execute);
//		free(execute);
//		i++;
//	}
//	return (NULL);
//}

void	close_rest_pipe(int *pipe_fd, int order)
{
	const int	use_pipe = order * 2 - 3;
	int			i;

	i = 0;
	while (i < use_pipe)
	{
		close(pipe_fd[i]);
		i++;
	}
	i += 2;
	while (pipe_fd[i] != END)
	{
		close(pipe_fd[i]);
		i++;
	}
}

int	execute_only_cmd(t_syntax_tree *command)
{
	int	pid;
	int	redi[2];

	pid = fork();
	//if (pid == -1)
	//	ft_error(SYSTEMCALL_FAILURE, NULL);
	if (pid == 0)
	{
		redi[INFILE] = INIT;
		redi[OUTFILE] = INIT;
		open_file(command->child[R], redi);
		if (redi[INFILE] != INIT)
			dup2(redi[INFILE], STDIN_FILENO);
		if (redi[OUTFILE] != INIT)
			dup2(redi[OUTFILE], STDOUT_FILENO);
		//execve(program, cmds, env);
		exit(2);
	}
	return (wait_process(pid, 1));
}



void	execute_start_cmd(t_syntax_tree *command, int *pipe_fd, int order)
{
	int	pid;
	int	redi[2];
	//char	*program;
	int		*backpipe;

	pid = fork();
	//if (pid == -1)
	//	ft_error(SYSTEMCALL_FAILURE, NULL);
	if (pid == 0)
	{
		backpipe = pipe_fd[(order - 2) * 2];
		close_rest_pipe(pipe_fd, order);
		//program = matching_path(path, cmds[0]);
		//if (program == NULL)
		//	ft_error(ACCESS_ERROR, cmds[0]);
		close(backpipe[0]);
		if (redi[INFILE] != INIT)
			dup2(redi[INFILE], STDIN_FILENO);
		if (redi[OUTFILE] != INIT)
			dup2(redi[OUTFILE], STDOUT_FILENO);
		else
			dup2(backpipe[1], STDOUT_FILENO);
		//execve(program, cmds, env);
		exit(2);
	}
}

void	execute_middle_cmd(t_syntax_tree *command, int *pipe_fd, int order)
{
	int		pid;
	int		redi[2];
	//char	*program;
	int		*frontpipe;
	int		*backpipe;

	pid = fork();
	//if (pid == -1)
	//	ft_error(SYSTEMCALL_FAILURE, NULL);
	if (pid == 0)
	{
		frontpipe = pipe_fd[(order - 1) * 2];
		backpipe = pipe_fd[order * 2];
		close_rest_pipe(pipe_fd, order);
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
		//execve(program, cmds, env);
		exit(2);
	}
}

int	execute_end_cmd(t_syntax_tree *command, int *pipe_fd)
{
	int		pid;
	int		redi[2];
	//char	*program;
	int		*frontpipe;

	pid = fork();
	//if (pid == -1)
	//	ft_error(SYSTEMCALL_FAILURE, NULL);
	if (pid == 0)
	{
		frontpipe = pipe_fd[0];
		close_rest_pipe(pipe_fd, 1);
		//program = matching_path(path, cmds[0]);
		//if (program == NULL)
		//	ft_error(ACCESS_ERROR, cmds[0]);
		close(frontpipe[1]);
		if (redi[INFILE] != INIT)
			dup2(redi[INFILE], STDIN_FILENO);
		if (redi[OUTFILE] != INIT)
			dup2(redi[OUTFILE], STDOUT_FILENO);
		else
			dup2(frontpipe[0], STDIN_FILENO);
		//execve(program, cmds, env);
		exit(2);
	}
	return (wait_process(pid, pipe_fd));
}

//결국 pipe는 모두다 전체를 알게될 것이다.