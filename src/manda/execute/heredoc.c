/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:19:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/08 18:18:58 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "execute.h"
#include "ft_error.h"
#include "mini_signal.h"

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

	set_heredoc_signal();
	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		ft_error(error_systemcall, errno, NULL);
	while (1)
	{
		in = readline("> ");
		if (g_signal == SIGINT)
			exit(1) ;
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
	set_signal_print_on();
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
			if (g_signal == SIGINT)
				return (-1);
			heredoc_process(redilist->content, cnt + cntadd);
			cntadd++;
		}
		redilist = redilist->next;
	}
	return (cntadd);
}

void	execute_heredoc(t_syntax_tree *root, int *cnt, t_env *env)
{
	int	cntadd;
	int	sig;

	if (root->type == sym_command || root->type == sym_subshell)
	{
		sig = _find_heredoc(root->child[R], *cnt);
		if (sig == -1)
			return ;
		cntadd = sig;
		*cnt += cntadd;
		return ;
	}
	execute_heredoc(root->child[L], cnt, env);
	execute_heredoc(root->child[R], cnt, env);
}
