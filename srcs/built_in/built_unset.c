/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:40:49 by cassunca          #+#    #+#             */
/*   Updated: 2026/01/06 16:22:31 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built.h"

/*
** TODO - Implementar unset corretamente (padrão Bash-like)
**
** Regras Gerais:
**  - unset deve aceitar múltiplos argumentos:
**      unset VAR1 VAR2 VAR3
**
**  - Para cada argumento:
**      * Validar identificador (mesmas regras do export):
**          - Não pode estar vazio
**          - Primeiro caractere: letra (A-Z a-z) ou '_' (underscore)
**          - Demais caracteres: letras, dígitos ou '_'
**          - Não pode conter '=' (ou outros caracteres inválidos)
**          - Se inválido -> imprimir erro:
**              unset: `argumento': not a valid identifier
**            e continuar com os próximos argumentos (não abortar)
**
**  - Comportamento sobre existência:
**      * Se variável existe -> remover do ambiente (env_unset)
**      * Se não existe -> silenciosamente ignorar (sem erro)
**
**  - Atualizar todas as estruturas internas:
**      * Remover também da tabela de "exported" se houver separação
**      * Garantir que não restem ponteiros pendentes
**
**  - Efeitos colaterais / proteções:
**      * Se houver variáveis "read-only" (se implementadas), considerar
**        se unset deve falhar para elas (no simples minishell pode ignorar)
**
**  - Mensagem de erro e códigos de saída:
**      * Se algum argumento inválido -> retornar status de erro (1)
**      * Se todos válidos -> retornar 0
**      * Não imprimir mensagens ao remover com sucesso
**
**  - Segurança / memória:
**      * Não ler além do fim da string (verificar null)
**      * Evitar uso de ft_split para esse caso (não há '=' necessário)
**      * Garantir que env_unset libera recursos corretamente
**
**  - Edge cases:
**      * unset ""          -> considerar inválido (imprimir erro)
**      * unset =VALUE      -> inválido
**      * unset 2VAR        -> inválido
**      * unset _VAR        -> válido
**
** Exemplos:
**  unset VAR          -> remove VAR se existir
**  unset VAR1 VAR2    -> remove ambos
**  unset 2ERR         -> printa erro e retorna 1, continua com outros args
*/

static int	is_valid_key(char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env_table *env, t_cmd *cmd)
{
	int	i;


	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_key(cmd->argv[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			i++;
			continue ;
		}
		env_unset(env, cmd->argv[i]);
		i++;
	}
}
