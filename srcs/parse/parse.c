/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/05 16:31:21 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/16 03:20:39 by mmoya       ###    #+. /#+    ###.fr     */
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
	// ft_strdel(&cmd->str);
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
/*
int		exec_chevin(t_file *in)
{
	int		fd[2];

	if (in == NULL)
		return (0);
	if (access(in->file, F_OK) != 0)
		return (0);
	while (in->next)
	{
		// CHECK READ ACCESS AND REPORT ERROR
		if (access(in->file, F_OK) != 0)
			return (0);
		dprintf(2, "LOOP\n");
		in = in->next;
	}
	if (in->here)
	{
		pipe(fd);
		in->type[C_OUT] = fd[0];
		ft_putstr_fd(in->here, fd[1]);
		close(fd[1]);
	}
	else
		in->type[C_OUT] = open(in->file, O_RDONLY);
	dup2(in->type[C_OUT], in->type[C_IN]);
	return (0);
}

int		exec_chevout(t_file *out)
{
	int		perm;

	if (out == NULL)
		return (0);
	while (out)
	{
		perm = O_WRONLY | O_CREAT;
		if (out->type[C_LEN] == 2)
			perm |= O_APPEND;
		if (out->type[C_OUT] == CHEV_FILE)
			out->type[C_OUT] = open(out->file, perm, CHEV_PERM);
		else if (out->type[C_OUT] == CHEV_CLOSE)
			close(out->type[C_IN]);
		dup2(out->type[C_OUT], out->type[C_IN]);
		out = out->next;
	}
	return (0);
}
*/
/*
static void		parse_test(t_cmd *cmd)
{
	int pid;
	int ret;
	t_file *tmp;
	tmp = NULL;
	pid = fork();
	if (pid == 0)
	{
		//exec_chevin(cmd->in);
		//exec_chevout(cmd->out);
		if (ft_strstr(cmd->arg[0], "ls"))
		{
			execve("/bin/ls", cmd->arg, NULL);
		}
		if (ft_strstr(cmd->arg[0], "cat"))
		{
			execve("/bin/cat", cmd->arg, NULL);
		}
		if (ft_strstr(cmd->arg[0], "echo"))
		{
			execve("/bin/echo", cmd->arg, NULL);
		}
		if (ft_strstr(cmd->arg[0], "env"))
		{
			execve("/usr/bin/env", cmd->arg, NULL);
		}
		dprintf(2, "ERROR\n");
		exit(-1);
	}
	else
		wait(&ret);
}*/

int				parse(char *line, t_sh_state *sh_state,
t_input_data *input_data)
{
	t_cmd	*cmd;
	char	*str;
	int		i;

	i = 0;
	cmd = NULL;
	if (!(str = parse_alias(line, sh_state->aliases, NULL)))
		exit_sh(sh_state, input_data);
	if (parse_check(str))
		return (1);
	while (str[i])
		i += parse_tokenize(str + i, &cmd);
	ft_strdel(&str);
	while (cmd)
	{
		if (parse_tokenparse(cmd, sh_state, input_data))
		{
			dprintf(1, "NIQUE TOI '%s'\n", cmd->str);
			while (cmd)
				cmd = parse_nextfree(cmd);
			return (1);
		}
		parse_print(cmd);
		//parse_test(cmd);
		cmd = parse_nextfree(cmd);
	}
	return (0);
}
