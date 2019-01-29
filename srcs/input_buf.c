/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   input_buf.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 22:21:43 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/29 22:26:25 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "common.h"
#include "input_buf.h"

t_input_buf	*init_input_buf(void)
{
	t_input_buf	*input_buf;

	if ((input_buf = (t_input_buf*)malloc(sizeof(t_input_buf))) == NULL)
		return (NULL);
	input_buf->len = 0;
	input_buf->size = DEFAULT_INPUT_BUF_SIZE;
	if ((input_buf->buf = (char *)malloc(DEFAULT_INPUT_BUF_SIZE)) == NULL)
		return (NULL);
	ft_bzero(input_buf->buf, input_buf->size);
	return (input_buf);
}

int			append_input_buf(char *str, t_input_buf *input_buf)
{
	size_t	len;

	len = ft_strlen(str);
	if (len + input_buf->len >= input_buf->size)
	{
		input_buf->buf = ft_realloc(input_buf->buf,
	input_buf->size, input_buf->size * 2);
		if (input_buf == NULL)
			return (1);
		input_buf->size *= 2;
	}
	ft_strcat(input_buf->buf, str);
	input_buf->len += len;
	return (0);
}
