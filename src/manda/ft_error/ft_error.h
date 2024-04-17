/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:39:03 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/10 20:53:51 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include <errno.h>

typedef enum e_error_type
{
	error_systemcall = -127,
	error_syntax,
	error_access,
	error_redirection,
	error_built_in
}	t_error_type;

# define SYSTEMCALL_FAILURE -100

# define OUTPUT_REDIRECTION_ERROR -5
# define INPUT_REDIRECTION_ERROR -4
# define SYNTEX_ERROR -3
# define ACCESS_ERROR -2

# define ERROR -1
# define FAILURE -1
# define SUCCESS 0
# define DO_NOTHING 2

void	ft_error(t_error_type errcase, int errnum, char *target);

#endif