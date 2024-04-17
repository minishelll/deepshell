/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 21:02:45 by taerakim         ###   ########.fr       */
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

void	free_redi(t_redi *redi)
{
	free(redi->file);
	free(redi);
}

void	free_syntax_tree(t_syntax_tree *curr)
{
	if (curr->type == command)
	{
		free_words(curr->child[L]);
		ft_lstclear(curr->child[R], free_redi);
		return ;
	}
	free_syntax_tree(curr->child[L]);
	if (curr->type == subshell)
		ft_lstclear(curr->child[R], free_redi);
	else
		free_syntax_tree(curr->child[R]);
}

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_malloc(sizeof(t_data));
	data->lr_table = insert_lr_table();
	data->grammar = insert_grammar();
	data->envlist = set_envlist(envp, NULL);
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
	print_welcome_title();
	(void)argv;
	//signal();
	data = init_data(envp);
	while (1)
	{
		//system("leaks minishell");
		input = readline(BLUE "deepshell" CYAN "$ " RESET);
		ast = parser(data->lr_table, data->grammar, input/*, data->envlist*/);
		add_history(input);
		free(input);
		data->exit_code = execute(ast/*, data->envlist*/);
		free_syntax_tree(ast);
	}
}
