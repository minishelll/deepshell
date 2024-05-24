/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 17:53:57 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BONUS_H
# define EXECUTE_BONUS_H

# include "syntax_tree_bonus.h"
# include "envlist_bonus.h"
# include "libft.h"

/* ******************************** DEFINE ********************************** */
# define TMPFILE "/tmp/tmp"
# define CONTINUE -1
# define PIPE_END -1
# define PIPE_ALL -1

/* ******************************** TYPEDEF ********************************* */
typedef enum e_pipe_order
{
	parent = -1,
	start,
	middle,
	end
}	t_pipe_order;

typedef struct s_pipe
{
	int	*pipelist;
	int	cnt;
}		t_pipe;

/* ******************************* FUNCTIONS ******************************** */
/* execute */
int		execute(t_syntax_tree *root, t_env *env);
int		execute_pipe(t_syntax_tree *curr, t_env *env, t_pipe *pipeinfo);
int		execute_subshell(t_syntax_tree *curr, t_env *env \
						, t_pipe *pipeinfo, t_pipe_order order);
int		execute_only_command(t_syntax_tree *command, t_env *env);
int		execute_command(t_syntax_tree *command, t_env *env \
						, t_pipe *pipeinfo, t_pipe_order order);
/* child */
typedef void	(*t_child_proc)(char **, t_env *, int *, int*);
void	single_process(char **cmds, t_env *env, int *redi);
void	start_process(char **cmds, t_env *env, int *use_pipe, int *redi);
void	mid_process(char **cmds, t_env *env, int *use_pipe, int *redi);
void	end_process(char **cmds, t_env *env, int *use_pipe, int *redi);
/* redirection & utils */
void	open_file(t_list *redi_list, int *redi);
char	*check_program(char **envlist, char *cmdname);
int		wait_process(int last_child, t_pipe *pipeinfo);
int		*handle_pipe(t_pipe *pipeinfo, t_pipe_order order);
void	close_redirect_file(int *redi);
/* heredoc */
int		execute_heredoc(t_syntax_tree *root, t_env *env);
int		heredoc_process(t_redi *redi, int order);

#endif