/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_replace_exec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 04:53:12 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/05 17:12:22 by mmoya       ###    #+. /#+    ###.fr     */
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
	out = NULL;
	cmd = fc_infos->first;
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
	return (out);
}

int			fc_replace_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
	t_list	*old;
	char	*str;
	int		ret;
	
	old = sh_state->history;
	sh_state->history = sh_state->history->next;
	free(old->content);
	free(old);
	if (fc_infos->pat == NULL)
		fc_infos->pat = ft_strdup("");
	if (fc_infos->rep == NULL)
		fc_infos->rep = ft_strdup("");
	if (!fc_infos->pat || !fc_infos->rep)
		return (fc_exit(fc_infos, -1));
	if (fc_infos->first == NULL)
		fc_infos->first = sh_state->history;
	str = fc_replace(fc_infos);
	ft_putendl(str);
	if (add_to_history_list(&(sh_state->history), str, ft_strlen(str) + 1) == NULL)
		return (-1);
	ret = parse_exec(str, sh_state, sh_state->input_data);
	ft_strdel(&str);
	return (0);
}