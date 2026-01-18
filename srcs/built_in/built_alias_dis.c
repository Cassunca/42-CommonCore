/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias_dis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:51:18 by kamys             #+#    #+#             */
/*   Updated: 2026/01/18 11:57:31 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	alias_len(t_alias_table *table)
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

static void	print_alias(char **order)
{
	int		i;
	char	*eq;

	i = 0;
	while (order[i])
	{
		eq = ft_strchr(order[i], '=');
		if (eq)
		{
			write(1, order[i], eq - order[i]);
			write(1, "=", 1);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\n", 1);
		}
		else
		{
			write(1, order[i], ft_strlen(order[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

static void	order_array(char **array)
{
	int		i;
	int		j;
	char	*key;

	i = 1;
	while (array[i])
	{
		key = array[i];
		j = i - 1;
		while (j >= 0 && key_cmp(array[j], key) > 0)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
		i++;
	}
}

void	display_alias(t_alias_table *alias)
{
	size_t	i;
	size_t	j;
	t_alias	*curr;
	char	**order;

	order = malloc(sizeof(char *) * (alias_len(alias) + 1));
	i = 0;
	j = 0;
	while (i < alias->size)
	{
		curr = alias->buckets[i++];
		while (curr)
		{
			order[j++] = ft_strjoin3(curr->key, "=", curr->value);
			curr = curr->next;
		}
	}
	order[j] = NULL;
	order_array(order);
	print_alias(order);
	i = 0;
	while (order[i])
		free(order[i++]);
	free(order);
}
