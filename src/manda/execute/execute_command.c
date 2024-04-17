/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 22:22:04 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

static char	*_matching_path(char *pathenv, char *cmdname)
{
	char	*find[2];
	char	*execute;
	char	*tmp;

	find[0] = pathenv[5];
	find[1] = ft_strchr(find[0], ':');
	while (find[1] != NULL)
	{
		tmp = ft_substr(find[0], 0, find[0] - find[1]);
		execute = ft_strjoin(tmp, cmdname);
		free(tmp);
		if (access(execute, X_OK) == 0)
			return (execute);
		free(execute);
		find[0] = find[1] + 1;
		find[1] = ft_strchr(find[0], ':');
	}
	return (NULL);
}

char	*is_able_execute(char **envlist, char *cmdname)
{
	char	*pathenv;
	char	*res;
	int		i;

	if (access(cmdname, X_OK) == 0)
		return (cmdname);
	i = 0;
	while (ft_strncmp(envlist[i], "PATH=", 5) != 0)
		i++;
	pathenv = envlist[i];
	//if (pathenv == NULL)
	//	ft_error(error_nosuchafile, errno, cmdname);
	res = _matching_path(pathenv, cmdname);
	//if (res == NULL)
	//	ft_error(error_nosuchafile, errno, cmdname);
	return (res);
}

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
