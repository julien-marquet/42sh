/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   data_utils_lst.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:40:33 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 02:39:43 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/data_utils/data_utils_lst.h"
#pragma GCC diagnostic ignored "-Wunused-parameter"

void		free_lstnode(void *buf, size_t len)
{
	free(buf);
	buf = NULL;
}

void		free_lstinternal_storage_node(void *buf, size_t len)
{
	t_internal_storage	*casted;

	casted = (t_internal_storage *)buf;
	ft_strdel(&casted->string);
	free(buf);
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
