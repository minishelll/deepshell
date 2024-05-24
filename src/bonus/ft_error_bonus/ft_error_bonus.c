/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:16:58 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:55 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ft_error_bonus.h"
#include "libft.h"

int	get_bi_errcode(t_bi_error type)
{
	if (type == invalid_option)
		return (EXIT_BUILT_IN_ERROR);
	else if (type >= required_numeric)
		return (EXIT_DASHELL_ERROR);
	return (EXIT_BASIC_ERROR);
}

static int	_print_bi_error(t_error_type errcase, t_bi_error type, char *target)
{
	const char	*bi_list[7] = {"echo: ", "cd: ", "pwd: ", "export: " \
								, "unset: ", "env: ", "exit: "};
	const char	*msglist[10] = {PERMISSION_DENIED, TOO_MANY_ARG, INVALID_ID \
						, INVALID_OPT, OLDPWD_NOT_SET, GETCWD_CHECK \
						, REQUIRED_NUMERIC, NOT_SUPPORT_OPT \
						, NOT_SUPPORT_AGU, NEED_ASSIGNMENT};

	ft_putstr_fd((char *)bi_list[errcase], 2);
	if (type == invalid_identifier)
		ft_putstr_fd("`", 2);
	if (type != too_many_argu)
		ft_putstr_fd(target, 2);
	if (type == invalid_identifier)
		ft_putstr_fd("'", 2);
	if (type != too_many_argu)
		ft_putstr_fd(": ", 2);
	if (type == use_errno)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd((char *)msglist[type], 2);
	ft_putstr_fd("\n", 2);
	return (get_bi_errcode(type));
}

static char	*_get_err_message(t_error_type errcase, int errnum)
{
	char	*message;

	message = NULL;
	if (errcase == error_access_f || errcase == error_access_x \
	|| errcase == error_redirection)
		message = strerror(errnum);
	else if (errcase == error_cmd_not_found)
		message = "command not found";
	else if (errcase == error_is_dir)
		message = "is a directory";
	else if (errcase == error_max_heredoc)
		message = "maximum here-document count exceeded";
	else if (errcase == error_syntax)
		message = "syntax error near unexpected token `";
	else if (errcase == error_ambiguous_redirection)
		message = "ambiguous redirect";
	return (message);
}

static void	_print_error(t_error_type errcase, int errnum, char *target)
{
	char	*message;

	message = _get_err_message(errcase, errnum);
	if (errcase != error_syntax && errcase != error_max_heredoc)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(message, 2);
	if (errcase == error_syntax)
	{
		ft_putstr_fd(target, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}

int	ft_error(t_error_type errcase, int errnum, char *target)
{
	unlink_all_tmpfile();
	ft_putstr_fd("dashell: ", 2);
	if (errcase == error_systemcall)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	if (errcase > error_built_in)
		return (_print_bi_error(errcase, errnum, target));
	_print_error(errcase, errnum, target);
	if (errcase == error_redirection)
		exit(EXIT_FAILURE);
	if (errcase == error_max_heredoc)
		exit(2);
	if (errcase == error_access_x || errcase == error_is_dir)
		exit(126);
	if (errcase == error_access_f || errcase == error_cmd_not_found)
		exit(127);
	return (1);
}
