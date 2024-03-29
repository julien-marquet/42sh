/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_replace_exec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 04:53:12 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 23:46:38 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static char	*fc_replace(t_fc_infos *fc_infos)
{
	char	*out;
	char	*pat;
	size_t	len;
	size_t	diff;
	t_list	*cmd;

	pat = NULL;
	cmd = fc_infos->first;
	out = NULL;
	if ((pat = ft_strstr(cmd->content, fc_infos->pat)))
	{
		diff = ft_strlen(cmd->content) - ft_strlen(pat);
		len = ft_strlen(cmd->content) - ft_strlen(fc_infos->pat) +
		ft_strlen(fc_infos->rep);
		if (!(out = ft_strnew(len)))
			return (NULL);
		pat += ft_strlen(fc_infos->pat);
		ft_strncat(out, cmd->content, diff);
		ft_strcat(out, fc_infos->rep);
		ft_strcat(out, pat);
	}
	ft_strdel(&fc_infos->pat);
	ft_strdel(&fc_infos->rep);
	return (out == NULL ? ft_strdup((char*)(cmd->content)) : out);
}

int			fc_replace_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	char	*str;
	int		ret;

	free_current_cmd(sh_state);
	if (fc_infos->pat == NULL)
		fc_infos->pat = ft_strdup("");
	if (fc_infos->rep == NULL)
		fc_infos->rep = ft_strdup("");
	if (!fc_infos->pat || !fc_infos->rep)
		return (fc_exit(fc_infos, -1));
	if (fc_infos->first == NULL)
		fc_infos->first = sh_state->history;
	if (!(str = fc_replace(fc_infos)))
		return (-1);
	ft_putendl_fd(str, 2);
	if (add_to_history_list(&(sh_state->history), str,
	ft_strlen(str) + 1) == NULL)
		return (-1);
	ret = parse_exec(str, sh_state, sh_state->input_data);
	ft_strdel(&str);
	return (0);
}
