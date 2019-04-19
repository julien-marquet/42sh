/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   data_utils_lst.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:41:05 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 02:38:50 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef DATA_UTILS_LST_H
# define DATA_UTILS_LST_H

# include "common.h"

void		free_dyn_buf(t_dyn_buf **dyn_buf);
void		free_lstnode(void *buf, size_t len);
void		free_lstinternal_storage_node(void *buf, size_t len);

#endif
