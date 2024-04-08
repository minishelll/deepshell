/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:07:09 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/08 17:39:22 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "semantic_analyzer.h"

static t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree);
static t_syntax_tree	*syntax_tree_new(t_termi type);
//static t_cmd			*syntax_cmd_new(void);
static void				make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree);
static void				traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree);
void					make_redi_list(t_list **redi_list, t_parse_tree *parse_tree);
void					*make_redi_node(t_parse_tree *parse_tree);

t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree)
{
	t_syntax_tree	*syntax_tree;
	int				idx;

	idx = 0;
	syntax_tree = (t_syntax_tree *)ft_malloc(sizeof(t_syntax_tree));
	return (make_syntax_tree(parse_tree));
}

static t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree)
{
	t_syntax_tree	*new_node;
	t_list			*redi_list;
	t_parse_tree	*temp;
	
	if (parse_tree->child_type[MID] == terminal)
	{
		new_node = syntax_tree_new(((t_token *)parse_tree->child[MID])->type);
		new_node->child[L] = make_syntax_tree(parse_tree->child[LEFT]);
		new_node->child[R] = make_syntax_tree(parse_tree->child[RIGHT]);
		return (new_node);
	}
	temp = (t_parse_tree *)parse_tree->child[LEFT];
	if (temp->type == subshell)
	{
		if (parse_tree->child[RIGHT])//io redirect
		{
			redi_list = NULL;
			new_node = syntax_tree_new(lparen);
			new_node->child[L] = make_syntax_tree(parse_tree->child[LEFT]);
			make_redi_list(&redi_list, parse_tree->child[LEFT]);
			new_node->child[R] = redi_list;
		}
		else
		{
			new_node = syntax_tree_new(lparen);
			new_node->child[L] = make_syntax_tree(temp->child[MID]);
		}
		return (new_node);
	}
	else if (parse_tree->type == simple_command)
	{
		new_node = syntax_tree_new(word);
		make_cmd_node(new_node, parse_tree);
		return (new_node);
	}
	else if (parse_tree->child_type[MID] == none)
	{
		if (parse_tree->child_type[LEFT] == terminal)
		{
			new_node = syntax_tree_new(((t_token *)parse_tree->child[MID])->type);
			return (new_node);
		}
		else if (parse_tree->child_type[LEFT] == non_terminal)
		{
			return (make_syntax_tree(parse_tree->child[LEFT]));
		}
	}
	return (NULL);
	/*
	1. 연산자가 나왔을 때
	2. simple_command가 나왔을 때
	3. subshell이 나왔을 때
	4. 디폴트 child 1
	*/
}
static t_syntax_tree	*syntax_tree_new(t_termi type)
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

// static t_cmd	*syntax_cmd_new(void)
// {
// 	t_cmd	*new_cmd;

// 	new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd));
// 	return (new_cmd);
// }

static void	make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree)
{
	char	**cmds;
	t_list	*cmd_list;
	t_list	*temp;
	t_list	*redi_list;
	int		size;

	cmd_list = NULL;
	redi_list = NULL;
	traversal_words(&cmd_list, &redi_list, parse_tree);
	size = ft_lstsize(cmd_list);
	cmds = (char **)ft_malloc(sizeof(char *) * (size + 1));
	cmds[size] = NULL;
	temp = cmd_list;
	size = 0;
	while (cmd_list)
	{
		cmds[size++] = cmd_list->content;
		cmd_list = cmd_list->next;
	}
	//ft_lstclear(&temp, free);
	node->child[0] = (void *)cmds;
	node->child[1] = redi_list;
}

static void	traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree)
{
	if (parse_tree->type == io_redirect)
	{
		make_redi_list(redi_list, parse_tree);
		return ;
	}
	if (parse_tree->child_type[0] == terminal)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(((t_token *)parse_tree->child[0])->word));
		return ;
	}
	traversal_words(cmd_list, redi_list, parse_tree->child[0]);
	if (parse_tree->child_type[1] == terminal)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(((t_token *)parse_tree->child[1])->word));
		return ;
	}
	if (parse_tree->child[1] != NULL)
		traversal_words(cmd_list, redi_list, parse_tree->child[1]);
}

void	*make_redi_node(t_parse_tree *parse_tree)
{
	t_parse_tree	*io;
	t_parse_tree	*filename;
	t_redi			*redi_node;
	//char			*debug;
	//t_token	*temp;
	//debug = 
	io = (t_parse_tree *)parse_tree->child[0];
	//temp = (t_token *)io->child[1];
	//io = io->child[0];
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
	//printf("%s!\n",((t_token *)io->child[1])->word);
	return (redi_node);
}

void	make_redi_list(t_list **redi_list, t_parse_tree *parse_tree)
{

	if (parse_tree->type == io_redirect)
	{
		ft_lstadd_back(redi_list, ft_lstnew(make_redi_node(parse_tree)));
		return ;
	}
	make_redi_list(redi_list, parse_tree->child[0]);
	if (parse_tree->child[1] != NULL)
		make_redi_list(redi_list, parse_tree->child[1]);
}
