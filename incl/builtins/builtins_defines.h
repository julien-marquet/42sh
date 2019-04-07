/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_defines.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:18:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/07 19:19:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DEFINES_H
# define BUILTINS_DEFINES_H

# define BUILTINS_NB 2
# define BUILTINS_MAX_LEN 20

typedef int	(*t_builtin_func)(void *, int fd_out);

#endif