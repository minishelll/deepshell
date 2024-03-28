/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:57:49 by taerankim         #+#    #+#             */
/*   Updated: 2024/03/28 15:14:03 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_words(char **dst)
{
	int	i;

	i = 0;
	while (dst[i] != NULL)
	{
		free(dst[i]);
		i++;
	}
	free(dst);
}

/* * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE *DELET* */
/* * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE *DELET* */
/* * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE * DELETE HERE *DELET* */
#include <stdio.h>
#include "insert_data.h"

/* ******************************* TEST LR_TABLE ******************************* */
/*
*/
void	print_one_t_grammar(t_kind kind, int type)
{
	if (kind == none)
		printf("none,         ");
	else if (kind == terminal)
	{
		printf("TERMINAL,     ");
		if (type == 0)
			printf("and_if");
		else if (type == 1)
			printf("or_if");
		else if (type == 2)
			printf("pipe");
		else if (type == 3)
			printf("lparen");
		else if (type == 4)
			printf("rparen");
		else if (type == 5)
			printf("word");
		else if (type == 6)
			printf("less");
		else if (type == 7)
			printf("great");
		else if (type == 8)
			printf("dgreat");
		else if (type == 9)
			printf("dless");
	}
	else if (kind == non_terminal)
	{
		printf("NON_TERMINAL, ");
		if (type == 0)
			printf ("complete_command");
		else if (type == 1)
			printf ("and_or");
		else if (type == 2)
			printf ("pipeline");
		else if (type == 3)
			printf ("command");
		else if (type == 4)
			printf ("subshell");
		else if (type == 5)
			printf ("simple_command");
		else if (type == 6)
			printf ("cmd_word");
		else if (type == 7)
			printf ("cmd_suffix");
		else if (type == 8)
			printf ("redirect_list");
		else if (type == 9)
			printf ("io_redirect");
		else if (type == 10)
			printf ("io_file");
		else if (type == 11)
			printf ("filename");
		else if (type == 12)
			printf ("io_here");
		else if (type == 13)
			printf ("here_end");
	}
	printf(" | ");

}

int main()
{
	t_grammar *grammar = insert_grammar();

	for (int i = 0; i < GRAMMAR; i++)
	{
		printf("BEFORE: ");
		print_one_t_grammar(non_terminal, grammar[i].before);
		printf("\n");
		for (int k = 0; k < 3; k++)
		{
			printf("AFTER: ");
			print_one_t_grammar(grammar[i].after[k][KIND], grammar[i].after[k][TYPE]);
		}
		printf("\n");
	}
	free(grammar);
	system("leaks minishell");
}

/* ******************************* TEST LR_TABLE ******************************* */
/*

void	print_one_t_action(t_action dst)
{
	if (dst.act == shift)
		printf("S, ");
	else if (dst.act == reduce)
		printf("R, ");
	else if (dst.act == grammar)
		printf("(G), ");
	if (dst.act == init)
		return ;
	printf("%d", dst.num);
}

int main()
{
	t_lr_table *lr_table;

	lr_table = insert_lr_table();
	for (int i = 0; i < ROW_STATE; i++)
	{
		for (int k = 0; k < COL_ACT; k++)
		{
			print_one_t_action(lr_table->action[i][k]);
			printf(" | ");
		}
		free(lr_table->action[i]);
		printf("\n");
	}
	free(lr_table->action);
	for (int i = 0; i < ROW_STATE; i++)
	{
		for (int k = 0; k < COL_GOTO; k++)
		{
			print_one_t_action(lr_table->go_to[i][k]);
			printf(" | ");
		}
		free(lr_table->go_to[i]);
		printf("\n");
	}
	free(lr_table->go_to);
	free(lr_table);
	system("leaks minishell");
	return (-1);
}
*/
