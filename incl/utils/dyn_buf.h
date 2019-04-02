/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 22:40:19 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/02 19:35:28 by jmarquet    ###    #+. /#+    ###.fr     */
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

int			insert_dyn_buf(char *str, t_dyn_buf *dyn_buf, size_t index);
t_dyn_buf	*init_dyn_buf(void);
void		reset_dyn_buf(t_dyn_buf *dyn_buf);
int			del_at_dyn_buf(t_dyn_buf *dyn_buf, size_t index);
int			shift_dyn_buf(t_dyn_buf *dyn_buf, size_t shift);
int			insertn_dyn_buf(char *str, t_dyn_buf *dyn_buf, size_t index, size_t len);
int			set_dyn_buf(t_dyn_buf *dyn_buf, char *buf);
int			set_n_dyn_buf(t_dyn_buf *dyn_buf, char *buf, size_t n);
void		free_dyn_buf(t_dyn_buf **dyn_buf);

void		free_lstnode(void *buf, size_t len);

#endif
