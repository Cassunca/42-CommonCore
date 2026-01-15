/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:21:20 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/15 12:50:03 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

int	key_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

int	key_cmp(const char *s1, const char *s2)
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

int	alias_len(t_alias_table *table)
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

void	print_alias(char **order)
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

int	is_valid_key(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == ' ' && s[i] == '\t')
			return (0);
		i++;
	}
	if (i == 0 && s[i] != '=')
		return (0);
	return (1);
}

void	parse_alias(char *s, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(s, '=');
	if (!eq)
	{
		*key = ft_strdup(s);
		*value = NULL;
		return ;
	}
	*key = ft_substr(s, 0, eq - s);
	*value = ft_strdup(eq + 1);
}

void	handle_alias(t_alias_table *alias, char *s)
{
	char	*key;
	char	*value;

	parse_alias(s, &key, &value);
	if (!is_valid_key(key))
	{
		ft_putstr_fd("alias: ", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		free(key);
		free(value);
		return ;
	}
	if (!ft_strchr(s, '='))
	{
		value = alias_get(alias, key);
		if (value)
			printf("alias %s='%s'\n", key, value);
		free(key);
		return ;
	}
	alias_set(alias, key, value);
	free(key);
	free(value);
}

void	alias(t_alias_table *alias, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[i])
		return (display_alias(alias));
	while (cmd->argv[i])
		handle_alias(alias, cmd->argv[i++]);
}
