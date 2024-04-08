/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:05:51 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 14:20:00 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

/* ******************************* REDIRECTION ****************************** */
typedef enum e_redi_type
{
	input,
	output,
	here_doc,
	append
}	t_redi_type;

typedef struct s_redi
{
	t_redi_type	type;
	char		*file;
	t_redi		*next;
}				t_redi;

/* ********************************* COMMAND ******************************** */
# define INIT -1
# define INFILE 0
# define OUTFILE 1

//typedef struct s_cmd
//{
//	char	**cmds;
//	t_redi	*redi_list;
//	int		redi[2];//처음 생성시 INIT(-1)값 넣어주세요
//}			t_cmd;

/* ****************************** SYNTAX TREE  ****************************** */
# define L 0
# define R 1

typedef enum e_symbol
{
	sym_or,
	sym_and,
	sym_pipe,
	//sym_only_cmd,//본인 타입
	sym_command,//좌 char **cmds, 우 t_redi *redi_list
	sym_subshell//좌 and_or, 우 redi_list
}	t_symbol;

typedef struct s_syntax_tree
{
	t_symbol	type;
	//t_symbol	child_type[2];
	void		*child[2];
}	t_syntax_tree;

/* ******************************** FUNCTION  ******************************* */
// parser_main();

#endif