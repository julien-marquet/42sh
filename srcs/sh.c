/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sh.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/28 22:59:25 by jmarquet     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 05:32:57 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sh.h"

static char	*get_hist_file(t_sh_state *sh_state)
{
	char	*tmp;
	char	*hist_file;

	if (!(tmp = expand_gethome(sh_state)))
		return (NULL);
	if (!(hist_file = ft_construct_str(2, tmp, "/.42sh_history")))
		return (NULL);
	ft_strdel(&tmp);
	return (hist_file);
}

static int	init_history(t_sh_state *sh_state)
{
	t_dyn_buf	*dyn;
	char		buf[READ_SIZE + 1];
	char		*hist_file;
	int			fd;
	int			r;

	if (!(hist_file = get_hist_file(sh_state)))
		return (1);
	fd = open(hist_file, O_RDONLY);
	ft_strdel(&hist_file);
	if (fd == -1)
		return (0);
	if ((dyn = init_dyn_buf()) == NULL)
		return (1);
	while ((r = read(fd, buf, READ_SIZE)) != 0)
	{
		buf[r] = 0;
		if (insert_dyn_buf(buf, dyn, dyn->len) != 0)
			return (1);
	}
	if (!(sh_state->history = hist_str2list(dyn->buf)))
		return (1);
	free_dyn_buf(&dyn);
	return (close(fd));
}

t_sh_state	*init_sh(void)
{
	t_sh_state	*sh_state;

	if ((sh_state = init_sh_state()) == NULL)
		return (NULL);
	if (init_term_state(sh_state) != 0)
		return (NULL);
	if (init_win_data() != 0)
		return (NULL);
	if (init_history(sh_state))
		return (NULL);
	return (sh_state);
}

static int	save_history(t_sh_state *sh_state)
{
	t_list	*hist;
	char	*hist_file;
	char	*tmp;
	int		fd;
	int		hist_size;

	if ((tmp = get_var(sh_state->internal_storage, "HISTSIZE")))
		hist_size = ft_atoi(tmp);
	else
		hist_size = 500;
	hist = sh_state->history;
	hist_file = get_hist_file(sh_state);
	if ((fd = open(hist_file, O_CREAT | O_TRUNC | O_WRONLY, HIST_PERM)) == -1)
	{
		ft_strdel(&hist_file);
		return (1);
	}
	while (hist && hist_size > 0)
	{
		ft_putendl_fd(hist->content, fd);
		hist_size--;
		hist = hist->next;
	}
	ft_strdel(&hist_file);
	return (close(fd));
}

void		exit_sh(t_sh_state *sh_state, t_input_data *input_data)
{
	unsigned char	status;
	void			(*del)(void *, size_t);

	status = sh_state->status;
	save_history(sh_state);
	del = free_lstnode;
	ft_lstdel(&sh_state->history, del);
	flush_all_jobs();
	set_term_state_backup(sh_state);
	free_sh_state(&sh_state);
	free_input_data(&input_data);
	set_search_mode(0);
	exit(status);
}
