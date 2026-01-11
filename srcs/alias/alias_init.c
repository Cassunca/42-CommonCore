/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 23:45:51 by kamys             #+#    #+#             */
/*   Updated: 2026/01/10 22:55:22 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

static char	*extract_alias_value(char *line)
{
	char	*value;
	char	*start;

	if (!line)
		return (NULL);
	start = ft_strchr(line, '=');
	if (!start)
		return (NULL);
	start++;
	value = ft_strtrim(start, "\"\n");
	return (value);
}

static char	*extract_alias_key(char *line)
{
	char	*key;
	char	*equal;
	char	*start;
	size_t	len;

	if (!line)
		return (NULL);
	start = line + 6;
	equal = ft_strchr(line, '=');
	if (!equal)
		return (NULL);
	len = equal - start;
	key = ft_substr(start, 0, len);
	return (key);
}

static int	handle_alias(t_alias_table *alias, char *line)
{
	char	*trim;
	char	*alias_key;
	char	*alias_value;

	(void)alias;
	trim = skip_whitespace(line);
	if (*trim == '#' || *trim == '\0')
		return (0);
	if (!ft_strncmp(trim, "alias", 5))
	{
		alias_key = extract_alias_key(trim);
		alias_value = extract_alias_value(trim);
		if (alias_key && alias_value)
		{
			alias_set(alias, alias_key, alias_value);
			free(alias_key);
			free(alias_value);
		}
		return (1);
	}
	return (0);
}

static int	load_rc_alias(t_alias_table *alias)
{
	int		fd;
	char	*line;

	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		handle_alias(alias, line);
		free(line);
	}
	close(fd);
	return (0);
}

t_alias_table	*init_alias(size_t size)
{
	t_alias_table	*alias;

	alias = malloc(sizeof(t_alias_table));
	if (!alias)
		return (NULL);
	alias->buckets = ft_calloc(size, sizeof(t_alias *));
	alias->size = size;
	load_rc_alias(alias);
	return (alias);
}
