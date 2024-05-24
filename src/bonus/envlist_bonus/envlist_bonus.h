/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:55:39 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLIST_BONUS_H
# define ENVLIST_BONUS_H

# include <stdbool.h>

typedef struct s_env
{
	char	**envlist;
	int		exit_code;
}			t_env;

# define NO_SPECIFIC_CHAR -1

/* ******************************* FUNCTIONS ******************************** */
char	**init_envlist(char **envp);
char	**add_envlist(char **envlist, char *add);
bool	delete_envlist(char **envlist, char *target);
bool	update_envlist(char **envlist, char *target, char *data);
char	*find_env(char **envlist, char *name);
/* util */
int		_get_size(char **envlist);
int		_find_empty_space(char **envlist);
int		_find_specific_char(char *str);

#endif