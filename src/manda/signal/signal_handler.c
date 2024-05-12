/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:16 by sehwjang          #+#    #+#             */
/*   Updated: 2024/05/12 14:08:34 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_signal.h"

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

int	heredoc_sig_handler(void)
{
	if (g_signal == SIGINT)
		do_heredoc(SIGINT);
	return (0);
}
