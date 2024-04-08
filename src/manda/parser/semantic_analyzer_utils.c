/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwanii <sehwanii@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-09 06:38:39 by sehwanii          #+#    #+#             */
/*   Updated: 2024-04-09 06:38:39 by sehwanii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "semantic_analyzer.h"
#include "stdbool.h"
t_syntax_tree	*syntax_tree_new(t_termi type)
{
	t_syntax_tree	*new_node;

	new_node = (t_syntax_tree *)ft_malloc(sizeof(t_syntax_tree));
	if (type == and_if)
		new_node->type = sym_and;
	else if (type == or_if)
		new_node->type = sym_or;
	else if (type == pipe)
		new_node->type = sym_pipe;
	else if (type == lparen)
		new_node->type = sym_subshell;
	else if (type == word)
		new_node->type = sym_command;
	return (new_node);
}

void	make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree)
{
	char	**cmds;
	t_list	*cmd_list;
	t_list	*redi_list;
	int		size;

	cmd_list = NULL;
	redi_list = NULL;
	traversal_words(&cmd_list, &redi_list, parse_tree);
	size = ft_lstsize(cmd_list);
	cmds = (char **)ft_malloc(sizeof(char *) * (size + 1));
	cmds[size] = NULL;
	size = 0;
	while (cmd_list)
	{
		cmds[size++] = cmd_list->content;
		cmd_list = cmd_list->next;
	}

	node->child[0] = (void *)cmds;
	node->child[1] = redi_list;
}

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

bool	is_subshell(t_parse_tree *parse_tree)
{
	t_parse_tree	*child;

	child = (t_parse_tree *)parse_tree->child[LEFT];
	if (child->type == subshell)
		return (true);
	else
		return (false);
}

t_syntax_tree	*make_subshell_node(t_parse_tree *parse_tree)
{
	t_syntax_tree	*new_node;
	t_list			*redi_list;
	t_parse_tree	*sub_shell_tree;

	sub_shell_tree = (t_parse_tree *)parse_tree->child[LEFT];
	if (parse_tree->child[MID])
	{
		redi_list = NULL;
		new_node = syntax_tree_new(lparen);
		new_node->child[L] = make_syntax_tree(sub_shell_tree->child[MID]);
		make_redi_list(&redi_list, ((t_parse_tree *)parse_tree->child[MID])->child[0]);
		new_node->child[R] = redi_list;
	}
	else
	{
		new_node = syntax_tree_new(lparen);
		new_node->child[L] = make_syntax_tree(sub_shell_tree->child[MID]);
	}
	return (new_node);
}