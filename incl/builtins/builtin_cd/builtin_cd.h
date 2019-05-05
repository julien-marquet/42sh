/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_cd.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/23 20:25:04 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 15:23:08 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "common.h"
# include "storage/storage.h"
# include "builtins/builtins_utils.h"

int		builtin_cd(t_sh_state *sh_state, int ac,
		const char **av, t_builtin_context *context);
int		verify_path(char *origin, char *curpath, char *formatted);

int		had_null_paths(char *cdpath, int i);
char	*get_old_pwd(t_sh_state *sh_state, t_builtin_context *context);
int		is_symbolic_link(char *path);
char	**get_dirs(char *base, char *path, char ***pointer);
int		verify_new(char **base, char *pointer, char **tmp, char ***dirs);

int		check_for_cons_separator(char *cdpath, int j);
int		check_dir_path(const char *path);
char	*resolve_free(char *base, char **dirs);
char	*format_and_verify(t_sh_state *sh_state,
		char *curpath, char *origin, int check);
int		check_links(const char **av, size_t opts);

char	*format_path(t_sh_state *sh_state, char *curpath, size_t res_links);
int		make_path_canonical(char **path);
int		make_path_absolute(t_sh_state *sh_state, char **path);

char	*get_dir_operand(t_sh_state *sh_state, int ac, const char **av,
int start);
char	*get_curpath(t_sh_state *sh_state, int ac, const char **av, int *i);
char	*retrieve_cdpath(t_sh_state *sh_state, const char **av,
int start);

int		get_prec_slash_pos(char *path, int i);
int		count_unnecessary_slashes(char *path, int i);
int		remove_dot(char **path, int *i);
int		remove_dot_dot(char **path, int *i);
int		remove_slashes(char **path, int *i);

char	*resolve_links(t_sh_state *state, char *base, char **path);

#endif
