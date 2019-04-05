/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lst_utils.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:41:05 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 18:11:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LST_UTILS_H
# define LST_UTILS_H

# include "common.h"

void		free_dyn_buf(t_dyn_buf **dyn_buf);
void		free_lstnode(void *buf, size_t len);

#endif
