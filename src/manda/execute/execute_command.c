/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/18 07:25:12 by taerakim         ###   ########.fr       */
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

	find[0] = &pathenv[5];
	find[1] = ft_strchr(find[0], ':');
	while (find[1] != NULL)
	{
		execute = ft_substr(find[0], 0, find[1] - find[0]);
		tmp = ft_strjoin(execute, "/");
		free(execute);
		execute = ft_strjoin(tmp, cmdname);
		if (access(execute, X_OK) == 0)
			return (execute);
		free(execute);
		find[0] = find[1] + 1;
		find[1] = ft_strchr(find[0], ':');
	}
	return (NULL);
}

char	*check_program(char **envlist, char *cmdname)
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

int	execute_only_command(t_syntax_tree *command, char **envlist)
{
	char	*program;
	int		pid;
	int		redi[2];

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
		//if (built_in == yes)
		//	execute_built_in(command->child[L], envlist);
		//else
		//{
			program = check_program(envlist, ((char **)command->child[L])[0]);
			execve(program, command->child[L], envlist);
			exit(2);
		//}
	}
	close_redirect_file(redi);
	return (wait_process(pid, NULL));
}

int	execute_command(t_syntax_tree *command, char **envlist
					, t_pipe *pipeinfo, t_pipe_order order)
{
	const t_child_proc	proc[3] = {start_process, mid_process, end_process};
	int					pid;
	int					*use_pipe;
	int					redi[2];

	open_file(command->child[R], redi);
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		use_pipe = handle_pipe(pipeinfo, order);
		proc[order](command->child[L], envlist, use_pipe, redi);
	}
	close_redirect_file(redi);
	if (order == end)
	{
		handle_pipe(pipeinfo, parent);
		return (wait_process(pid, pipeinfo));
	}
	else
		return (CONTINUE);
}
