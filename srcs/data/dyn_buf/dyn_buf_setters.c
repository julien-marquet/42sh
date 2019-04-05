/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf_setters.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:44:58 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 17:57:11 by jmarquet    ###    #+. /#+    ###.fr     */
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
	if (dyn_buf->len >= dyn_buf->size)
	{
		dyn_buf->size = dyn_buf->len + DEFAULT_DYN_BUF_SIZE;
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
	if (dyn_buf->len >= dyn_buf->size)
	{
		dyn_buf->size = dyn_buf->len + DEFAULT_DYN_BUF_SIZE;
		ft_strdel(&(dyn_buf->buf));
		if ((dyn_buf->buf = (char *)malloc(dyn_buf->size)) == NULL)
			return (1);
	}
	ft_strcpy(dyn_buf->buf, buf);
	return (0);
}