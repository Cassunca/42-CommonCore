/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:56:28 by kamys             #+#    #+#             */
/*   Updated: 2026/01/06 18:28:24 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

static char	*cwd_tail(char *cwd, int depth)
{
	char	*p;

	if (!cwd || depth <= 0)
		return (cwd);
	p = cwd + ft_strlen(cwd);
	while (p > cwd && depth > 0)
	{
		p--;
		if (*p == '/')
			depth--;
	}
	if (p <= cwd)
		return (cwd);
	return (p + 1);
}

static char	*expand_cwd(char limit)
{
	char	*cwd;
	char	*tail;
	char	*res;
	int		depth;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("~"));
	depth = ft_atoi(&limit);
	if (depth < 1)
		depth = 1;
	if (depth > 9)
		depth = 9;
	tail = cwd_tail(cwd, depth);
	res = ft_strdup(tail);
	free(cwd);
	return (res);
}

static char	*interpret_escapes(char *s)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_strncmp(&s[i], "\\x1b", 4))
		{
			res[j++] = '\001';
			res[j++] = 27;
			res[j++] = '\002';
			i += 4;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

static char	*resolve_prompt_token(t_env_table *env, char *s, int *i)
{
	char	*val;

	val = NULL;
	if (s[*i + 1] == 'u')
	{
		val = env_get(env, "USER");
		*i += 2;
	}
	else if (s[*i + 1] == 'd')
	{
		val = cwd_with_tilde(env);
		*i += 2;
	}
	else if (ft_isdigit(s[*i + 1]) && s[*i + 2] == 'd')
	{
		val = expand_cwd(s[*i + 1]);
		*i += 3;
	}
	return (val);
}

static size_t	prompt_len(t_env_table *env, char *s)
{
	size_t	len;
	char	*val;
	int		i;

	len = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			val = resolve_prompt_token(env, s, &i);
			if (val)
			{
				len += ft_strlen(val);
				if (val != env_get(env, "USER"))
					free(val);
				continue ;
			}
		}
		len++;
		i++;
	}
	return (len);
}

static void	append_prompt_value(t_env_table *env, char **val, char **res, int *j)
{
	char	*p;

	p = *val;
	while (*p)
		(*res)[(*j)++] = *p++;
	if (*val != env_get(env, "USER"))
		free(*val);
}

static char	*interpret_vars(t_env_table *env, char *s)
{
	char	*res;
	char	*val;
	int		i;
	int		j;

	res = malloc(prompt_len(env, s) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1])
		{
			val = resolve_prompt_token(env, s, &i);
			if (val)
			{
				append_prompt_value(env, &val, &res, &j);
				continue ;
			}
		}
		res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

static char	*skip_whitespace(char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

static char	*parse_ps1(t_env_table *env, char *line)
{
	char	*raw;
	char	*escaped;
	char	*final;

	raw = ft_strtrim(skip_whitespace(line) + 7, "\"\n");
	if (!raw)
		return (NULL);
	escaped = interpret_escapes(raw);
	free(raw);
	if (!escaped)
		return (NULL);
	final = interpret_vars(env, escaped);
	free(escaped);
	return (final);
}

static int	handle_ps1(t_env_table *env, char *line)
{
	char	*trim;
	char	*ps1;

	trim = skip_whitespace(line);
	if (*trim == '#' || *trim == '\0')
		return (0);
	if (!ft_strncmp(trim, "PROMPT=", 7))
	{
		ps1 = parse_ps1(env, line);
		if (ps1)
		{
			env_set(env, "PS1", ps1);
			free(ps1);
		}
		return (1);
	}
	return (0);
}

static int	load_rc(t_env_table *env)
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
		if (handle_ps1(env, line))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}

void	init_ps1(t_env_table *env)
{
	if (env_get(env, "PS1"))
		return ;
	if (!load_rc(env))
		prompt_default(env);
}

char	*get_prompt(t_env_table *env)
{
	char	*ps1;

	ps1 = env_get(env, "PS1");
	if (!ps1)
		return ("minishell$ ");
	return (ps1);
}
