/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 13:26:08 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

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

int	execute_only_command(t_syntax_tree *command)
{
	int	pid;
	int	redi[2];

	open_file(command->child[R], redi);
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		if (redi[INFILE] != INIT)
			dup2(redi[INFILE], STDIN_FILENO);
		if (redi[OUTFILE] != INIT)
			dup2(redi[OUTFILE], STDOUT_FILENO);
		execve(((char **)command->child[L])[0], command->child[L], NULL);
		exit(2);
	}
	close_redirect_file(redi);
	return (wait_process(pid, NULL));
}

int	execute_command(t_syntax_tree *command, int *pipe_fd, int cnt
														, t_pipe_order order)
{
	int	pid;
	int	redi[2];

	open_file(command->child[R], redi);
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0 && order == start)
		start_process(command->child[L], pipe_fd, cnt, redi);
	else if (pid == 0 && order == middle)
		mid_process(command->child[L], pipe_fd, cnt, redi);
	else if (pid == 0 && order == end)
		end_process(command->child[L], pipe_fd, redi);
	close_redirect_file(redi);
	if (order == end)
	{
		close_rest_pipe(pipe_fd, PIPE_ALL);
		return (wait_process(pid, pipe_fd));
	}
	else
		return (CONTINUE);
}
