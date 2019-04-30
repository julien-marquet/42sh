/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_test.h                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/11 21:00:28 by legrivel     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/21 22:34:12 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_TEST_H
# define BUILTIN_TEST_H

# include "common.h"
# include <errno.h>

typedef struct	s_test_infos
{
	size_t		negate;
	int			base_ac;
	size_t		is_last_builtin;
}				t_test_infos;

int				is_unary_op(const char *arg);
int				is_binary_op(const char *arg);
int				test_error(char *builtin, char *file, char *msg);
int				make_test(t_test_infos *infos, const char **av, int ac);
int				make_unary_test(char op, const char *arg);
int				check_args(const char **av);
int				make_binary_test(const char **av);
int				builtin_test(t_sh_state *sh_state, int ac,
			const char **av, t_builtin_context *context);

#endif
