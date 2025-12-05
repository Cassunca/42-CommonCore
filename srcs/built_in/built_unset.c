/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:40:49 by cassunca          #+#    #+#             */
/*   Updated: 2025/12/05 16:46:15 by kamys            ###   ########.fr       */
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

void	unset(t_env_table *env, char *key)
{
	char	*start;
	// punk, quase igual ao export vamo meter bala na agulha
	start = key;
	while (*start)
	{
		if (*start == '=')
			return ;
		start++;
	}
	env_unset(env, key);
}
