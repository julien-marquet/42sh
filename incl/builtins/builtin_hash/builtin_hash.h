#ifndef BUILTIN_HASH_H
# define BUILTIN_HASH_H

# include "common.h"

int				test_bin(char *bin_path);
char			*permission_denied(char *path);
char			*create_path(char *path, char *bin);
char			*add_path(char *path, t_list **table, char *bin, size_t inc_hits);

t_hash_table	*get_link(t_list **table, char *bin);
void			delete_table(t_list **table);
char			*append_bin(char *bin, t_list **table, t_list *internal_storage, size_t *found);
char			*get_bin_path(char **av, t_list **table, t_list *internal_storage, size_t *error);

int             builtin_hash(t_sh_state *sh_state, int ac,
            const char **av, t_builtin_context *context);
int				search_path(t_list *table, t_list *internal_storage);

#endif

