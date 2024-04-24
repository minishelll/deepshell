/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:16:58 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 21:18:25 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ft_error.h"
#include "libft.h"

static int	_print_bi_error(t_error_type errcase, t_bi_error type, char *target)
{
	const char	*bi_list[7] = {"echo: ", "cd: ", "pwd: ", "export: " \
								, "unset: ", "env: ", "exit: "};
	const char	*msglist[7] = {INVALID_OPT, INVALID_ID
								, TOO_MANY_ARG, REQUIRED_NUMERIC \
								, NOT_SUPPORT_OPT, NOT_SUPPORT_AGU \
								, NEED_ASSIGNMENT};

	ft_putstr_fd((char *)bi_list[errcase], 2);
	if (type == invalid_identifier)
		ft_putstr_fd("`", 2);
	ft_putstr_fd(target, 2);
	if (type == invalid_identifier)
		ft_putstr_fd("'", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((char *)msglist[type], 2);
	ft_putstr_fd("\n", 2);
	if (type == invalid_identifier)
		return (EXIT_BUILT_IN_ERROR);
	else if (type >= required_numeric)
		return (EXIT_DEEPSHELL_ERROR);
	return (EXIT_BASIC_ERROR);
}

static void	_print_error(t_error_type errcase, int errnum, char *target)
{
	char		*message;

	message = NULL;
	if (errcase == error_redirection)
		message = strerror(errnum);
	else if (errcase == error_access)
		message = "command not found";
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_error(t_error_type errcase, int errnum, char *target)
{
	if (errcase == error_systemcall)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	ft_putstr_fd("deepshell: ", 2);
	if (errcase > error_built_in)
		return (_print_bi_error(errcase, errnum, target));
	_print_error(errcase, errnum, target);
	if (errcase == error_redirection)
		exit(EXIT_FAILURE);
	if (errcase == error_access)
		exit(127);
	return (0);
}
