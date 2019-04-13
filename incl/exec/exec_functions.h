/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   exec_functions.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/13 22:51:46 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/13 23:03:33 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXEC_FUNCTIONS_H
# define EXEC_FUNCTIONS_H

# include "common.h"
# include "builtins/builtins_dispatcher.h"
# include "exec/exec_dispatcher.h"

t_exec_func		get_exec_function(t_exec_mode exec_mode);

#endif
