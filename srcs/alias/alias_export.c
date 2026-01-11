/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:31:33 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 22:33:07 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

static int	hash_len(t_alias_table *table)
{
	size_t	count;
	size_t	i;
	t_alias	*curr;

	count = 0;
	i = 0;
	while (i < table->size)
	{
		curr = table->buckets[i++];
		while (curr)
		{
			count++;
			curr = curr->next;
		}
	}
	return (count);
}

static char	*entry_line(t_alias *curr)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(curr->key, "=");
	entry = ft_strjoin(tmp, curr->value);
	free(tmp);
	return (entry);
}

char	**alias_export(t_alias_table *table)
{
	char	**envp;
	t_alias	*curr;
	size_t	j;
	size_t	i;

	envp = malloc(sizeof(char *) * (hash_len(table) + 1));
	j = 0;
	i = 0;
	while (i < table->size)
	{
		curr = table->buckets[i++];
		while (curr)
		{
			envp[j++] = entry_line(curr);
			curr = curr->next;
		}
	}
	envp[j] = NULL;
	return (envp);
}
