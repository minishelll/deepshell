/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:59:11 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/02 22:32:57 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "envlist.h"

/* ******************************** TYPEDEF ********************************* */
typedef enum e_bi_type
{
	bi_none = -1,
	bi_echo,
	bi_cd,
	bi_pwd,
	bi_export,
	bi_unset,
	bi_env,
	bi_exit
}	t_bi_type;

# define SPECIFIC_CHAR_X 0
# define SPECIFIC_CHAR_O 1

typedef enum e_atol_res
{
	success,
	not_numeric
}	t_atol_res;

/* ******************************* FUNCTIONS ******************************** */
int	execute_built_in(char **cmds, t_env *env, t_bi_type type, int *redi);
t_bi_type	is_built_in(char *cmdname);

typedef int (*t_built_in)(char **, t_env *);
int			ft_echo(char **cmds, t_env *env);
int			ft_cd(char **cmds, t_env *env);
int			ft_pwd(char **cmds, t_env *env);
int			ft_export(char **cmds, t_env *env);
int			ft_unset(char **cmds, t_env *env);
int			ft_env(char **cmds, t_env *env);
int			ft_exit(char **cmds, t_env *env);

//◦ echo with option -n
//◦ cd with only a relative or absolute path
//◦ pwd with no options
//◦ export with no options
//◦ unset with no options
//◦ env with no options or arguments
//◦ exit with no options

#endif