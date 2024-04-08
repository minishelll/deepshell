/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic_analyzer.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:08:00 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/06 16:37:23 by sehwjang         ###   ########.fr       */
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
void			make_redi_list(t_list **redi_list, t_parse_tree *parse_tree);
void			traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree);
t_syntax_tree	*make_syntax_tree(t_parse_tree *parse_tree);
void            traversal_words(t_list **cmd_list, t_list **redi_list, t_parse_tree *parse_tree);

//semantic_analyzer_utils.c
t_syntax_tree	*syntax_tree_new(t_termi type);
void	        make_cmd_node(t_syntax_tree *node, t_parse_tree *parse_tree);
void	        *make_redi_node(t_parse_tree *parse_tree);
bool	    is_subshell(t_parse_tree *parse_tree);
t_syntax_tree	*make_subshell_node(t_parse_tree *parse_tree);
#endif