/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:58:06 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "insert_data_bonus.h"
# include "envlist_bonus.h"

/* ********************************** DATA ********************************** */
typedef struct s_data
{
	t_lr_table	*lr_table;
	t_grammar	*grammar;
	t_env		*env;
}				t_data;

# define PROMPT "\033[36;1mdashell\033[0;37m$ \033[0m"

/* ************************** PRINT_WELCOME_TITLE *************************** */
# define OUTLINE    "\033[0;36m"
# define TITLE_ART  "\033[36;6m"
# define DASH3      "\033[0;30;m"
# define TITLE_TEXT "\033[37;7m"
# define CAT        "\033[0;30m"
# define HEART      "\033[0;31m"
# define BELL       "\033[0;33m"
# define NAME       "\033[30;1m"
# define RESET      "\033[0m"

void	print_welcome_title(void);

#endif