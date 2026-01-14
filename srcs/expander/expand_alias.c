/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 23:15:01 by kamys             #+#    #+#             */
/*   Updated: 2026/01/22 12:16:42 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static	int	len_st(char	**s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static	void	free_argv(char **arg)
{
	int	i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}

static void	replace_arg(t_cmd *cmd, char *alias_val)
{
	char	**new_argv;
	char	**alias_words;
	int		i;
	int		j;

	alias_words = ft_split(alias_val, ' ');
	new_argv = malloc(sizeof(char *) * (cmd->argc + len_st(alias_words) + 1));
	i = 0;
	while (alias_words[i])
	{
		new_argv[i] = ft_strdup(alias_words[i]);
		i++;
	}
	j = 1;
	while (cmd->argv[j])
		new_argv[i++] = ft_strdup(cmd->argv[j++]);
	new_argv[i] = NULL;
	free_argv(cmd->argv);
	free_argv(alias_words);
	cmd->argv = new_argv;
}

static void	expand_alias(t_cmd *cmd, t_shell *sh)
{
	char	*alias_val;

	if (!cmd->argv || !cmd->argv[0] || cmd->alias_expanded)
		return ;
	alias_val = alias_get(sh->aliases, cmd->argv[0]);
	if (!alias_val)
		return ;
	replace_arg(cmd, alias_val);
	cmd->alias_expanded = 1;
}

void	expand_alias_ast(t_ast *root, t_shell *sh)
{
	if (!root)
		return ;
	if (root->type == NODE_CMD)
		expand_alias((t_cmd *)root->content, sh);
	expand_alias_ast(root->left, sh);
	expand_alias_ast(root->right, sh);
}
