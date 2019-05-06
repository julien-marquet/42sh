/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_env.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/05 22:38:16 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 05:04:26 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include "common.h"
# include "storage/storage.h"
# include "jobs/jobs.h"

void		env_error(char *origin, int *res);
char		*create_job_name_from_arr(const char **av);
t_proc_grp	*register_special_job(int pid, const char **av);
char		*find_utility(t_sh_state *sh_state, const char **av,
t_builtin_context *context);
int			count_pairs(const char **av, int *start, char *origin);
int				builtin_env(t_sh_state *sh_state, int ac, const char **av,
		t_builtin_context *context);
int			send_special_to_fg(t_sh_state *sh_state, t_proc_grp *proc_grp);

typedef struct	s_special_exec_context
{
	char *const	*av;
	char		**env;
	char		*path;
}				t_special_exec_context;

#endif
