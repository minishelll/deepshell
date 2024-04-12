/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:48:46 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/11 19:52:48 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "syntax_tree.h"
# include "insert_data.h"

t_syntax_tree	*parser(t_lr_table *lr_table, t_grammar *grammar, char *input);

#endif