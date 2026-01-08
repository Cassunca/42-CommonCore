/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:07:16 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/08 15:12:16 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	load_env(t_env_table *table, char **envp)
{
	int		i;
	char	*entry;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		entry = envp[i];
		equal = ft_strchr(entry, '=');
		if (equal)
		{
			key = ft_substr(entry, 0, equal - entry);
			value = ft_strdup(equal + 1);
			env_set(table, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

t_env_table	*env_init(size_t size, char **envp)
{
	t_env_table	*table;

	table = malloc(sizeof(t_env_table));
	if (!table)
		return (NULL);
	table->buckets = ft_calloc(size, sizeof(t_env *));
	table->size = size;
	if (envp)
		load_env(table, envp);
	return (table);
}

void	env_destroy(t_env_table *table)
{
	size_t	i;
	t_env	*curr;
	t_env	*next;

	i = 0;
	while (i < table->size)
	{
		curr = table->buckets[i];
		while (curr)
		{
			next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			curr = next;
		}
		i++;
	}
	free(table->buckets);
	free(table);
}
