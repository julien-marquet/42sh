/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_defines.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:18:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 23:03:36 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DEFINES_H
# define BUILTINS_DEFINES_H

# define BUILTINS_NB 6
# define BUILTINS_MAX_LEN 20

typedef int	(*t_builtin_func)(t_sh_state *, int ac, const char **av, int fd_out);

#endif
