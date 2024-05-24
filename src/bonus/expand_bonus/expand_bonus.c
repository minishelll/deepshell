/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:20:26 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "expand_bonus.h"
#include "ft_error_bonus.h"

static int	_remove_empty_str(t_list *split)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = split;
	while (curr != NULL)
	{
		if (((t_token *)curr->content)->word[0] == '\0')
		{
			free_token(curr->content);
			curr->content = NULL;
		}
		else
			i++;
		curr = curr->next;
	}
	return (i);
}

static char	**_apply_cmds(t_list *split)
{
	const int	size = _remove_empty_str(split);
	char		**new;
	t_list		*curr;
	int			i;

	new = NULL;
	if (size != 0)
	{
		new = (char **)ft_calloc(sizeof(char *), size + 1);
		i = 0;
		curr = split;
		while (curr != NULL)
		{
			if (curr->content != NULL)
			{
				new[i] = ((t_token *)curr->content)->word;
				i++;
			}
			curr = curr->next;
		}
	}
	ft_lstclear(&split, free);
	return (new);
}

static char	**expand_command(char **cmds, t_env *env)
{
	t_list	*total;
	t_list	*split;
	int		i;

	total = NULL;
	i = 0;
	while (cmds[i] != NULL)
	{
		if (ft_strchr(cmds[i], '$') == NULL && ft_strchr(cmds[i], '*') == NULL \
		&& ft_strchr(cmds[i], '\'') == NULL && ft_strchr(cmds[i], '"') == NULL)
			ft_lstadd_back(&total, \
							ft_lstnew(new_token(ft_strdup(cmds[i]), word)));
		else
		{
			split = expand_one_word(cmds[i], env);
			ft_lstadd_back(&total, split);
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
	return (_apply_cmds(total));
}

static int	expand_redirection(t_list *redilist, t_env *env)
{
	t_redi	*curr;
	t_list	*expand;

	while (redilist != NULL)
	{
		curr = redilist->content;
		if (ft_strchr(curr->file, '$') != NULL \
		|| ft_strchr(curr->file, '*') != NULL \
		|| ft_strchr(curr->file, '\'') != NULL \
		|| ft_strchr(curr->file, '"') != NULL)
		{
			expand = expand_one_word(curr->file, env);
			if (expand->next != NULL)
			{
				ft_lstclear(&expand, free_token);
				return (ft_error(error_ambiguous_redirection, 0, curr->file));
			}
			curr->file = ((t_token *)expand->content)->word;
			ft_lstdelone(expand, free);
		}
		redilist = redilist->next;
	}
	return (0);
}

int	expand(t_syntax_tree *command, t_env *env)
{
	int	result;

	if (command->child[R] != NULL)
	{
		result = expand_redirection(command->child[R], env);
		if (result == 1)
			return (1);
	}
	command->child[L] = expand_command(command->child[L], env);
	return (0);
}
