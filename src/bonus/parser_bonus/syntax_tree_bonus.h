/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:05:51 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_TREE_BONUS_H
# define SYNTAX_TREE_BONUS_H

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
	t_redi_type		type;
	char			*file;
}					t_redi;

/* ********************************* COMMAND ******************************** */
# define INIT -1
# define INFILE 0
# define OUTFILE 1

/* ****************************** SYNTAX TREE  ****************************** */
# define L 0
# define R 1

typedef enum e_symbol
{
	sym_or,
	sym_and,
	sym_pipe,
	sym_command,
	sym_subshell
}	t_symbol;

typedef struct s_syntax_tree
{
	t_symbol	type;
	void		*child[2];
}	t_syntax_tree;

#endif