/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:25 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/26 15:23:11 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "built_in.h"
#include "ft_error.h"

void	single_process(char **cmds, t_env *env, int *redi)
{
	char	*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	if (cmds[0] == NULL)
		exit(0);
	program = check_program(env->envlist, cmds[0]);
	execve(program, cmds, env->envlist);
	exit(2);
}

void	start_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	const t_bi_type	bi_type = is_built_in(cmds[0]);
	char			*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(use_pipe[0], STDOUT_FILENO);
	if (cmds[0] == NULL)
		exit(0);
	else if (bi_type != none)
		exit(execute_built_in(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}

void	mid_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	const t_bi_type	bi_type = is_built_in(cmds[0]);
	char			*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(use_pipe[1], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(use_pipe[0], STDOUT_FILENO);
	if (cmds[0] == NULL)
		exit(0);
	else if (bi_type != none)
		exit(execute_built_in(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}

void	end_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	const t_bi_type	bi_type = is_built_in(cmds[0]);
	char			*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(use_pipe[0], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	if (cmds[0] == NULL)
		exit(0);
	else if (bi_type != none)
		exit(execute_built_in(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}
