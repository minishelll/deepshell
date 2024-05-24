/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_grammar_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:22:54 by taerankim         #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSERT_GRAMMAR_BONUS_H
# define INSERT_GRAMMAR_BONUS_H

# define GRAMMAR_0  "complete_command -> and_or"
# define GRAMMAR_1  "and_or -> pipeline"
# define GRAMMAR_2  "and_or -> and_or AND_IF pipeline"
# define GRAMMAR_3  "and_or -> and_or OR_IF pipeline"
# define GRAMMAR_4  "pipeline -> command"
# define GRAMMAR_5  "pipeline -> pipeline PIPE command"
# define GRAMMAR_6  "command -> simple_command"
# define GRAMMAR_7  "command -> subshell"
# define GRAMMAR_8  "command -> subshell redirect_list"
# define GRAMMAR_9  "subshell -> LPAREN and_or RPAREN"
# define GRAMMAR_10 "simple_command -> redirect_list cmd_word cmd_suffix"
# define GRAMMAR_11 "simple_command -> redirect_list cmd_word"
# define GRAMMAR_12 "simple_command -> redirect_list"
# define GRAMMAR_13 "simple_command -> cmd_word cmd_suffix"
# define GRAMMAR_14 "simple_command -> cmd_word"
# define GRAMMAR_15 "cmd_word -> WORD"
# define GRAMMAR_16 "cmd_suffix -> io_redirect"
# define GRAMMAR_17 "cmd_suffix -> cmd_suffix io_redirect"
# define GRAMMAR_18 "cmd_suffix -> WORD"
# define GRAMMAR_19 "cmd_suffix -> cmd_suffix WORD"
# define GRAMMAR_20 "redirect_list -> io_redirect"
# define GRAMMAR_21 "redirect_list -> redirect_list io_redirect"
# define GRAMMAR_22 "io_redirect -> io_file"
# define GRAMMAR_23 "io_redirect -> io_here"
# define GRAMMAR_24 "io_file -> LESS filename"
# define GRAMMAR_25 "io_file -> GREAT filename"
# define GRAMMAR_26 "io_file -> DGREAT filename"
# define GRAMMAR_27 "filename -> WORD"
# define GRAMMAR_28 "io_here -> DLESS here_end"
# define GRAMMAR_29 "here_end -> WORD"

#endif