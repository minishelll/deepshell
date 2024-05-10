/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:30:27 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/10 15:39:46 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_H
# define MINI_SIGNAL_H

int	g_signal;

// void	signal_init();
void	set_rl_signal(void);
void	set_child_signal(void);
void	set_signal_ignore(void);
void	term_init();
void	do_sig_int(int signum);
void	do_sig_term(int signum, int exit_code);
void	do_sig_quit(int signum);
void	init_signal(void);
void	set_heredoc_signal(void);
void	do_heredoc(int signum);

void    set_signal_print_on(void);
void	set_signal_ctrl_print_off(void);
void	set_signal_ctrl_print_on(void);

#endif