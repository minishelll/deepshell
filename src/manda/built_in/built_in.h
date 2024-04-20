/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:59:11 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 13:51:41 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

/* ******************************** TYPEDEF ********************************* */
typedef enum e_bi_type
{
	none = -1,
	bi_echo,
	bi_cd,
	bi_pwd,
	bi_export,
	bi_unset,
	bi_env,
	bi_exit
}	t_bi_type;

typedef int (*t_built_in)(char **, char **);

/* ******************************* FUNCTIONS ******************************** */
int			execute_built_in(char **cmds, char **envlist, t_bi_type type);
t_bi_type	is_built_in(char *cmdname);

int			ft_echo(char **cmds, char **envlist);
int			ft_cd(char **cmds, char **envlist);
int			ft_pwd(char **cmds, char **envlist);
int			ft_export(char **cmds, char **envlist);
int			ft_unset(char **cmds, char **envlist);
int			ft_env(char **cmds, char **envlist);
int			ft_exit(char **cmds, char **envlist);

//◦ echo with option -n
//◦ cd with only a relative or absolute path
//◦ pwd with no options
//◦ export with no options
//◦ unset with no options
//◦ env with no options or arguments
//◦ exit with no options

#endif