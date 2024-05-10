/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:19:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/10 16:27:02 by sehwjang         ###   ########.fr       */
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

	num = ft_itoa(order);
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
		in = readline("> \033[s");
		if (in == NULL)
		{
    		printf("\033[u\033[1B\033[1A");
			break ;
		}

		if (g_signal == SIGINT)
			do_heredoc(SIGINT);
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
	exit(0);
}

//int	heredoc_process(t_redi *redi, int order)
//{
//	char	*tmpfile;
//	int		result;
//	int		pid;

//	tmpfile = _get_tmpfilename(order);
//	pid = fork();
//	if (pid == -1)
//		ft_error(error_systemcall, errno, NULL);
//	if (pid == 0)
//	{
//		_input_heredoc(redi, tmpfile);
//		exit(0);//??
//	}
//	result = wait_process(pid, NULL);
//	free(redi->file);
//	redi->file = tmpfile;
//	return (result);
//}

int	_find_heredoc(t_list *redilist, int cnt)
{
	char	*tmpfile;
	int		result;
	int		pid;

	while (redilist != NULL)
	{
		if (((t_redi *)redilist->content)->type == here_doc)
		{
			cnt += 1;
			tmpfile = _get_tmpfilename(cnt);
			pid = fork();
			if (pid == -1)
				ft_error(error_systemcall, errno, NULL);
			if (pid == 0)
				_input_heredoc(redilist->content, tmpfile);
			result = wait_process(pid, NULL);
			free(((t_redi *)redilist->content)->file);
			((t_redi *)redilist->content)->file = tmpfile;
			if (result == 1)
			{
				g_signal = 0;
				return (1);
			}
		}
		redilist = redilist->next;
	}
	return (0);
}

void	_recursive_heredoc(t_syntax_tree *curr, t_env *env, int *cnt, int *sig)
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
