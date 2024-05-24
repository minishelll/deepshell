/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_all_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taerakim <taerakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:08:42 by taerakim          #+#    #+#             */
/*   Updated: 2024/05/24 21:25:30 by taerakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_error_bonus.h"

void	unlink_all_tmpfile(void)
{
	int			i;
	const char	*tmpfile[16] = {"/tmp/tmp1", "/tmp/tmp2", "/tmp/tmp3" \
						, "/tmp/tmp4", "/tmp/tmp5", "/tmp/tmp6", "/tmp/tmp7" \
						, "/tmp/tmp8", "/tmp/tmp9", "/tmp/tmp10" \
						, "/tmp/tmp11", "/tmp/tmp12", "/tmp/tmp13" \
						, "/tmp/tmp14", "/tmp/tmp15", "/tmp/tmp16"};

	i = 0;
	while (access(tmpfile[i], F_OK) == 0)
	{
		if (unlink(tmpfile[i]) == -1)
			ft_error(error_systemcall, errno, NULL);
		i++;
	}
}
