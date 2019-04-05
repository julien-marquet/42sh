/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf_manipulations.h                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 22:40:19 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:11:05 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DYN_BUF_MANIPULATIONS_H
# define DYN_BUF_MANIPULATIONS_H

# include "common.h"
# include "data/dyn_buf/dyn_buf_defines.h"

int			insert_dyn_buf(char *str, t_dyn_buf *dyn_buf, size_t index);
t_dyn_buf	*init_dyn_buf(void);
int			del_at_dyn_buf(t_dyn_buf *dyn_buf, size_t index);
int			shift_dyn_buf(t_dyn_buf *dyn_buf, size_t shift);
int			insertn_dyn_buf(char *str, t_dyn_buf *dyn_buf,
			size_t index, size_t len);

#endif
