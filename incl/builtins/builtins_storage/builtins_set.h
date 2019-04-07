/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_set.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 18:49:06 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 19:34:51 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_SET_H
# define BUILTINS_SET_H

# include "common.h"
# include "storage/storage_manipulations.h"

int		builtins_set(t_sh_state *sh_state, int	fd_out);

#endif
