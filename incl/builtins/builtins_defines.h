/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_defines.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:18:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 04:03:37 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DEFINES_H
# define BUILTINS_DEFINES_H

# define BUILTINS_NB 17

# define B_1 "set", "env", "setenv", "unsetenv", "unset", "exit", "echo"
# define B_2	"export", "[", "alias", "unalias", "jobs", "fg", "bg", "hash"
# define B_3 "test", "cd", NULL

# define F_1 builtin_set, builtin_env, builtin_setenv, builtin_unsetenv
# define F_2 builtin_unset, builtin_exit, builtin_echo, builtin_export
# define F_3 builtin_test, builtin_alias, builtin_unalias, builtin_jobs
# define F_4 builtin_fg, builtin_bg, builtin_hash, builtin_test
# define F_5 builtin_cd, NULL

#endif
