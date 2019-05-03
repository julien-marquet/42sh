/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fc_replace_exec.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 04:53:12 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 05:24:19 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "builtins/builtin_fc.h"

static char	*fc_replace(t_list *hist, t_fc_infos *fc_infos)
{
	// TODO REPLACE STR BY PAT, PAT_LEN
	dprintf(1, "%s\n", ft_strstr(hist->content, fc_infos->pat));
	return (NULL);
}

int			fc_replace_exec(t_sh_state *sh_state, t_fc_infos *fc_infos)
{
//	int		ret;
	
	(void)sh_state;
	(void)fc_infos;
	if (fc_infos->first != NULL)
		fc_infos->first = sh_state->history;
	fc_replace(sh_state->history->next, fc_infos);
	dprintf(1, "%s\n", fc_infos->first ? fc_infos->first->content:"RIEN");
	//ret = parse_exec(cmd->content, sh_state, sh_state->input_data);
	return (0);
}