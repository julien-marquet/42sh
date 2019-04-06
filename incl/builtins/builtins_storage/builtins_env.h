/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_env.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:38:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 23:04:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_ENV_H
# define BUILTINS_ENV_H

# include "common.h"
# include "storage/storage_manipulations.h"

int		builtins_env(void *env, int fd_out);

#endif