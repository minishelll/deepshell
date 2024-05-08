/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:16 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/08 17:56:38 by sehwjang         ###   ########.fr       */
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

void	sig_handler(int signo)
{
	if (signo == SIGINT)
		g_signal = SIGINT;
	else if (signo == SIGTERM)
		g_signal = SIGTERM;
	else if (signo == SIGQUIT)
		g_signal = SIGQUIT;
}

int	rl_sig_handler(void)
{
	if (g_signal == SIGINT)
		do_sig_int(SIGINT);
	return (0);
}

void	set_rl_signal(void)
{
	set_signal_print_off();
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, sig_handler);
	rl_signal_event_hook = rl_sig_handler;
}

int	heredoc_sig_handler(void)
{
	if (g_signal == SIGINT)
		do_heredoc(SIGINT);
	return (0);
}

void	set_signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_signal(void)
{
	int	i = 1;
	while (i < NSIG)
	{
		if (i != SIGKILL && i != SIGSTOP)
			signal(i, SIG_IGN);
		i++;
	}
}

void	set_heredoc_signal(void)
{
	if (g_signal == SIGINT)
		exit(1);
	signal(SIGINT, sig_handler);
	rl_signal_event_hook = heredoc_sig_handler;
}
