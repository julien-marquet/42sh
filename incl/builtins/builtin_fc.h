/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:12:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/22 17:50:07 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_FC_H
# define BUILTIN_FC_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "error_handler.h"

# define F_E 1 << 1
# define F_L 1 << 2
# define F_N 1 << 3
# define F_R 1 << 4
# define F_S 1 << 5

int		builtin_fc(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);

#endif
