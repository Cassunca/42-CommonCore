/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:11:23 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/24 16:13:02 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	env_set(t_env_table *table, char *key, char *value)
{
	unsigned long	idx;
	t_env			*curr;
	t_env			*new;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (strcmp(curr->key, key) == 0) // rebuild ft_strcmp
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	new = env_new(key, value);
	new->next = table->buckets[idx];
	table->buckets[idx] = new;
}

void	env_unset(t_env_table *table, char *key)
{
	unsigned long	idx;
	t_env			*curr;
	t_env			*prev;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->key, key) == 0) // rebuild ft_strcmp
		{
			if (prev)
				prev->next = curr->next;
			else
				table->buckets[idx] = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

char	*env_get(t_env_table *table, char *key)
{
	unsigned long	idx;
	t_env			*curr;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (strcmp(curr->key, key) == 0) // rebuild ft_strcmp
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
