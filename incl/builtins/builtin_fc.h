/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtin_fc.h                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 00:12:30 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:00:00 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef BUILTIN_FC_H
# define BUILTIN_FC_H

# include "common.h"
# include "builtins/builtins_utils.h"
# include "editing/history/history.h"
# include "error_handler.h"

# define EDITOR "ed"
# define HIST_PERM CHEV_PERM

typedef	struct	s_fc_infos
{
	char		*opts;
	char		*pat;
	char		*rep;
	char		*editor;
	t_list		*first;
	t_list		*last;
	int			is_set;
	int			replace;
}				t_fc_infos;

/*
** UTILS
*/

char			*tmp_file(t_sh_state *sh_state);
size_t			fc_hist_to_num(t_list *find, t_list *hist);
size_t			fc_hist_to_num_rev(t_list *find, t_list *hist);
size_t			fc_get_hist_num(t_sh_state *sh_state, const char *str);
size_t			get_hist_len(t_list *hist);
void    		add_valid(t_fc_infos *fc_infos, char new);
int				fc_options(const char **av, t_fc_infos *fc_infos,
				t_builtin_context *context);
int				fc_exit(t_fc_infos *fc_infos, int ret);

/*
**
*/

int				fc_exec(t_sh_state *sh_state, t_fc_infos *fc_infos);
int				fc_replace_exec(t_sh_state *sh_state, t_fc_infos *fc_infos);
int				fc_print(t_list *hist, t_fc_infos *fc_infos, int fd);
int				builtin_fc(t_sh_state *sh_state, int ac, const char **av,
				t_builtin_context *context);

/*
** FREE
*/

int				free_list(t_list *list);

#endif
