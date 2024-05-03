/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:20:26 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/03 17:18:38 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "expand.h"
#include "ft_error.h"

static bool	_check_symbol(char *word)
{
	if (ft_strchr(word, '$') != NULL \
	|| ft_strchr(word, '*') != NULL \
	|| ft_strchr(word, '\'') != NULL \
	|| ft_strchr(word, '"') != NULL)
		return (true);
	return (false);
}

static int	expand_redirection(t_list *redilist, t_env *env)
{
	t_redi	*curr;
	t_list	*expand;

	while (redilist != NULL)
	{
		curr = redilist->content;
		if (_check_symbol(curr->file) == true)
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

static char	**_apply_cmds(t_list *split)
{
	char	**new;
	t_list	*tmp;
	int		i;

	new = (char **)ft_calloc(sizeof(char *), ft_lstsize(split) + 1);
	i = 0;
	while (split != NULL)
	{
		if (((t_token *)split->content)->type == undefined)
			free(((t_token *)split->content)->word);
		else
		{
			new[i] = ((t_token *)split->content)->word;
			i++;
		}
		tmp = split;
		split = split->next;
		ft_lstdelone(tmp, free);
	}
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
		if (_check_symbol(cmds[i]) == false)
			ft_lstadd_back(&total, ft_lstnew( \
									new_token(ft_strdup(cmds[i]), word)));
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
