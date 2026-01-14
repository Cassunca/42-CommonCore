/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 23:46:01 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 12:15:56 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_H
# define ALIAS_H

# include "minishell.h"

typedef struct s_shell	t_shell;

typedef struct s_alias
{
	char			*key;
	char			*value;
	struct s_alias	*next;
}	t_alias;

typedef struct s_alias_table
{
	t_alias			**buckets;
	size_t			size;
}	t_alias_table;

/* ========== ALIAS ========== */

t_alias_table	*init_alias(size_t size);
char			**alias_export(t_alias_table *table);

/* ========== ALIAS TABLE ========== */

void			alias_set(t_alias_table *table, char *key, char *value);
void			alias_unset(t_alias_table *table, char *key);
char			*alias_get(t_alias_table *table, char *key);

/* ========== ALIAS NEW ========== */

t_alias			*alias_new(char *key, char *value);
void			alias_destroy(t_alias_table *table);

#endif