/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:39:03 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/10 13:09:24 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <errno.h>

/* ******************************* ERROR_TYPE ******************************* */
typedef enum e_error_type
{
	error_systemcall = -127,
	error_syntax,
	error_access,
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
	no_such_file,//1
	permission_denied,//1
	too_many_argu,//1
	invalid_identifier,//1
	invalid_option,//2
	required_numeric,//255
	not_support_option,//??
	not_support_argument,//??
	need_assignment//??
}	t_bi_error;

/* ******************************* EXIT_CODE ******************************** */
# define EXIT_BASIC_ERROR 1
# define EXIT_BUILT_IN_ERROR 2
# define EXIT_DEEPSHELL_ERROR 255
/*
0		성공
1		일반적인 에러
2		builtin shell command 에러
126		command가 존재하지만 실행 불가
127		command 존재 x
128		not used on shell
128+N	signal N 으로 종료된 경우
255		범위 밖인 경우
*/

/* ***************************** ERROR_MESSAGE ****************************** */
/* based on bash */
# define NO_SUCH_FILE "No such file or directory"
# define PERMISSION_DENIED "Permission denied"
# define TOO_MANY_ARG "too many arguments"
# define INVALID_ID "not a valid identifier"
# define INVALID_OPT "invalid option"
# define REQUIRED_NUMERIC "numeric argument required"
/* deepshell define */
# define NOT_SUPPORT_OPT "option is not support"
# define NOT_SUPPORT_AGU "argument is not support"
# define NEED_ASSIGNMENT "value is required (name=value)"

/* ******************************* FUNCTIONS ******************************** */
int		ft_error(t_error_type errcase, int errnum, char *target);
void	unlink_all_tmpfile(void);

#endif