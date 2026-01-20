/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassunca <cassunca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 18:09:14 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/20 15:51:52 by cassunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int handle_cmd_heredocs(void *content, t_shell *sh)
{
    t_redir *current;
    t_cmd   *cmd;

    cmd = (t_cmd *)content;
    if (!cmd || !cmd->redir)
        return (0);
    current = cmd->redir;
    while (current)
    {
        if (current->type == REDIR_HEREDOC)
        {
            if (exec_heredoc(current, sh) == INTERRUPTED_BY_SIGINT)
                return (INTERRUPTED_BY_SIGINT);
        }
        current = current->next;
    }
    return (0);
}

int traverse_ast_heredoc(t_ast *node, t_shell *sh)
{
    int status;

    if (!node)
        return (0);
    if (node->type == NODE_CMD)
        return (handle_cmd_heredocs(node->content, sh));
    status = traverse_ast_heredoc(node->left, sh);
    if (status != 0)
        return (status);
    return (traverse_ast_heredoc(node->right, sh));
}
