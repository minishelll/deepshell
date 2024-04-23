/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 00:39:03 by taerakim          #+#    #+#             */
/*   Updated: 2024/04/23 11:49:59 by taerakim         ###   ########.fr       */
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

void	ft_error(t_error_type errcase, int errnum, char *target);

#endif