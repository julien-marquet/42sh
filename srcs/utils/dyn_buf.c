/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/30 04:57:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 13:43:48 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "utils/dyn_buf.h"

t_dyn_buf	*init_dyn_buf(void)
{
	t_dyn_buf	*dyn_buf;

	if ((dyn_buf = (t_dyn_buf*)malloc(sizeof(t_dyn_buf))) == NULL)
		return (NULL);
	dyn_buf->len = 0;
	dyn_buf->size = DEFAULT_DYN_BUF_SIZE;
	if ((dyn_buf->buf = (char *)malloc(DEFAULT_DYN_BUF_SIZE)) == NULL)
		return (NULL);
	ft_bzero(dyn_buf->buf, dyn_buf->size);
	return (dyn_buf);
}

int			insert_dyn_buf(char *str, t_dyn_buf *dyn_buf, size_t index)
{
	size_t	len;
	size_t	new_size;

	len = ft_strlen(str);
	if (len + dyn_buf->len >= dyn_buf->size)
	{
		new_size = len + dyn_buf->len > dyn_buf->size * 2 ?
	len + dyn_buf->len + DEFAULT_DYN_BUF_SIZE : dyn_buf->size * 2;
		dyn_buf->buf = ft_realloc(dyn_buf->buf,
	dyn_buf->size, new_size);
		if (dyn_buf == NULL)
			return (1);
		dyn_buf->size = new_size;
	}
	ft_memmove(&(dyn_buf->buf[index + len]), &(dyn_buf->buf[index]),
dyn_buf->len - index);
	ft_memcpy(&(dyn_buf->buf[index]), str, len);
	dyn_buf->len += len;
	return (0);
}

int			insertn_dyn_buf(char *str, t_dyn_buf *dyn_buf, size_t index, size_t len)
{
	size_t	new_size;

	if (len + dyn_buf->len >= dyn_buf->size)
	{
		new_size = len + dyn_buf->len > dyn_buf->size * 2 ?
	len + dyn_buf->len + DEFAULT_DYN_BUF_SIZE : dyn_buf->size * 2;
		dyn_buf->buf = ft_realloc(dyn_buf->buf,
	dyn_buf->size, new_size);
		if (dyn_buf == NULL)
			return (1);
		dyn_buf->size = new_size;
	}
	ft_memmove(&(dyn_buf->buf[index + len]), &(dyn_buf->buf[index]),
dyn_buf->len - index);
	ft_memcpy(&(dyn_buf->buf[index]), str, len);
	dyn_buf->len += len;
	return (0);
}

int		shift_dyn_buf(t_dyn_buf *dyn_buf, size_t shift)
{
	ft_memmove(dyn_buf->buf, &(dyn_buf->buf[shift]), dyn_buf->len - shift);
	dprintf(2, "SHIFT OF %zu for a total of %zu initial chars\n", shift, dyn_buf->len);
	dyn_buf->len -= shift;
	dprintf(2, "remaining buf len = %zu\n", dyn_buf->len);
	ft_bzero(&(dyn_buf->buf[dyn_buf->len]), dyn_buf->size - dyn_buf->len);

	return (0);
}

int		del_at_dyn_buf(t_dyn_buf *dyn_buf, size_t index)
{
	if (index < dyn_buf->len)
	{
		if (dyn_buf->len > 0)
		{
			ft_strcpy(&(dyn_buf->buf[index]), &(dyn_buf->buf[index + 1]));
			dyn_buf->buf[dyn_buf->len - 1] = '\0';
			dyn_buf->len -= 1;
			return (1);
		}
	}
	return (0);
}

void		reset_dyn_buf(t_dyn_buf *dyn_buf)
{
	dyn_buf->len = 0;
	ft_bzero(dyn_buf->buf, dyn_buf->size);
}
