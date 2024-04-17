/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/17 13:26:21 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "syntax_tree.h"
# include "libft.h"

# define TMPFILE_IN_HOMEDIR "/Users/taerakim/tmp"
//# define TMPFILE_IN_HOMEDIR "$(HOME)/tmp"
# define CONTINUE -1
# define PIPE_END -1
# define PIPE_ALL -1

# define READ 0
# define WRITE 1

typedef enum e_pipe_order
{
	parent = -1,
	start,
	middle,
	end
}	t_pipe_order;

int		execute(t_syntax_tree *root);

int		execute_subshell(t_syntax_tree *curr, int *pipe_fd, int cnt \
													, t_pipe_order order);

int		execute_only_command(t_syntax_tree *command);
int		execute_command(t_syntax_tree *command, int *pipe_fd, int cnt
												, t_pipe_order order);

int		wait_process(int last_child, int *pipe_fd);
void	start_process(char **cmds, int *pipe_fd, int cnt, int *redi);
void	mid_process(char **cmds, int *pipe_fd, int cnt, int *redi);
void	end_process(char **cmds, int *pipe_fd, int *redi);

void	open_file(t_list *redi_list, int *redi);

void	close_rest_pipe(int *pipe_fd, int order);
void	close_redirect_file(int *redi);

#endif