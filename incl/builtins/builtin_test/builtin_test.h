/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: legrivel <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 22:05:40 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 22:05:43 by legrivel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_TEST_H
# define BUILTIN_TEST_H

# include "common.h"
# include <errno.h>
# include <sys/stat.h>

int     make_unary_test(char op, const char *arg);
int     make_binary_test(const char *arg1, const char *op, const char *arg2);
int     builtin_test(t_sh_state *sh_state, int ac, const char **av, int fd_out);

#endif
