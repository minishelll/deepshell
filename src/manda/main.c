/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul. kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 13:51:59 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
#include "execute.h"
#include "libft.h"

void	free_redi(void *redi)
{
	t_redi	*ptr;

	ptr = (t_redi *)redi;
	free(ptr->file);
	free(ptr);
}

void	free_syntax_tree(t_syntax_tree *curr)
{
	t_list	*redi_list;

	if (curr->type == command)
	{
		free_words(curr->child[L]);
		if (curr->child[R] != NULL)
		{
			redi_list = curr->child[R];
			ft_lstclear(&redi_list, free_redi);
		}
		free(curr);
		return ;
	}
	free_syntax_tree(curr->child[L]);
	if (curr->child[R] != NULL)
	{
		if (curr->type == subshell)
		{
			redi_list = curr->child[R];
			ft_lstclear(&redi_list, free_redi);
		}
		else
			free_syntax_tree(curr->child[R]);
	}
	free(curr);
}

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
		update_envlist(env->envlist, "OLDPWD", "");
}

t_data	*init_data(char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_syntax_tree	*ast;
	char			*input;

	if (argc != 1)
		exit(EXIT_FAILURE);
	print_welcome_title();
	(void)argv;
	//signal();
	data = init_data(envp);
	while (1)
	{
		//system("leaks minishell");
		input = readline(BLUE "deepshell" CYAN "$ " RESET);
		ast = parser(data, input);
		add_history(input);
		if (ast == NULL)
			continue ;
		free(input);
		data->env->exit_code = execute(ast, data->env);
		free_syntax_tree(ast);
	}
}
