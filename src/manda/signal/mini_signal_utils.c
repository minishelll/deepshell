/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signal_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehwjang <sehwjang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:53:39 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/10 15:57:40 by sehwjang         ###   ########.fr       */
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

void	do_heredoc(int signum)
// heredoc에서 crtl+c 시그널 입력시 줄바꿈을 출력하고 1을 반환하며 종료됨
{
	(void)signum;
	set_signal_print_on();
	ft_putstr_fd("\n", 2); // 줄바꿈을 출력
	exit (1); // 1 을 반환하며 종료
}