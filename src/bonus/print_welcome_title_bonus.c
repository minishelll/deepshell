/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_welcome_title_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:57:23 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_bonus.h"

static void	_more(void)
{
	printf(TITLE_TEXT" dashell "RESET);
	printf(CAT"           > "RESET);
	printf(BELL"⦿"RESET);
	printf(CAT" <                   "RESET);
	printf(OUTLINE"│\n│               "RESET);
	printf(NAME" taerakim "RESET);
	printf(CAT"                           "RESET);
	printf(NAME" sehwjang "RESET);
	printf(CAT"                "RESET);
	printf(OUTLINE"│\n│                                                      "\
		"                        │\n╚─────────────────────────────────────────"\
		"─────────────────────────────────────╝\n"RESET);
}

void	print_welcome_title(void)
{
	printf(OUTLINE"╔─────────────────────────────────────────────────────────"\
		"─────────────────────╗\n│                                            "\
		"                                  │\n│                               "\
		"                                               │\n│                  "\
		"            "RESET);
	printf(TITLE_ART"█▀▀▄ ▄▀█ ▄▀▀ █▄▄█                               "RESET);
	printf(OUTLINE"│\n│                  "RESET);
	printf(CAT"/\\_/\\       "RESET);
	printf(TITLE_ART"░▄▄▀ █▀█ ▄░█ █░ █       "RESET);
	printf(CAT"/\\_/\\                   "RESET);
	printf(OUTLINE"│\n│                 "RESET);
	printf(CAT"( ~.o )             "RESET);
	printf(DASH3"---             "RESET);
	printf(CAT"( o.< )                  "RESET);
	printf(OUTLINE"│\n│                  "RESET);
	printf(CAT"> "RESET);
	printf(HEART"❤︎"RESET);
	printf(CAT" <           "RESET);
	_more();
}
