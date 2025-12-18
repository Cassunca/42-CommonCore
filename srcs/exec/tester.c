/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 05:19:35 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/18 13:27:35 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_ast	*new_ast_node(t_node_type type, t_ast *left, t_ast *right, void *content)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->content = content;
	return (node);
}

t_cmd	*new_cmd_content(char **av)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_ast));
	if (!cmd)
		return (NULL);
	cmd->argv = av;
	i = 0;
	while (av[i])
		i++;
	cmd->argc = i;
	return (cmd);
}

int	is_exit (char **av)
{
	if (av && av[0] && !ft_strcmp(av[0], "exit"))
		return (1);
	return (0);
}

int	execute_exit(char **av, char **env)
{
	int	status;

	(void)env;
	printf("exit\n");
	status = 0;
	if (av[1])
		status = ft_atoi(av[1]);
	exit(status);
	return (status);
}




