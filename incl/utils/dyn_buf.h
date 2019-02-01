/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 22:40:19 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/01 01:43:53 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DYN_BUF_H
# define DYN_BUF_H
# define DEFAULT_DYN_BUF_SIZE 128
# include "common.h"

typedef struct	s_dyn_buf
{
	size_t	len;
	size_t	size;
	char	*buf;
}				t_dyn_buf;

int			append_dyn_buf(char *str, t_dyn_buf *input_buf);
t_dyn_buf	*init_dyn_buf(void);
void		reset_dyn_buf(t_dyn_buf *dyn_buf);
int			del_at_dyn_buf(t_dyn_buf *dyn_buf, size_t index);

#endif
