/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 16:31:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 16:59:19 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parse/parse.h"

/*
** parse_tokenlen:
**
** TOKEN LEN MINUS REDIRECTION CHARACTERS
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

static t_cmd	*parse_tokenparse(t_cmd *cmd, t_sh_state *sh_state, t_input_data *input_data)
{
	int		len;

	parse_expansion(cmd, sh_state);
	parse_chev(cmd, sh_state, input_data);
	len = parse_tokenlen(cmd);
	if (!(cmd->arg = parse_strsplit(cmd->str, len)))
		return (NULL);
	ft_strdel(&cmd->str);
	return (cmd);
}

void			parse_print(t_cmd *cmd)
{
	int		i;
	t_file	*file;

	i = 0;
	while (cmd->arg[i])
	{
		dprintf(2, "arg[%i] = %s\n", i, cmd->arg[i]);
		i++;
	}
	file = cmd->in;
	while (file)
	{
		dprintf(2, "input in=%i len=%i ", file->type[C_IN], file->type[C_LEN]);
		dprintf(2, "out=%i = '%s' '%s'\n", file->type[C_OUT], file->file, file->here);
		file = file->next;
	}
	file = cmd->out;
	while (file)
	{
		dprintf(2, "output in=%i len=%i ", file->type[C_IN], file->type[C_LEN]);
		dprintf(2, "out=%i = '%s'\n", file->type[C_OUT], file->file);
		file = file->next;
	}
	dprintf(2, "Redir %s\n", cmd->red);
}

// static void		parse_test(t_cmd *cmd, t_term *term)
// {
// 	int pid;
// 	int ret;
// 	t_file *tmp;

// 	tmp = NULL;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		exec_chevin(cmd);
// 		exec_chevout(cmd);
// 		if (ft_strstr(cmd->arg[0], "ls"))
// 		{
// 			execve("/bin/ls", cmd->arg, term->env);
// 		}
// 		if (ft_strstr(cmd->arg[0], "cat"))
// 		{
// 			execve("/bin/cat", cmd->arg, term->env);
// 		}
// 		if (ft_strstr(cmd->arg[0], "echo"))
// 		{
// 			execve("/bin/echo", cmd->arg, term->env);
// 		}
// 		if (ft_strstr(cmd->arg[0], "env"))
// 		{
// 			execve("/usr/bin/env", cmd->arg, term->env);
// 		}
// 		dprintf(2, "ERROR\n");
// 		exit(-1);
// 	}
// 	else
// 		wait(&ret);
// }

int				parse(char *str, t_sh_state *sh_state, t_input_data *input_data)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = NULL;
	str = parse_alias(str, sh_state->aliases);
	if (parse_check(str))
		return (1);
	while (str[i])
		i += parse_tokenize(str + i, &cmd);
	while (cmd)
	{
		if (!(cmd = parse_tokenparse(cmd, sh_state, input_data)))
			return (1);
		parse_print(cmd);
		//parse_test(cmd, term);
		cmd = parse_nextfree(cmd);
	}
	return (0);
}
