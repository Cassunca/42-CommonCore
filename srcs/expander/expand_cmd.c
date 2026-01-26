/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:05:34 by kamys             #+#    #+#             */
/*   Updated: 2026/01/26 00:58:25 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	**argv_add(char **argv, char *word)
{
	int		i;
	char	**new;

	i = 0;
	while (argv && argv[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (argv && argv[i])
	{
		new[i] = argv[i];
		i++;
	}
	new[i++] = ft_strdup(word);
	new[i] = NULL;
	free(argv);
	return (new);
}

static int	match_pattern(char *p, char *s)
{
	if (!*p && !*s)
		return (1);
	if (*p == '*')
		return (match_pattern(p + 1, s)
			|| (*s && match_pattern(p, s + 1)));
	if (*p == '?')
		return (*s && match_pattern(p + 1, s + 1));
	if (*p == *s)
		return (match_pattern(p + 1, s + 1));
	return (0);
}

static void	split_path(char *word, char **dir, char **pat)
{
	char	*slash;

	slash = ft_strrchr(word, '/');
	if (!slash)
	{
		*dir = ft_strdup(".");
		*pat = ft_strdup(word);
	}
	else
	{
		*dir = ft_substr(word, 0, slash - word);
		*pat = ft_strdup(slash + 1);
	}
}

static char	**wildcard_expand(char	**argv, char *word)
{
	struct dirent	*entry;
	char			**matches;
	char			*dir_name;
	char			*pattern;
	char			*full;
	DIR				*dir;
	int				count;

	split_path(word, &dir_name, &pattern);
	dir = opendir(dir_name);
	if (!dir)
		return (argv_add(argv, word));
	matches = NULL;
	count = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			if (ft_strcmp(dir_name, ".") == 0)
				matches = argv_add(matches, entry->d_name);
			else
			{
				char	*tmp;
				tmp = ft_strjoin(dir_name, "/");
				full = ft_strjoin(tmp, entry->d_name);
				free(tmp);
				matches = argv_add(matches, full);
				free(full);
			}
			count++;
		}
	}
	closedir(dir);
	free(dir_name);
	free(pattern);
	if (count == 0)
		return (argv_add(argv, word));
	char	**tmp;
	tmp = matches;
	while (matches && *tmp)
		argv = argv_add(argv, *tmp++);
	free_char_array(matches);
	return (argv);
}

static int	has_wildcard(const char *s)
{
	return (ft_strchr(s, '*') || ft_strchr(s, '?'));
}

void	restore_wildcard(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\a')
			s[i] = '*';
		i++;
	}
}

void	expand_cmd(t_cmd *cmd, t_shell *sh)
{
	char	**new;
	char	*word;
	int		i;

	i = 0;
	new = NULL;
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		word = expand_word(cmd->argv[i], sh);
		if (has_wildcard(word))
			new = wildcard_expand(new, word);
		else
		{
			restore_wildcard(word);
			new = argv_add(new, word);
		}
		free(word);
		i++;
	}
	free(cmd->argv);
	cmd->argv = new;
}
