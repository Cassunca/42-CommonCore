/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:02:58 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/24 16:33:43 by amyrodri         ###   ########.fr       */
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

// env.c
unsigned long	hash(char *str);

t_env_table		*env_init(size_t size, char **envp);
void			env_destroy(t_env_table *table);

t_env			*env_new(char *key, char *value);

void			env_set(t_env_table *table, char *key, char *value);
void			env_unset(t_env_table *table, char *key);
char			*env_get(t_env_table *table, char *key);

char			**env_export(t_env_table *table);

#endif