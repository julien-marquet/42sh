/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_set.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:49:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 23:02:10 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_SET_H
# define BUILTINS_SET_H

# include "common.h"
# include "storage/storage_manipulations.h"

int		builtins_set(void *i_storage, int	fd_out);

#endif