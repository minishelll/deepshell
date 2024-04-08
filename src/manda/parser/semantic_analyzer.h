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

t_syntax_tree	*semantic_analyzer(t_parse_tree *parse_tree);

#endif