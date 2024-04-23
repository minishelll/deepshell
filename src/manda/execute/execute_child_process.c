/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 18:58:25 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 11:35:19 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "built_in.h"
#include "ft_error.h"

void	start_process(char **cmds, char **envlist, int *use_pipe, int *redi)
{
	const t_bi_type	bi_type = is_built_in(cmds[0]);
	char			*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	else
		dup2(use_pipe[0], STDOUT_FILENO);
	if (bi_type != none)
		exit(execute_built_in(cmds, envlist, bi_type));
	else
	{
		program = check_program(envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}

void	mid_process(char **cmds, char **envlist, int *use_pipe, int *redi)
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
	if (bi_type != none)
		exit(execute_built_in(cmds, envlist, bi_type));
	else
	{
		program = check_program(envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}

void	end_process(char **cmds, char **envlist, int *use_pipe, int *redi)
{
	const t_bi_type	bi_type = is_built_in(cmds[0]);
	char			*program;

	if (redi[INFILE] != INIT)
		dup2(redi[INFILE], STDIN_FILENO);
	else
		dup2(use_pipe[0], STDIN_FILENO);
	if (redi[OUTFILE] != INIT)
		dup2(redi[OUTFILE], STDOUT_FILENO);
	if (bi_type != none)
		exit(execute_built_in(cmds, envlist, bi_type));
	else
	{
		program = check_program(envlist, cmds[0]);
		execve(program, cmds, NULL);
		exit(2);
	}
}
