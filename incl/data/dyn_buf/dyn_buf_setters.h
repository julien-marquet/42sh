/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   dyn_buf_setters.h                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:46:28 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:11:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DYN_BUF_SETTERS_H
# define DYN_BUF_SETTERS_H

# include "common.h"
# include "data/dyn_buf/dyn_buf_defines.h"

int			set_dyn_buf(t_dyn_buf *dyn_buf, char *buf);
int			set_n_dyn_buf(t_dyn_buf *dyn_buf, char *buf, size_t n);
void		reset_dyn_buf(t_dyn_buf *dyn_buf);

#endif
