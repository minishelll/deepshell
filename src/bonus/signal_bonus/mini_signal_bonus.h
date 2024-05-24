/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:30:27 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNAL_BONUS_H
# define MINI_SIGNAL_BONUS_H

# include <signal.h>

/* *************************** GLOBAL_VARIABLE ****************************** */
volatile sig_atomic_t	g_signal;

/* ******************************* FUNCTIONS ******************************** */
/* do_signal.c */
void	do_sig_int(int signum);
void	do_sig_term(int signum, int exit_code);
void	do_sig_quit(int signum);
void	do_heredoc(int signum);
/* set_signal.c */
void	set_rl_signal(void);
void	set_signal_ignore(void);
void	set_child_signal(void);
void	set_heredoc_signal(void);
/* mini_terminal.c */
void	set_signal_print_on(void);
void	set_signal_ctrl_print_off(void);
void	set_signal_ctrl_print_on(void);
/* sighander.c */
void	sig_handler(int signo);
int		rl_sig_handler(void);
int		heredoc_sig_handler(void);

#endif