/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:16 by sehwjang          #+#    #+#             */
/*   Updated: 2024/04/29 21:05:31 by sehwjang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <stdlib.h>
#include "mini_signal.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	do_sig_int(int signum)
{
	g_signal = SIGINT;
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	do_sig_term(int signum, int exit_code)
{
	(void)signum;
	ft_putstr_fd("\033[1A", 2);
	ft_putstr_fd("\033[11C", 2);
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
}

void	do_sig_quit(int signum)
{
	(void)signum;
}

void	sig_handler(int signo, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;

	if (signo == SIGINT)
		g_signal = SIGINT;
	else if (signo == SIGTERM)
		g_signal = SIGTERM;
	else if (signo == SIGQUIT)
		g_signal = SIGQUIT;
	return ;
}

int	my_sig_handler(void)
{
	if (g_signal == SIGINT)
		do_sig_int(SIGINT);// Readline에게 입력 줄을 다시 그리도록 요청
	else if(g_signal == SIGTERM)
		printf("SIGTERM");
	else
		return (0);
	return (0);
}

void	set_parent_signal(void)
{
	struct sigaction	s_sigact;

	s_sigact.sa_flags = SA_SIGINFO;
	set_signal_print_off();
	sigfillset(&s_sigact.sa_mask);
	sigdelset(&s_sigact.sa_mask, SIGINT);
	sigdelset(&s_sigact.sa_mask, SIGTERM);
	sigdelset(&s_sigact.sa_mask, SIGQUIT);
	s_sigact.sa_flags = SA_RESTART;
	s_sigact.sa_sigaction = &sig_handler;
	sigaction(SIGINT, &s_sigact, NULL);
	sigaction(SIGTERM, &s_sigact, NULL);
	sigaction(SIGQUIT, &s_sigact, NULL);
	rl_signal_event_hook = my_sig_handler;
}

void	set_signal_ignore(void)
{
	struct sigaction	s_sigact;

	s_sigact.sa_flags = SA_SIGINFO;
	set_signal_print_on();
	sigemptyset(&s_sigact.sa_mask);
	sigdelset(&s_sigact.sa_mask, SIGINT);
	sigdelset(&s_sigact.sa_mask, SIGTERM);
	sigdelset(&s_sigact.sa_mask, SIGQUIT);
	s_sigact.sa_flags = SA_RESTART;
	s_sigact.sa_handler = SIG_IGN;
	sigaction(SIGINT, &s_sigact, NULL);
	sigaction(SIGTERM, &s_sigact, NULL);
	sigaction(SIGQUIT, &s_sigact, NULL);
	rl_signal_event_hook = my_sig_handler;
}

void	set_child_signal(void)
{
	struct sigaction	s_sigact;

	s_sigact.sa_flags = SA_SIGINFO;
	set_signal_print_on();
	sigemptyset(&s_sigact.sa_mask);
	sigdelset(&s_sigact.sa_mask, SIGINT);
	sigdelset(&s_sigact.sa_mask, SIGTERM);
	sigdelset(&s_sigact.sa_mask, SIGQUIT);
	s_sigact.sa_flags = SA_RESTART;
	s_sigact.sa_handler = SIG_DFL;
	sigaction(SIGINT, &s_sigact, NULL);
	sigaction(SIGTERM, &s_sigact, NULL);
	sigaction(SIGQUIT, &s_sigact, NULL);
}


