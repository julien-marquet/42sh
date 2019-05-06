/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_type.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/25 05:04:39 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 06:04:57 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_TYPE_H
# define BUILTIN_TYPE_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "aliases/aliases.h"
# include "editing/input/completion/completion.h"

typedef enum	e_cmd_type
{
	cmd_notfound,
	cmd_alias,
	cmd_builtin,
	cmd_executable
}				t_cmd_type;

int		check_file_exec(const char *path);
int		builtin_type(t_sh_state *sh_state, int ac,
		const char **av, t_builtin_context *context);

#endif
