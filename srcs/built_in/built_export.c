/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:28:05 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/06 15:10:37 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

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

static char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*new_str;

	len1 = 0;
	len2 = 0;
	len3 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	if (s3)
		len3 = ft_strlen(s3);
	new_str = malloc(len1 + len2 + len3 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		ft_memcpy(new_str, s1, len1);
	if (s2)
		ft_memcpy(new_str + len1, s2, len2);
	if (s3)
		ft_memcpy(new_str + len1 + len2, s3, len3);
	new_str[len1 + len2 + len3] = '\0';
	return (new_str);
}

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

void display_export(t_env_table *env)
{
	size_t	i;
	size_t	j;
	t_env	*curr;
	char	**order;

	order = malloc(sizeof(char *) * (hash_len(env) + 1));
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
}

static int	is_valid_key(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' || s[i + 1] == '+')
			return (1);
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	is_append(char *s)
{
	char	*eq;

	eq = ft_strchr(s, '=');
	if (eq && eq > s && *(eq - 1) == '+')
		return (1);
	return (0);
}

static void	parse_export(char *s, char **key, char **value, int append)
{
	char	*eq;

	eq = ft_strchr(s, '=');
	if (!eq)
	{
		*key = ft_strdup(s);
		*value = NULL;
		return ;
	}
	*key = ft_substr(s, 0, eq - s - append);
	*value = ft_strdup(eq + 1);
}

static void apply_export(t_env_table *env, char *key, char *value, int append)
{
	char	*old;
	char	*new;

	if (!append)
		return (env_set(env, key, value));
	old = env_get(env, key);
	if (!old)
		return (env_set(env, key, value));
	if (!value || !*value)
		return ;
	new = ft_strjoin(old, value);
	env_set(env, key, new);
	free(new);
}

static void	handle_export(t_env_table *env, char *s)
{
	char	*key;
	char	*value;
	int		append;

	append = is_append(s);
	parse_export(s, &key, &value, append);
	if (!is_valid_key(key))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		free(key);
		free(value);
		return ;
	}
	if (!ft_strchr(s, '='))
	{
		if (!env_get(env, key))
			env_set(env, key, ft_strdup(""));
		free(key);
		return ;
	}
	apply_export(env, key, value, append);
	free(key);
	free(value);
}

void	export(t_env_table *env, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[i])
		return (display_export(env));
	while (cmd->argv[i])
		handle_export(env, cmd->argv[i++]);
}
