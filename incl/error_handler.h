/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error_handler.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 18:11:23 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 03:34:11 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include "common.h"

void	print_error(const char *origin, const char *err, int fd);
void	handle_path_error(const char *origin, const char *path, int err);
void	handle_dir_path_error(const char *origin, const char *path, int err);
void	handle_no_dir_error(const char *origin, const char *path, int err);
void	handle_path_exec_error(const char *origin, const char *path, int err);

#endif
