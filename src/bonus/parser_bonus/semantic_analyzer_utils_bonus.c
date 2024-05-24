/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer_utils_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:38:39 by sehwanii          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "semantic_analyzer_bonus.h"

//make a new node of ast
t_syntax_tree	*syntax_tree_new(t_termi type)
{
	t_syntax_tree	*new_node;

	new_node = (t_syntax_tree *)ft_malloc(sizeof(t_syntax_tree));
	if (type == and_if)
		new_node->type = sym_and;
	else if (type == or_if)
		new_node->type = sym_or;
	else if (type == pipe_term)
		new_node->type = sym_pipe;
	else if (type == lparen)
		new_node->type = sym_subshell;
	else if (type == word)
		new_node->type = sym_command;
	return (new_node);
}

//make cmd node with child[L] : cmd_list, child[R] : redi_list
void	make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree)
{
	char	**cmds;
	t_list	*cmd_list;
	t_list	*tmp;
	t_list	*redi_list;
	int		size;

	cmd_list = NULL;
	redi_list = NULL;
	make_word_list(&cmd_list, &redi_list, parse_tree);
	size = ft_lstsize(cmd_list);
	cmds = (char **)ft_malloc(sizeof(char *) * (size + 1));
	cmds[size] = NULL;
	size = 0;
	tmp = cmd_list;
	while (cmd_list)
	{
		cmds[size++] = cmd_list->content;
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free(tmp);
	}
	node->child[L] = (void *)cmds;
	node->child[R] = redi_list;
}

//makes new redirection node
void	*make_redi_node(t_parse_tree *parse_tree)
{
	t_parse_tree	*io;
	t_parse_tree	*filename;
	t_redi			*redi_node;

	io = (t_parse_tree *)parse_tree->child[0];
	redi_node = (t_redi *)ft_malloc(sizeof(t_redi));
	if (((t_token *)io->child[0])->type == less)
		redi_node->type = input;
	else if (((t_token *)io->child[0])->type == dless)
		redi_node->type = here_doc;
	else if (((t_token *)io->child[0])->type == great)
		redi_node->type = output;
	else if (((t_token *)io->child[0])->type == dgreat)
		redi_node->type = append;
	filename = io->child[1];
	redi_node->file = ((t_token *)filename->child[0])->word;
	return (redi_node);
}

//if parse_tree->child[LEFT] == lparen, return 1
bool	is_subshell(t_parse_tree *parse_tree)
{
	t_parse_tree	*child;

	child = (t_parse_tree *)parse_tree->child[LEFT];
	if (child->type == subshell)
		return (true);
	else
		return (false);
}

//makes subshell_node with child[L] = syntax_tree, child[R] = redi_list
t_syntax_tree	*make_subshell_node(t_parse_tree *parse_tree)
{
	t_syntax_tree	*new_node;
	t_list			*redi_list;
	t_parse_tree	*sub_shell_tree;
	t_parse_tree	*redi_tree;

	sub_shell_tree = (t_parse_tree *)parse_tree->child[LEFT];
	if (parse_tree->child[MID])
	{
		redi_list = NULL;
		new_node = syntax_tree_new(lparen);
		new_node->child[L] = make_syntax_tree(sub_shell_tree->child[MID]);
		redi_tree = (t_parse_tree *)parse_tree->child[MID];
		make_redi_list(&redi_list, redi_tree->child[0]);
		new_node->child[R] = redi_list;
	}
	else
	{
		new_node = syntax_tree_new(lparen);
		new_node->child[L] = make_syntax_tree(sub_shell_tree->child[MID]);
		new_node->child[R] = NULL;
	}
	return (new_node);
}
