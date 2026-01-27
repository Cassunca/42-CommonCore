/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:08:56 by kamys             #+#    #+#             */
/*   Updated: 2026/01/27 15:12:30 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	pid_minishell(char	**res, int	*i)
{
	char	*pid;

	pid = ft_itoa(getpid());
	append_str(res, pid);
	free(pid);
	(*i)++;
}

void	handle_dolar(char **res, char *s, int *i, t_shell *sh)
{
	char	*var;
	char	*val;
	int		start;

	(*i)++;
	if (!s[*i])
		return (append_char(res, '$'));
	if (s[*i] == '$')
		return (pid_minishell(res, i));
	if (s[*i] == '?')
	{
		append_str(res, ft_itoa(sh->last_status));
		(*i)++;
		return ;
	}
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
		return (append_char(res, '$'));
	start = *i;
	while (ft_isalnum(s[*i]) || s[*i] == '_')
		(*i)++;
	var = ft_substr(s, start, *i - start);
	val = env_get(sh->env, var);
	if (val)
		append_str(res, val);
	free(var);
}
