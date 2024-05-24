/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "parser_bonus.h"
#include "execute_bonus.h"
#include "mini_signal_bonus.h"
#include "ft_error_bonus.h"

static void	_set_basic_env(t_env *env)
{
	char	*update;

	update = find_env(env->envlist, "SHLVL");
	if (update == NULL)
		update = ft_itoa(0);
	else
		update = ft_itoa(ft_atoi(update) + 1);
	if (update_envlist(env->envlist, "SHLVL", update) == false)
		env->envlist = add_envlist(env->envlist, \
									ft_strjoin("SHLVL=", update));
	free(update);
	update = find_env(env->envlist, "PWD");
	if (update == NULL)
		update = "";
	if (update_envlist(env->envlist, "SHELL", update) == false)
		env->envlist = add_envlist(env->envlist, \
									ft_strjoin("SHELL=", update));
	update = find_env(env->envlist, "OLDPWD");
	if (update != NULL)
		delete_envlist(env->envlist, "OLDPWD");
}

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_malloc(sizeof(t_data));
	data->lr_table = insert_lr_table();
	data->grammar = insert_grammar();
	data->env = (t_env *)ft_malloc(sizeof(t_env));
	data->env->envlist = init_envlist(envp);
	data->env->exit_code = 0;
	_set_basic_env(data->env);
	return (data);
}

static char	*get_input(t_env *env)
{
	char	*input;

	set_rl_signal();
	input = readline(PROMPT);
	if (g_signal == SIGINT)
	{
		env->exit_code = 1;
		g_signal = 0;
	}
	if (input == NULL)
		do_sig_term(SIGTERM, env->exit_code);
	if (*input == '\0')
		return (NULL);
	add_history(input);
	return (input);
}

static t_data	*init_minishell(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	print_welcome_title();
	return (init_data(envp));
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_syntax_tree	*ast;
	char			*input;
	int				heredoc;

	data = init_minishell(argc, argv, envp);
	while (1)
	{
		input = get_input(data->env);
		if (input == NULL)
			continue ;
		set_signal_ignore();
		ast = parser(data, input);
		free(input);
		if (ast == NULL)
			continue ;
		heredoc = execute_heredoc(ast, data->env);
		if (heredoc != 1)
			data->env->exit_code = execute(ast, data->env);
		else
			data->env->exit_code = 1;
		unlink_all_tmpfile();
		free_syntax_tree(ast);
	}
}
