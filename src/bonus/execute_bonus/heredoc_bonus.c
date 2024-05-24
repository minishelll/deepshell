/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:19:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "execute_bonus.h"
#include "ft_error_bonus.h"

static int	_find_heredoc(t_list *redilist, int cnt)
{
	int	result;

	while (redilist != NULL)
	{
		if (((t_redi *)redilist->content)->type == here_doc)
		{
			cnt += 1;
			result = heredoc_process(redilist->content, cnt);
			if (result == 1)
				return (1);
		}
		redilist = redilist->next;
	}
	return (0);
}

static void	_recursive_heredoc(t_syntax_tree *curr, t_env *env
								, int *cnt, int *sig)
{
	int	result;

	if (*sig == 1)
		return ;
	if (curr->type == sym_command || curr->type == sym_subshell)
	{
		result = _find_heredoc(curr->child[R], *cnt);
		if (result == 1)
		{
			*sig = 1;
			return ;
		}
		*cnt += result;
		return ;
	}
	_recursive_heredoc(curr->child[L], env, cnt, sig);
	_recursive_heredoc(curr->child[R], env, cnt, sig);
}

int	execute_heredoc(t_syntax_tree *root, t_env *env)
{
	int	sig;
	int	cnt;

	sig = 0;
	cnt = 0;
	_recursive_heredoc(root, env, &cnt, &sig);
	if (sig == 1)
		return (1);
	return (0);
}
