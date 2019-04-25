/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jmarquet <jmarquet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 16:31:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/25 04:59:40 by jmarquet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

/*
** parse_tokenlen:
**
** Token len minus redirection characters
*/

static int		parse_tokenlen(t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->str);
	if (cmd->type)
	{
		while (len > 0 && cmd->str[len - 1] == cmd->type)
			len--;
		cmd->red = ft_strdup(cmd->str + len);
	}
	return (len);
}

static int		parse_tokenparse(t_cmd *cmd, t_sh_state *sh_state,
t_input_data *input_data)
{
	int		len;
	int		i;

	i = 0;
	if (parse_expansion(cmd, sh_state))
		return (1);
	parse_chev(cmd, sh_state, input_data);
	len = parse_tokenlen(cmd);
	while (i < len && ft_isspace(cmd->str[i]))
		i++;
	if (i == len)
		return (0);
	if (!(cmd->arg = parse_strsplit(cmd->str, len)))
		return (1);
	return (0);
}

void			parse_print(t_cmd *cmd)
{
	int		i;
	t_file	*file;

	i = 0;
	dprintf(2, "\033[34;1m");
	while (cmd->arg && cmd->arg[i])
	{
		dprintf(2, "arg[%i] = %s\n", i, cmd->arg[i]);
		i++;
	}
	file = cmd->in;
	while (file)
	{
		dprintf(2, "input in=%i len=%i ", file->type[C_IN], file->type[C_LEN]);
		dprintf(2, "out=%i = '%s' '%s'\n",
		file->type[C_OUT], file->file, file->here);
		file = file->next;
	}
	file = cmd->out;
	while (file)
	{
		dprintf(2, "output in=%i len=%i ", file->type[C_IN], file->type[C_LEN]);
		dprintf(2, "out=%i = '%s'\n", file->type[C_OUT], file->file);
		file = file->next;
	}
	dprintf(2, "Redir %s Assign %i\n", cmd->red, cmd->assign);
	dprintf(2, "\033[0m");
}

char			*create_job_name(t_cmd *acmd)
{
	char	*name;
	char	*tmp;

	name = NULL;
	while (!cmd_is_empty(acmd))
	{
		if (name == NULL && acmd->str != NULL)
			name = ft_strdup(acmd->str);
		else if (acmd->str != NULL)
		{
			tmp = name;
			name = ft_strjoin(tmp, acmd->str);
			ft_strdel(&tmp);
		}
		if (acmd->red == NULL || ft_strcmp(acmd->red, ";") == 0 ||
		ft_strcmp(acmd->red, "&") == 0)
			break ;
		acmd = acmd->next;
	}
	return (name);
}

int				is_processable(t_cmd *cmd)
{
	char	*str;
	int		res;

	if ((str = ft_strtrim(cmd->str)) == NULL)
		return (0);
	if (ft_strlen(str) == 0)
		res = 0;
	else
		res = 1;
	ft_strdel(&str);
	return (res);
}

int				parse_exec(char *line, t_sh_state *sh_state,
t_input_data *input_data)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	char	*str;
	int		i;
	char	*job_name;
	t_cmd	*acmd;

	i = 0;
	cmd = NULL;
	if (!(str = parse_alias(line, sh_state->aliases, NULL)))
		exit_sh(sh_state, input_data);
	if (parse_check(str))
		return (1);
	while (str[i])
		i += parse_tokenize(str + i, &cmd);
	ft_strdel(&str);
	acmd = cmd;
	while (cmd)
	{
		tmp = NULL;
		if (parse_tokenparse(cmd, sh_state, input_data))
		{
			free_cmds(acmd);
			return (1);
		}
		//parse_print(cmd);
		if (cmd->red == NULL || ft_strcmp(cmd->red, ";") == 0 ||
	ft_strcmp(cmd->red, "&") == 0)
		{
			create_redir_file(cmd);
			tmp = cmd->next;
			job_name = create_job_name(acmd);
			i = exec_cmd_list(sh_state, acmd, job_name, NULL);
			ft_strdel(&job_name);
			if (i == -1)
				return (-1);
			cmd = tmp;
			acmd = cmd;
		}
		else
			cmd = cmd->next;
	}
	return (0);
}
