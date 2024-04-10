/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:01:10 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 15:42:33 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
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

static void	_handle_file_open(t_redi *curr, int *redi)
{
	if (curr->type == input)
		redi[INFILE] = open(curr->file, O_RDONLY);
	else if (curr->type == here_doc)
	{
		//_here_doc(curr->file);
		redi[INFILE] = open(TMPFILE_IN_HOMEDIR, O_RDONLY, 0644);
	}
	if (errno != 0)
	{
		ft_error(error_infile, curr->file);
		errno = 0;
		return ;
	}
	if (curr->type == output)
		redi[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (curr->type == append)
		redi[OUTFILE] = open(curr->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (errno != 0)
		ft_error(error_outfile, curr->file);
}

void	open_file(t_list *redi_list, int *redi)
{
	t_list	*curr;
	int		tmp[2];
	//bool	infile_error; //이거 켜져있으면 뒤에 열기는 하되 에러출력 X 심지어 out에러시... 안만들긴 하네... 시불ㅋㅋㅋㅋㅋㅋㅋㅋㅋ

	redi[INFILE] = INIT;
	redi[OUTFILE] = INIT;
	curr = redi_list;
	while (curr != NULL)
	{
		tmp[INFILE] = redi[INFILE]; 
		tmp[OUTFILE] = redi[OUTFILE]; 
		_handle_file_open(curr->content, tmp);
		if (redi[INFILE] != tmp[INFILE])
		{
			if (redi[INFILE] != INIT)
				close(redi[INFILE]);
			redi[INFILE] = tmp[INFILE];
		}
		if (redi[OUTFILE] != tmp[OUTFILE])
		{
			if (redi[OUTFILE] != INIT)
				close(redi[OUTFILE]);
			redi[OUTFILE] = tmp[OUTFILE];
		}
		curr = curr->next;
	}
}
