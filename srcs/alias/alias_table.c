/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:29:54 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 22:36:50 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	alias_set(t_alias_table *table, char *key, char *value)
{
	unsigned long	idx;
	t_alias			*curr;
	t_alias			*new;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	new = alias_new(key, value);
	new->next = table->buckets[idx];
	table->buckets[idx] = new;
}

void	alias_unset(t_alias_table *table, char *key)
{
	unsigned long	idx;
	t_alias			*curr;
	t_alias			*prev;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
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

char	*alias_get(t_alias_table *table, char *key)
{
	unsigned long	idx;
	t_alias			*curr;

	idx = hash(key) % table->size;
	curr = table->buckets[idx];
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}
