/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:48:46 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/12 13:49:16 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax_tree.h"
# include "minishell.h"

t_syntax_tree	*parser(t_data *data, char *input);
void			free_syntax_tree(t_syntax_tree *curr);
void			free_redi(void *redi);
#endif