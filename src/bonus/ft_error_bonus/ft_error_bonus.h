/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:39:03 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:32:23 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_BONUS_H
# define FT_ERROR_BONUS_H

# include <errno.h>

/* ******************************* ERROR_TYPE ******************************* */
typedef enum e_error_type
{
	error_systemcall = -127,
	error_syntax,
	error_access_f,
	error_access_x,
	error_cmd_not_found,
	error_is_dir,
	error_redirection,
	error_ambiguous_redirection,
	error_file,
	error_max_heredoc,
	error_built_in = -1,
	error_echo,
	error_cd,
	error_pwd,
	error_export,
	error_unset,
	error_env,
	error_exit
}	t_error_type;

typedef enum e_bi_error
{
	use_errno = -1,
	permission_denied,
	too_many_argu,
	invalid_identifier,
	invalid_option,
	oldpwd_not_set,
	getcwd_check,
	required_numeric,
	not_support_option,
	not_support_argument,
	need_assignment
}	t_bi_error;

/* ******************************* EXIT_CODE ******************************** */
# define EXIT_BASIC_ERROR 1
# define EXIT_BUILT_IN_ERROR 2
# define EXIT_DASHELL_ERROR 255

/* ***************************** ERROR_MESSAGE ****************************** */
/* based on bash */
# define PERMISSION_DENIED "Permission denied"
# define TOO_MANY_ARG "too many arguments"
# define INVALID_ID "not a valid identifier"
# define INVALID_OPT "invalid option"
# define OLDPWD_NOT_SET "OLDPWD not set"
# define GETCWD_CHECK "error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory"
# define REQUIRED_NUMERIC "numeric argument required"
/* dashell define */
# define NOT_SUPPORT_OPT "option is not support"
# define NOT_SUPPORT_AGU "argument is not support"
# define NEED_ASSIGNMENT "value is required (name=value)"

/* ******************************* FUNCTIONS ******************************** */
int		ft_error(t_error_type errcase, int errnum, char *target);
int		get_bi_errcode(t_bi_error type);
void	unlink_all_tmpfile(void);

#endif