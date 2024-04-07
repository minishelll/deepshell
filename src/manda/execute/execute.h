/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/07 19:05:05 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "syntax_tree.h"

# define TMPFILE_IN_HOMEDIR "/Users/taerakim/tmp"
# define CONTINUE -1
# define PIPE_END -1
# define PIPE_ALL -1

typedef enum e_pipe_order
{
	parent = -1,
	start,
	middle,
	end
}	t_pipe_order;

int		execute(t_syntax_tree *root);

int		execute_only_command(t_syntax_tree *command);
int		execute_command(t_syntax_tree *command, int *pipe_fd, int cnt
												, t_pipe_order order);
void	close_rest_pipe(int *pipe_fd, int order);

int		wait_process(int last_child, int *pipe_fd);
void	start_process(t_syntax_tree *command, int *pipe_fd, int cnt, int *redi);
void	mid_process(t_syntax_tree *command, int *pipe_fd, int cnt, int *redi);
void	end_process(t_syntax_tree *command, int *pipe_fd, int *redi);

void	open_file(t_redi *redi_list, int *redi);

#endif