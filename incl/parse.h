/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mmoya <mmoya@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/02/23 17:46:26 by mmoya        #+#   ##    ##    #+#       */
/*   Updated: 2019/04/05 16:06:20 by mmoya       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "common.h"
// # include <stdlib.h>
// # include <stdio.h>
// # include <term.h>
// # include <unistd.h>
// # include <termios.h>
// # include <signal.h>
// # include <limits.h>
// # include <fcntl.h>
// # include <sys/stat.h>
// # include <sys/ioctl.h>
// # include <sys/types.h>
# include <pwd.h>

# define SH_NAME "21sh"

# define CHEV_PERM 420

# define READ_END 0
# define WRITE_END 1

# define C_IN 0
# define C_LEN 1
# define C_OUT 2

/*
** TEMP ENV FUNCT
*/

# define sh_getenv(x, y) NULL
# define sh_getenvn(x, y, z) NULL

typedef struct	s_term {
	char		*str;
	size_t		cpos;
	char		**env;
	int			fd;
	int			flag;
}				t_term;

typedef struct		s_file {
	char			*file;
	char			*here;
	int				*type;
	struct s_file	*next;
}					t_file;

typedef struct		s_arg {
	char			*arg;
	int				type;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_cmd {
	char			*str;
	char			**arg;
	char			type;
	char			*red;
	t_file			*in;
	t_file			*out;
	struct s_cmd	*next;
}					t_cmd;

/*
** PARSE
*/

int				parse(char *str, t_term *term);
char			*stresc(char *find, char *str, int i);
void			parse_chev(t_cmd *cmd);
int				parse_tokenize(char *str, t_cmd **cmd);
void			parse_expansion(t_cmd *cmd, t_term *term);
void			parse_tilde(t_cmd *cmd, t_term *term);
char			**parse_strsplit(char *str, int len);
char			*strndup_qr(char *str, size_t len);
char			*strinsert(char *dst, char *new, size_t i, size_t end);
int				is_quoted(char *str, int i);

int				parse_error(char *str, int i);
int				parse_check(char *str);

t_cmd			*parse_nextfree(t_cmd *cmd);

// char			*sh_getenv(char *key, char **env);
// char			*sh_getenvn(char *key, char **env, int size);

/*
** EXEC
*/

int				exec_chevout(t_cmd *cmd);
int				exec_chevin(t_cmd *cmd);

#endif
