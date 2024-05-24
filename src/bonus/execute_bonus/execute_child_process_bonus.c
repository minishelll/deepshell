/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:25 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute_bonus.h"
#include "built_in_bonus.h"
#include "ft_error_bonus.h"

void	single_process(char **cmds, t_env *env, int *redi)
{
	char	*program;

	if (cmds == NULL)
		exit(0);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	program = check_program(env->envlist, cmds[0]);
	execve(program, cmds, env->envlist);
	exit(2);
}

void	start_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	t_bi_type	bi_type;
	char		*program;

	if (cmds == NULL)
		exit(0);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(use_pipe[0], STDOUT_FILENO);
	bi_type = is_built_in(cmds[0]);
	if (bi_type != bi_none)
		exit(execute_builtin(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, env->envlist);
		exit(2);
	}
}

void	mid_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	t_bi_type	bi_type;
	char		*program;

	if (cmds == NULL)
		exit(0);
	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(use_pipe[1], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(use_pipe[0], STDOUT_FILENO);
	bi_type = is_built_in(cmds[0]);
	if (bi_type != bi_none)
		exit(execute_builtin(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, env->envlist);
		exit(2);
	}
}

void	end_process(char **cmds, t_env *env, int *use_pipe, int *redi)
{
	t_bi_type	bi_type;
	char		*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(use_pipe[0], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	if (cmds == NULL)
		exit(0);
	bi_type = is_built_in(cmds[0]);
	if (bi_type != bi_none)
		exit(execute_builtin(cmds, env, bi_type, redi));
	else
	{
		program = check_program(env->envlist, cmds[0]);
		execve(program, cmds, env->envlist);
		exit(2);
	}
}
