/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:01:48 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_TYPE_BONUS_H
# define INPUT_TYPE_BONUS_H

/* ********************************** TYPE ********************************** */
typedef enum e_kind
{
	none = -1,
	terminal,
	non_terminal,
	state
}	t_kind;

typedef enum e_terminal
{
	and_if = 0,
	or_if,
	pipe_term,
	lparen,
	rparen,
	word,
	less,
	great,
	dgreat,
	dless,
	dollar_sign,
	undefined
}	t_termi;

typedef enum e_non_terminal
{
	complete_command = 0,
	and_or,
	pipeline,
	command,
	subshell,
	simple_command,
	cmd_word,
	cmd_suffix,
	redirect_list,
	io_redirect,
	io_file,
	filename,
	io_here,
	here_end
}	t_ntermi;

#endif