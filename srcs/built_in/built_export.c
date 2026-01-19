/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:28:05 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/22 12:17:33 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

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

static void	apply_export(t_env_table *env, char *key, char *value, int append)
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
