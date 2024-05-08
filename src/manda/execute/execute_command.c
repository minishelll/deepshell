/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/08 18:21:40 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "built_in.h"
#include "ft_error.h"
#include "mini_signal.h"

static char	*_matching_path(char *pathenv, char *cmdname)
{
	char	**splited;
	char	*execute;
	char	*tmp;
	int		i;

	splited = ft_split(&pathenv[5], ':');
	i = 0;
	while (splited[i] != NULL)
	{
		tmp = ft_strjoin(splited[i], "/");
		execute = ft_strjoin(tmp, cmdname);
		free(tmp);
		if (access(execute, X_OK) == 0)
			return (execute);
		free(execute);
		i++;
	}
	i = 0;
	while (splited[i] != NULL)
	{
		free(splited[i]);
		i++;
	}
	free(splited);
	return (NULL);
}

char	*check_program(char **envlist, char *cmdname)
{
	char	*pathenv;
	char	*res;

	if (access(cmdname, X_OK) == 0)
		return (cmdname);
	pathenv = find_env(envlist, "PATH");
	if (pathenv == NULL)
		return (NULL);
	res = _matching_path(pathenv, cmdname);
	if (res == NULL)
		ft_error(error_access, errno, cmdname);
	return (res);
}

int	execute_only_command(t_syntax_tree *command, t_env *env)
{
	t_bi_type	bi_type;
	int			pid;
	int			redi[2];

	open_file(command->child[R], redi);
	bi_type = is_built_in(((char **)command->child[L])[0]);
	if (bi_type != bi_none)
		return (execute_built_in(command->child[L], env, bi_type, redi));
	else
	{
		pid = fork();
		if (pid == -1)
			ft_error(error_systemcall, errno, NULL);
		if (pid == 0)
			single_process(command->child[L], env, redi);
		return (wait_process(pid, NULL));
	}
}

int	execute_command(t_syntax_tree *command, t_env *env
					, t_pipe *pipeinfo, t_pipe_order order)
{
	const t_child_proc	proc[3] = {start_process, mid_process, end_process};
	int					pid;
	int					*use_pipe;
	int					redi[2];

	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		set_child_signal();
		open_file(command->child[R], redi);
		use_pipe = handle_pipe(pipeinfo, order);
		proc[order](command->child[L], env, use_pipe, redi);
	}
	if (order == end)
	{
		handle_pipe(pipeinfo, parent);
		return (wait_process(pid, pipeinfo));
	}
	else
		return (CONTINUE);
}
