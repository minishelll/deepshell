/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:00 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/10 19:45:29 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEMANTIC_ANALYZER_H
# define SEMANTIC_ANALYZER_H

# include "tokenizer.h"
# include "syntax_analyzer.h"
# include "syntax_tree.h"
# include "libft.h"
# include "stdbool.h"

//semantic_analyzer.c
t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree);
t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree);
void			make_redi_list(t_list **redi_list, t_parse_tree *parse_tree);
void			make_word_list(t_list **cmd, t_list **redi, \
								t_parse_tree *parse_tree);

//semantic_analyzer_utils.c
t_syntax_tree	*syntax_tree_new(t_termi type);
void			make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree);
void			*make_redi_node(t_parse_tree *parse_tree);
bool			is_subshell(t_parse_tree *parse_tree);
t_syntax_tree	*make_subshell_node(t_parse_tree *parse_tree);
#endif