/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_dis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:28:32 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 12:16:48 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	key_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

static int	key_cmp(const char *s1, const char *s2)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	len1 = key_len(s1);
	len2 = key_len(s2);
	while (i < len1 && i < len2)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (len1 - len2);
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

static void	print_export(char **order)
{
	int		i;
	char	*eq;

	i = 0;
	while (order[i])
	{
		write(1, "declare -x ", 11);
		eq = ft_strchr(order[i], '=');
		if (eq)
		{
			write(1, order[i], eq - order[i]);
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq) + 1);
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, order[i], ft_strlen(order[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	display_export(t_env_table *env)
{
	size_t	i;
	size_t	j;
	t_env	*curr;
	char	**order;

	order = malloc(sizeof(char *) * (env_len(env) + 1));
	i = 0;
	j = 0;
	while (i < env->size)
	{
		curr = env->buckets[i];
		while (curr)
		{
			order[j++] = ft_strjoin3(curr->key, "=", curr->value);
			curr = curr->next;
		}
		i++;
	}
	order[j] = NULL;
	order_array(order);
	print_export(order);
	i = 0;
	while (order[i])
		free(order[i++]);
	free(order);
}
