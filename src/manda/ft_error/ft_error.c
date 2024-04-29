/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:16:58 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/12 15:16:02 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ft_error.h"
#include "libft.h"

static void	_print_to_stderr(t_error_type errcase, int errnum, char *target)
{
	char	*message;

	if (errcase == error_redirection)
		message = strerror(errnum);
	if (errcase == error_access)
		message = "command not found";
	ft_putstr_fd("deepshell: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_error(t_error_type errcase, int errnum, char *target)
{
	if (errcase == error_systemcall)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	_print_to_stderr(errcase, errnum, target);
	if (errcase == error_redirection)
		exit(EXIT_FAILURE);
	if (errcase == error_access)
		exit(127);
}
