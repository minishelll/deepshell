/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:01:10 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 13:55:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include "execute.h"
#include "ft_error.h"

static void	_here_doc(char *delimiter)
{
	const int	len = ft_strlen(delimiter);
	char		*in;
	int			tmpfile;

	tmpfile = open(TMPFILE_IN_HOMEDIR, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmpfile == ERROR)
		ft_error(error_file, TMPFILE_IN_HOMEDIR);
	while (1)
	{
		in = readline("> ");
		//if (in == NULL)
		//	break ;
		if (ft_strncmp(delimiter, in, len) == 0 && in[len] == '\n')
		{
			free(in);
			break ;
		}
		write(tmpfile, in, ft_strlen(in));
		free(in);
	}
	close(tmpfile);
}

static void	_handle_file_open(t_redi *curr, int *redi)
{
	if (curr->type == input)
		redi[INFILE] = open(curr->file, O_RDONLY);
	else if (curr->type == here_doc)
	{
		_here_doc(curr->file);
		redi[INFILE] = open(TMPFILE_IN_HOMEDIR, O_RDONLY, 0644);
	}
	else if (curr->type == output)
		redi[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (curr->type == append)
		redi[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (errno != 0)
		ft_error(error_file, curr->file);
}

int	open_file(t_redi *redi_list, int *redi)
{
	t_redi	*curr;
	int		prevfile;

	redi[INFILE] = INIT;
	redi[OUTFILE] = INIT;
	curr = redi_list;
	while (curr != NULL)
	{
		prevfile = redi[INFILE]; 
		prevfile = redi[OUTFILE]; 
		_handle_file_open(curr, redi);
		if (prevfile != redi[INFILE])
			close(prevfile);
		if (prevfile != redi[OUTFILE])
			close(prevfile);
		curr = curr->next;
	}
}
