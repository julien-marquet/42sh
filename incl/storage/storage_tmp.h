/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   storage_tmp.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 17:27:34 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 05:30:11 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef STORAGE_TMP_H
# define STORAGE_TMP_H

# include "common.h"

void		remove_tmp_env(t_list **storage);
int			update_builtin_env(t_list **storage, t_list *vars);

#endif
