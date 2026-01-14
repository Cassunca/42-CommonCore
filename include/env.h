/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:02:58 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/22 12:16:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_env_table
{
	t_env	**buckets;
	size_t	size;
}	t_env_table;

/* ========== ENV ========== */

unsigned long	hash(char *str);
t_env			*env_new(char *key, char *value);
char			**env_export(t_env_table *table);

/* ========== ENV INIT ========== */

t_env_table		*env_init(size_t size, char **envp);
void			env_destroy(t_env_table *table);

/* ========== ENV TABLE ========== */

void			env_set(t_env_table *table, char *key, char *value);
void			env_unset(t_env_table *table, char *key);
char			*env_get(t_env_table *table, char *key);

#endif