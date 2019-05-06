/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirs.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/22 23:22:40 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/02 15:04:15 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef REDIRS_H
# define REDIRS_H

# include "pipe_redir/pipe_defines.h"
# include "common.h"
# include <fcntl.h>
# include "builtins/builtins_utils.h"
# include "error_handler.h"

int		handle_in(t_file *in, char *origin);
int		create_redir_files(t_cmd *acmd);
int		redirs_exit(t_file *in, char *origin);
int		redirs_exit2(char *origin, t_file *in, int err);
int		handle_signal(t_file *file);
void	handle_fd_error(t_file *in, char *origin);
int		handle_file_in(t_file *in);
int		handle_here(t_file *in);
int		check_file_read(const char *path);
int		check_file_write(const char *path);
int		check_dir_write(const char *path);
char	*get_parent_dir_path(const char *path);
int		handle_redir(t_cmd *cmd, char *origin);
int		create_redir_files(t_cmd *acmd);
#endif
