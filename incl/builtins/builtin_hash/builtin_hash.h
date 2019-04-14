#ifndef BUILTIN_HASH_H
# define BUILTIN_HASH_H

# include "common.h"

char			*get_bin_path(char **av, t_list **table, t_list *internal_storage);
int             builtin_hash(t_sh_state *sh_state, int ac,
            const char **av, t_builtin_context *context);
int				search_path(t_list *table, t_list *internal_storage);

#endif

