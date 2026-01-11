/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:28:58 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 22:56:56 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

t_alias	*alias_new(char *key, char *value)
{
	t_alias	*node;

	node = malloc(sizeof(t_alias));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	alias_destroy(t_alias_table *table)
{
	size_t	i;
	t_alias	*curr;
	t_alias	*next;

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
