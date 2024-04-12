/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:01:10 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/12 15:35:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include "execute.h"
#include "ft_error.h"

//static void	_here_doc(char *delimiter)
//{
//	const int	len = ft_strlen(delimiter);
//	char		*in;
//	int			tmpfile;

//	tmpfile = open(TMPFILE_IN_HOMEDIR, O_CREAT | O_WRONLY | O_TRUNC, 0644);
//	if (tmpfile == ERROR)
//		ft_error(error_file, TMPFILE_IN_HOMEDIR);
//	while (1)
//	{
//		//in = readline("> ");
//		//if (in == NULL)
//		//	break ;
//		if (ft_strncmp(delimiter, in, len) == 0 && in[len] == '\n')
//		{
//			free(in);
//			break ;
//		}
//		write(tmpfile, in, ft_strlen(in));
//		free(in);
//	}
//	close(tmpfile);
//}

static void	_update_redi(int *org, int *new)
{
	if (org[INFILE] != new[INFILE])
	{
		if (org[INFILE] != INIT)
			close(org[INFILE]);
		org[INFILE] = new[INFILE];
	}
	if (org[OUTFILE] != new[OUTFILE])
	{
		if (org[OUTFILE] != INIT)
			close(org[OUTFILE]);
		org[OUTFILE] = new[OUTFILE];
	}
}

static int	_handle_open(t_redi *curr, int *redi, bool *error)
{
	int	tmp[2];

	errno = 0;
	if (curr->type == input)
		tmp[INFILE] = open(curr->file, O_RDONLY);
	else if (curr->type == here_doc)
	{
		//_here_doc(curr->file);
		tmp[INFILE] = open(TMPFILE_IN_HOMEDIR, O_RDONLY, 0644);
		//heredoc은 즉시 끝낼지 고민된다
	}
	else if (error[OUTFILE] == false)
	{
		if (curr->type == output)
			tmp[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else if (curr->type == append)
			tmp[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	if (errno != 0)
		return (curr->type);
	_update_redi(redi, tmp);
	return (CONTINUE);
}

void	open_file(t_list *redi_list, int *redi)
{
	int		record_errno;
	char	*record_target;
	bool	error[2];
	int		check;

	redi[INFILE] = INIT;
	redi[OUTFILE] = INIT;
	record_errno = INIT;
	error[INFILE] = false;
	error[OUTFILE] = false;
	while (redi_list != NULL)
	{
		check = _handle_open(redi_list->content, redi, error);
		if (check != CONTINUE && record_errno == INIT)
		{
			record_errno = errno;
			record_target = ((t_redi *)redi_list->content)->file;
			error[check % 2] = true;
			break ;
		}
		redi_list = redi_list->next;
	}
	if (record_errno != INIT)
		ft_error(error_redirection, record_errno, record_target);
}
