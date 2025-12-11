/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 04:05:57 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/11 05:31:32 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin(char **av)
{
	(void)av;
	return (0);
}

int	execute_builtin(char **av)
{
	(void)av;
	printf("DEBUG: Executing mocked builtin.\n");
	return (0);
}

char	*resolve_path(char *cmd, char **envp)
{
	(void)envp;
	if (strcmp(cmd, "ls") == 0)
		return (strdup("/bin/ls"));
	if (strcmp(cmd, "cat") == 0)
		return (strdup("/bin/cat"));
	return (strdup(cmd));
}

t_ast	*built_ast(t_token *tokens)
{
	char	**av_ls;
	t_cmd	*cmd_content;
	t_ast	*root_node;

	(void)tokens;
	av_ls = (char **)malloc(sizeof(char *) * 3);
	if (!av_ls)
		return (NULL);
	av_ls[0] = ft_strdup("ls");
	av_ls[1] = ft_strdup("-l");
	av_ls[2] = NULL;
	cmd_content = new_cmd_content(av_ls);
	if (!cmd_content)
		return (NULL);
	root_node = new_ast_node(NODE_CMD, NULL, NULL, cmd_content);
	printf("--- DEBUG: AST para 'ls -l' criada manualmente ---\n");
	return (root_node);
}
