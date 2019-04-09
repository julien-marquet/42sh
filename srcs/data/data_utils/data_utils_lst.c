/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   data_utils_lst.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:40:33 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 02:56:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/data_utils/data_utils_lst.h"

void		free_lstnode(void *buf, size_t len)
{
	len++;
	free(buf);
	buf = NULL;
}

void		free_dyn_buf(t_dyn_buf **dyn_buf)
{
	if (dyn_buf != NULL && *dyn_buf != NULL)
	{
		if ((*dyn_buf)->buf != NULL)
			free((*dyn_buf)->buf);
		free(*dyn_buf);
	}
}
