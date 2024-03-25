/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:01:48 by taerakim          #+#    #+#             */
/*   Updated: 2024/03/25 13:33:45 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* ******************************** LITERAL ********************************* */
# define S_PIPE "|"
# define S_AND_IF "&&"
# define S_OR_IF "||"
# define S_LESS "<"
# define S_DLESS "<<"
# define S_GREAT ">"
# define S_DGREAT ">>"
# define S_LPAREN "("
# define S_RPAREN ")"

/* ********************************** TYPE ********************************** */
# define TERMINAL 0
# define NON_TERMINAL 1

enum e_terminal
{
	and_if = 0,
	or_if,
	pipe,
	lparen,
	rparen,
	name,
	word,
	assignment_word,
	less,
	great,
	dgreat,
	dless,
	dollar_sign
};

enum e_non_terminal
{
	complete_command = 0,
	and_or,
	pipeline,
	command,
	compound_command,
	subshell,
	name,
	simple_command,
	cmd_name,
	cmd_word,
	cmd_prefix,
	cmd_suffix,
	redirect_list,
	io_redirect,
	io_file,
	filename,
	io_here,
	here_end
};

typedef enum e_terminal		t_termi;
typedef enum e_non_terminal	t_ntermi;

/* ********************************* STRUCT ********************************* */
# define FRONT 0
# define MID 1
# define BACK 2

typedef struct s_token
{
	t_termi	type;
	char	*word;
}			t_token;

typedef struct s_parse_tree
{
	t_ntermi	type;
	bool		child_type[3];
	void		*child[3];
}				t_parse_tree;

#endif