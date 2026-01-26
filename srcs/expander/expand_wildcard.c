/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:53:39 by amyrodri          #+#    #+#             */
/*   Updated: 2026/01/26 15:37:32 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

static char	**matches_full(char **matches, char *d_name, char *dir_name)
{
	char			*tmp;
	char			*full;

	tmp = ft_strjoin(dir_name, "/");
	full = ft_strjoin(tmp, d_name);
	free(tmp);
	matches = argv_add(matches, full);
	free(full);
	return (matches);
}

static char	**free_matches(char **matches, char **argv)
{
	char	**tmp;

	tmp = matches;
	while (matches && *tmp)
		argv = argv_add(argv, *tmp++);
	free_char_array(matches);
	return (argv);
}

static char	**handle_entry(t_wc *wc, struct dirent *entry)
{
	if (entry->d_name[0] == '.' && wc->pattern[0] != '.')
		return (wc->matches);
	if (!match_pattern(wc->pattern, entry->d_name))
		return (wc->matches);
	if (!ft_strcmp(wc->dir_name, "."))
		wc->matches = argv_add(wc->matches, entry->d_name);
	else
		wc->matches = matches_full(wc->matches,
				entry->d_name, wc->dir_name);
	wc->count++;
	return (wc->matches);
}

char	**wildcard_expand(char	**argv, char *word)
{
	struct dirent	*entry;
	DIR				*dir;
	t_wc			wc;

	split_path(word, &wc.dir_name, &wc.pattern);
	dir = opendir(wc.dir_name);
	if (!dir)
		return (argv_add(argv, word));
	wc.matches = NULL;
	wc.count = 0;
	entry = readdir(dir);
	while (entry)
	{
		handle_entry(&wc, entry);
		entry = readdir(dir);
	}
	closedir(dir);
	free(wc.dir_name);
	free(wc.pattern);
	if (wc.count == 0)
		return (argv_add(argv, word));
	argv = free_matches(wc.matches, argv);
	return (argv);
}
