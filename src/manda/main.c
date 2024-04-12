/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/12 14:16:40 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
#include "libft.h"

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_malloc(sizeof(t_data));
	data->lr_table = insert_lr_table();
	data->grammar = insert_grammar();
	data->env_table = envp;
	data->exit_code = 0;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_syntax_tree	*ast;
	char			*input;

	if (argc != 1)
		exit(EXIT_FAILURE);
	print_header();
	(void)argv;
	//signal();
	data = init_data(envp);
	while (1)
	{
		//system("leaks minishell");
		input = readline(BLUE "deepshell" CYAN "$ " RESET);
		ast = parser(data->lr_table, data->grammar, input);
		add_history(input);
		free(input);
		//data->exit_code = execute(ast);
		//free_syntax_tree(ast);
	}
}
