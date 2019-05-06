/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf_setters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:44:58 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 17:15:20 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "data/dyn_buf/dyn_buf_setters.h"

void		reset_dyn_buf(t_dyn_buf *dyn_buf)
{
	dyn_buf->len = 0;
	ft_bzero(dyn_buf->buf, dyn_buf->size);
}

int			set_dyn_buf(t_dyn_buf *dyn_buf, char *buf)
{
	dyn_buf->len = ft_strlen(buf);
	if (dyn_buf->len + 1 >= dyn_buf->size)
	{
		dyn_buf->size = ((dyn_buf->len  + 1) * 2);
		ft_strdel(&(dyn_buf->buf));
		if ((dyn_buf->buf = (char *)malloc(dyn_buf->size)) == NULL)
			return (1);
	}
	ft_strcpy(dyn_buf->buf, buf);
	return (0);
}

int			set_n_dyn_buf(t_dyn_buf *dyn_buf, char *buf, size_t n)
{
	dyn_buf->len = ft_strlen(buf);
	if (n < dyn_buf->len)
		dyn_buf->len = n;
	if (dyn_buf->len + n + 1 >= dyn_buf->size)
	{
		dyn_buf->size = (dyn_buf->len + n + 1) * 2;
		ft_strdel(&(dyn_buf->buf));
		if ((dyn_buf->buf = (char *)malloc(dyn_buf->size)) == NULL)
			return (1);
	}
	ft_strcpy(dyn_buf->buf, buf);
	return (0);
}
