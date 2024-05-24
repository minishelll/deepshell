/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_signal_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:53:39 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdlib.h>
#include "mini_signal_bonus.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>

void	do_sig_int(int signum)
{
	g_signal = SIGINT;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	do_sig_term(int signum, int exit_code)
{
	ft_putstr_fd("\033[1A", 2);
	ft_putstr_fd("\033[9C", 2);
	ft_putstr_fd("exit\n", 2);
	exit(exit_code);
	(void)signum;
}

void	do_sig_quit(int signum)
{
	(void)signum;
}

void	do_heredoc(int signum)
{
	set_signal_print_on();
	ft_putstr_fd("\n", 1);
	exit(1);
	(void)signum;
}
