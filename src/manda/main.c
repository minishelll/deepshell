/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:41 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/29 23:32:54 by sehwjang         ###   ########.fr       */
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

t_data	*init_data(char **envp)
{
	t_data	*data;

	data = (t_data *)ft_malloc(sizeof(t_data));
	data->lr_table = insert_lr_table();
	data->grammar = insert_grammar();
	data->envlist = init_envlist(envp);
	data->exit_code = 0;
	return (data);
}

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	t_syntax_tree	*ast;
	char			*input;

	atexit(leaks);
	if (argc != 1)
		exit(EXIT_FAILURE);
	print_welcome_title();
	(void)argv;
	//signal();
	data = init_data(envp);
	while (1)
	{
		input = readline(BLUE "deepshell" CYAN "$ " RESET);
		ast = parser(data->lr_table, data->grammar, input/*, data->envlist*/);
		if (ast == NULL)
			continue ;
		add_history(input);
		free(input);
		data->exit_code = execute(ast, data->envlist);
		free_syntax_tree(ast);
	}
}
