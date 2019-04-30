/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins_defines.h                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/07 19:18:08 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 10:02:21 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTINS_DEFINES_H
# define BUILTINS_DEFINES_H

# define BUILTINS_NB 21

# define B_1 "set", "env", "setenv", "unsetenv", "unset", "exit", "echo"
# define B_2 "export", "[", "alias", "unalias", "jobs", "fg", "bg", "hash"
# define B_3 "test", "cd", "type", "fc", "true", "false", NULL

# define BUILTINS_NAMES B_1, B_2, B_3

# define F_1 builtin_set, builtin_env, builtin_setenv, builtin_unsetenv
# define F_2 builtin_unset, builtin_exit, builtin_echo, builtin_export
# define F_3 builtin_test, builtin_alias, builtin_unalias, builtin_jobs
# define F_4 builtin_fg, builtin_bg, builtin_hash, builtin_test
# define F_5 builtin_cd, builtin_type, builtin_fc, builtin_true
# define F_6 builtin_false, NULL

# define BUILTINS_FUNCS F_1, F_2, F_3, F_4, F_5, F_6

#endif
