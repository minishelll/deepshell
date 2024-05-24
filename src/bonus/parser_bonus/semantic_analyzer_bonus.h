/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:00 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTIC_ANALYZER_BONUS_H
# define SEMANTIC_ANALYZER_BONUS_H

# include "syntax_analyzer_bonus.h"
# include "syntax_tree_bonus.h"

/* ******************************* FUNCTIONS ******************************** */
/* semantic_analyzer.c */
t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree);
t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree);
void			make_redi_list(t_list **redi_list, t_parse_tree *parse_tree);
void			make_word_list(t_list **cmd, t_list **redi, \
								t_parse_tree *parse_tree);
/* semantic_analyzer_utils.c */
t_syntax_tree	*syntax_tree_new(t_termi type);
void			make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree);
void			*make_redi_node(t_parse_tree *parse_tree);
bool			is_subshell(t_parse_tree *parse_tree);
t_syntax_tree	*make_subshell_node(t_parse_tree *parse_tree);

#endif