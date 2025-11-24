/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:14:19 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/24 16:11:07 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	hash_len(t_env_table *table)
{
	size_t	count;
	size_t	i;
	t_env	*curr;

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

static char	*entry_line(t_env *curr)
{
	char	*entry;
	char	*tmp;

	tmp = ft_strjoin(curr->key, "=");
	entry = ft_strjoin(tmp, curr->value);
	free(tmp);
	return (entry);
}

char	**env_export(t_env_table *table)
{
	char	**envp;
	t_env	*curr;
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
