/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_exit.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 22:38:41 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 22:44:38 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_EXIT_H
# define BUILTIN_EXIT_H

# include "common.h"

int		builtin_exit(t_sh_state *sh_state, int ac, const char **av, int fd_out);

#endif