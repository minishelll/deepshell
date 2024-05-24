/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:12:32 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "execute_bonus.h"
#include "built_in_bonus.h"
#include "expand_bonus.h"
#include "mini_signal_bonus.h"
#include "ft_error_bonus.h"

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
	struct stat	file_info;
	char		*pathenv;
	char		*res;

	if (ft_strchr(cmdname, '/') != NULL)
	{
		if (stat(cmdname, &file_info) == 0 && S_ISDIR(file_info.st_mode) != 0)
			ft_error(error_is_dir, errno, cmdname);
		if (access(cmdname, F_OK) != 0)
			ft_error(error_access_f, errno, cmdname);
		if (access(cmdname, X_OK) == 0)
			return (cmdname);
		else
			ft_error(error_access_x, errno, cmdname);
	}
	res = NULL;
	pathenv = find_env(envlist, "PATH");
	if (pathenv != NULL)
		res = _matching_path(pathenv, cmdname);
	if (res == NULL)
		ft_error(error_cmd_not_found, errno, cmdname);
	return (res);
}

int	execute_only_command(t_syntax_tree *command, t_env *env)
{
	t_bi_type	bi_type;
	int			pid;
	int			redi[2];

	if (expand(command, env) == 1)
		return (1);
	open_file(command->child[R], redi);
	if (command->child[L] != NULL)
	{
		bi_type = is_built_in(((char **)command->child[L])[0]);
		if (bi_type != bi_none)
			return (execute_builtin(command->child[L], env, bi_type, redi));
	}
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		set_child_signal();
		single_process(command->child[L], env, redi);
	}
	return (wait_process(pid, NULL));
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
		if (expand(command, env) == 1)
			return (1);
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
