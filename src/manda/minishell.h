/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:58:06 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 11:50:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "insert_data.h"

/* ********************************** DATA ********************************** */
typedef struct s_data
{
	t_lr_table	*lr_table;
	t_grammar	*grammar;
	char		**envlist;
	int			exit_code;
}				t_data;

//# define PROMPT "deepshell$ "

/* ****************************** PRINT_COLOR ******************************* */
# define RED      "\x1b[31m"
# define GREEN    "\x1b[32m"
# define YELLOW   "\x1b[33m"
# define BLUE     "\x1b[34m"
# define MAGENTA  "\x1b[35m"
# define CYAN     "\x1b[36m"
# define RESET    "\x1b[0m"

void	print_welcome_title(void);

#endif