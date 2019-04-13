/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 23:13:44 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 23:03:27 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "common.h"
# include "builtins/builtins.h"
# include "exec/exec_functions.h"

int		execute(t_sh_state *sh_state, char **parsed);

#endif
