/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:19:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/29 23:27:50 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"

static char	*_get_tmpfilename(int order)
{
	char	*num;
	char	*res;

	num = ft_itoa(order + 1);
	res = ft_strjoin(TMPFILE, num);
	free(num);
	return (res);
}

static void	_input_heredoc(t_redi *redi, char *tmpfile)
{
	const int	len = ft_strlen(redi->file);
	char		*in;
	int			fd;

	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(error_systemcall, errno, NULL);
	while (1)
	{
		in = readline("> ");
		if (in == NULL)
			break ;
		if (ft_strncmp(redi->file, in, len + 1) == 0)
		{
			free(in);
			break ;
		}
		ft_putendl_fd(in, fd);
		free(in);
	}
	free(redi->file);
	close(fd);
}

void	heredoc_process(t_redi *redi, int order)
{
	char	*tmpfile;
	int		pid;

	tmpfile = _get_tmpfilename(order);
	pid = fork();
	if (pid == -1)
		ft_error(error_systemcall, errno, NULL);
	if (pid == 0)
	{
		_input_heredoc(redi, tmpfile);
		exit(0);//??
	}
	wait_process(pid, NULL);
	free(redi->file);
	redi->file = tmpfile;
}

int	_find_heredoc(t_list *redilist, int cnt)
{
	int	cntadd;

	cntadd = 0;
	while (redilist != NULL)
	{
		if (((t_redi *)redilist->content)->type == here_doc)
		{
			heredoc_process(redilist->content, cnt + cntadd);
			cntadd++;
		}
		redilist = redilist->next;
	}
	return (cntadd);
}

void	execute_heredoc(t_syntax_tree *root, int *cnt)
{
	int	cntadd;

	if (root->type == sym_command || root->type == sym_subshell)
	{
		cntadd = _find_heredoc(root->child[R], *cnt);
		*cnt += cntadd;
		return ;
	}
	execute_heredoc(root->child[L], cnt);
	execute_heredoc(root->child[R], cnt);
}
