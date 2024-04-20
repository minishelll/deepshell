/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:55:39 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/20 13:26:28 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdbool.h>

/* ******************************* FUNCTIONS ******************************** */
char	**init_envlist(char **envp);
char	**add_envlist(char **envlist, char *add);
char	**delete_envlist(char **envlist, char *target);
bool	update_envlist(char **envlist, char *target, char *data);
char	*find_env(char **envlist, char *name);

#endif