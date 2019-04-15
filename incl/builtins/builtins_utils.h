/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_utils.h                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 03:01:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 00:43:02 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_UTILS_H
# define BUILTINS_UTILS_H

# include "common.h"
# include "error_handler.h"

int		handle_builtin_options(const char **av, const char *valid,
		char **valid_options, t_builtin_context *context);
int		add_origin(char **origin, const char *src);

#endif
