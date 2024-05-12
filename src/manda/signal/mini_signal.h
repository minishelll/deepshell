/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:30:27 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/11 21:42:28 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

int	g_signal;

//do_signal.c
void	do_sig_int(int signum);
void	do_sig_term(int signum, int exit_code);
void	do_sig_quit(int signum);
void	do_heredoc(int signum);

//set_signal.c
void	set_rl_signal(void);
void	set_signal_ignore(void);
void	set_child_signal(void);
void	set_heredoc_signal(void);

//mini_terminal.c
void	set_signal_print_on(void);
void	set_signal_ctrl_print_off(void);
void	set_signal_ctrl_print_on(void);

//sighander.c
void	sig_handler(int signo);
int		rl_sig_handler(void);
int		heredoc_sig_handler(void);

#endif