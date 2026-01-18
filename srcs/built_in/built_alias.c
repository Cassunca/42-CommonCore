/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:21:20 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/18 11:51:40 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

static int	is_valid_key(char *s)
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

static void	parse_alias(char *s, char **key, char **value)
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

static void	handle_alias(t_alias_table *alias, char *s)
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
