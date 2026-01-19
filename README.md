# 🐚 minishell

> `minishell` é uma implementação em **C** de um interpretador de comandos inspirado no **bash**, capaz de executar comandos externos, builtins, gerenciar **pipes**, **redirecionamentos**, **variáveis de ambiente** e **sinais**, simulando o comportamento básico de um shell Unix.

> Este projeto foi desenvolvido em parceria por [**Amy Rodrigues**](https://github.com/AmyRodri) e [**Christian Assunção**](https://github.com/Cassunca), como parte do currículo da escola 42, com foco no estudo de **processos**, **execução concorrente**, **comunicação entre processos** e **gerenciamento de descritores de arquivo**.

![Banner](https://img.shields.io/badge/Project-minishell-blueviolet)
![C](https://img.shields.io/badge/Language-C-red)
![42](https://img.shields.io/badge/School-42-black)
![Status](https://img.shields.io/badge/Status-%20Completed-green)

---

## 🎯 Objetivo

O objetivo do **minishell** é desenvolver um interpretador de comandos funcional, inspirado no **bash**, capaz de reproduzir o comportamento essencial de um shell Unix.

O projeto tem como foco principal:
- Interpretar e executar **comandos externos** utilizando `fork`, `execve` e `wait`.
- Implementar **pipes** (`|`) para comunicação entre múltiplos processos.
- Gerenciar **redirecionamentos de entrada e saída**, incluindo `<`, `>`, `>>` e `<<` (heredoc).
- Implementar **builtins** essenciais, como `cd`, `echo`, `pwd`, `export`, `unset`, `env` e `exit`.
- Manipular corretamente **variáveis de ambiente**, incluindo expansão (`$VAR`, `$?`).
- Tratar **sinais do sistema** (`SIGINT`, `SIGQUIT`, `EOF`) de forma semelhante ao bash.
- Garantir gerenciamento correto de **memória** e **descritores de arquivo**, evitando vazamentos e comportamentos indefinidos.

Além disso, o projeto visa aprofundar a compreensão de conceitos fundamentais de sistemas operacionais, como **processos**, **execução concorrente**, **comunicação entre processos**, **controle de sinais** e **arquitetura de software em C**.

---

## 💻 Como usar  

#### 📦 Compilação com Makefile

Para compilar o projeto, execute o comando abaixo no terminal:

```bash
make
```
O comando irá compilar todos os arquivos-fonte e gerar o executável `minishell`.

♻️ Comandos do Makefile

O projeto inclui os seguintes alvos no Makefile:

- `make`
> Compila o projeto.

- `make clean`
> Remove os arquivos objeto (`.o`).

- `make fclean`
> Remove os arquivos objeto e o executável.

- `make re`
> Recompila o projeto do zero (faz `fclean` seguido de `all`).

## ▶️ Execução

Após a compilação, execute o programa utilizando o comando abaixo:

```bash
./minishell
```

Ao iniciar, o minishell exibirá um prompt interativo, no qual é possível digitar comandos da mesma forma que em um shell Unix tradicional.

**Exemplos de uso**
```bash
ls -la
echo "Hello, minishell"
ls | grep minishell
cat < input.txt | wc -l > output.txt
```

> Para encerrar o programa, utilize o comando `exit` ou pressione `Ctrl + D`.

**Modo não interativo (-c)**
```bash
./minishell -c "comando1 | comando2 > arquivo"
```

Executa o(s) comando(s) fornecido(s) como argumento e encerra o programa após a execução.

Esse modo é útil para testes automatizados, scripts ou execuções pontuais.

**Exemplos**
```bash
./minishell -c "echo Hello, minishell"
./minishell -c "ls -la | grep minishell"
```
---

## ⚙️ Funcionalidades

O **minishell** implementa funcionalidades essenciais de um shell Unix, reproduzindo o comportamento esperado do **bash** dentro do escopo do projeto.

### 🔹 Execução de Comandos
- Execução de **comandos externos** a partir das variáveis de ambiente (`PATH`).
- Suporte a **argumentos**, aspas simples (`'`) e aspas duplas (`"`).
- Resolução de caminhos relativos e absolutos.

### 🔹 Builtins
O projeto implementa os seguintes comandos internos:
- `echo` (com suporte à flag `-n`)
- `cd` (com caminhos relativos, absolutos e `~`)
- `pwd`
- `export`
- `unset`
- `env`
- `alias`
- `unalias`
- `exit`

### 🔹 Pipes
- Suporte a **pipelines** com o operador `|`.
- Execução correta de múltiplos comandos encadeados.
- Comunicação entre processos através de **pipes anônimos**.

### 🔹 Redirecionamentos
- Redirecionamento de entrada (`<`)
- Redirecionamento de saída (`>`)
- Redirecionamento de saída em modo append (`>>`)
- **Heredoc** (`<<`), com leitura interativa até o delimitador definido.

### 🔹 Variáveis de Ambiente
- Expansão de variáveis com `$VAR`.
- Expansão do código de saída do último comando (`$?`).
- Manipulação dinâmica do ambiente com `export` e `unset`.

### 🔹 Alias
- Suporte à definição de **alias de comandos**.
- Expansão automática de alias antes da execução.
- Carregamento de alias a partir do arquivo de configuração `.minishellrc`.

### 🔹 Prompt Personalizável
- Suporte a **prompt configurável**.
- Leitura das configurações de prompt a partir do arquivo `.minishellrc`.
- Atualização dinâmica do prompt conforme variáveis e contexto de execução.

### 🔹 Sinais
- Tratamento adequado de sinais:
  - `Ctrl + C` (`SIGINT`)
  - `Ctrl + \` (`SIGQUIT`)
  - `Ctrl + D` (EOF)
- Comportamento consistente com o bash em modo interativo.

### 🔹 Modo de Execução
- **Modo interativo**, com prompt persistente.
- **Modo não interativo** (`-c`), permitindo execução direta de comandos.

### 🔹 Gerenciamento de Recursos
- Gerenciamento correto de **memória dinâmica**.
- Fechamento adequado de **descritores de arquivo**.
- Execução validada com ferramentas como `valgrind`, sem vazamentos de memória.

---

## 🧠 Conceitos Trabalhados

O desenvolvimento do **minishell** envolveu o estudo e a aplicação prática de conceitos fundamentais de **sistemas operacionais** e **programação em C**, essenciais para a compreensão do funcionamento interno de um shell Unix.

### 🔹 Processos
- Criação e gerenciamento de processos com `fork`.
- Execução de programas utilizando `execve`.
- Sincronização e controle do fluxo de execução com `wait` e `waitpid`.

### 🔹 Comunicação entre Processos
- Uso de **pipes** para transmissão de dados entre processos.
- Encadeamento de múltiplos comandos em pipelines.
- Gerenciamento correto de entrada e saída entre processos conectados.

### 🔹 Redirecionamento de Arquivos
- Manipulação de **descritores de arquivo**.
- Redirecionamento de entrada e saída com `dup2`.
- Controle de leitura e escrita em arquivos e heredocs.

### 🔹 Sinais
- Tratamento de sinais do sistema (`SIGINT`, `SIGQUIT`, `EOF`).
- Diferença de comportamento entre processos pai e filhos.
- Implementação de sinais compatível com o comportamento do bash.

### 🔹 Parsing e Interpretação de Comandos
- Tokenização da linha de comando.
- Análise sintática para identificação de comandos, operadores e redirecionamentos.
- Organização da execução respeitando precedência e estrutura dos comandos.

### 🔹 Variáveis de Ambiente
- Representação e manipulação do ambiente em estruturas próprias.
- Expansão de variáveis durante a interpretação dos comandos.
- Atualização dinâmica do ambiente em tempo de execução.

### 🔹 Gerenciamento de Memória
- Uso seguro de alocação dinâmica (`malloc`, `free`).
- Prevenção de vazamentos de memória.
- Validação com ferramentas de análise como `valgrind`.

### 🔹 Arquitetura de Software
- Separação clara de responsabilidades entre módulos.
- Organização do código visando legibilidade, manutenção e extensibilidade.
- Implementação seguindo boas práticas de programação em C.

---

## ⚠️ Limitações Conhecidas

Embora o **minishell** implemente funcionalidades essenciais de um shell Unix, algumas características do **bash** completo não fazem parte do escopo deste projeto.

As principais limitações conhecidas incluem:

- Não há suporte a **expansão de curingas** (*wildcards*), como `*`, `?` e `[]`.
- Não há suporte a **controle de jobs** (`fg`, `bg`, `jobs`).
- O comportamento do **prompt** e de algumas mensagens de erro pode diferir do bash em casos específicos.
- O projeto não implementa **scripts shell** nem execução de arquivos `.sh`.
- O tratamento de erros pode não cobrir todos os casos extremos presentes no bash.

Essas limitações estão alinhadas com os requisitos do projeto **minishell** da escola 42 e não comprometem os objetivos educacionais do trabalho.

---

## 🗂️ Estrutura do Projeto

A organização do projeto foi pensada para separar responsabilidades e facilitar a manutenção e compreensão do código.

```text
.
├── include
└── srcs
    ├── alias
    ├── built_in
    ├── env
    ├── exec
    ├── expander
    ├── lexer
    ├── parser
    ├── prompt
    └── utils
```

📁 Diretórios

* `include/`
> Contém os arquivos de cabeçalho (.h), com definições de estruturas, protótipos de funções e macros utilizadas em  todo o projeto.

* `srcs/alias/`
> Implementação do sistema de alias, incluindo definição, armazenamento e expansão de comandos.

* `srcs/built_in/`
> Implementação dos builtins do minishell (cd, echo, export, unset, env, pwd, exit).

* `srcs/env/`
> Gerenciamento das variáveis de ambiente, incluindo criação, modificação, remoção e expansão.

* `srcs/exec/`
> Responsável pela execução dos comandos, criação de processos, gerenciamento de pipes, redirecionamentos e chamadas a execve.

* `srcs/expander/`
> Tratamento de expansões, como variáveis de ambiente, código de saída ($?) e alias antes da execução.

* `srcs/lexer/`
> Tokenização da linha de comando, identificando palavras, operadores, pipes e redirecionamentos.

* `srcs/parser/`
> Análise sintática dos tokens gerados pelo lexer e construção da estrutura necessária para a execução dos comandos.

* `srcs/prompt/`
> Implementação do prompt personalizável, incluindo leitura de configurações e atualização dinâmica.

* `srcs/utils/`
> Funções auxiliares reutilizáveis em todo o projeto (strings, listas, gerenciamento de memória, etc.).

---

## 👩‍💻 Autoria

**✨ [Amy Rodrigues](https://github.com/AmyRodri) ✨**  
**✨ [Christian Assunção](https://github.com/Cassunca) ✨**

🎓 Estudantes de **C** e **desenvolvimento de baixo nível** na **[42 São Paulo](https://www.42sp.org.br/)**  
🐧 Entusiastas de **Linux** | 💻 Amantes de **terminal**  
⚙️ Apaixonados por entender **como as coisas realmente funcionam por trás dos bastidores**

---

## 📎 Licença

Este projeto foi desenvolvido como parte do currículo educacional da 42 São Paulo.

📘 **Uso permitido**:
- Pode ser utilizado como referência para estudos e aprendizado individual
- Pode servir de inspiração para seus próprios projetos

🚫 **Proibido**:
- Submeter cópias deste projeto como se fossem de sua autoria em avaliações da 42 ou outras instituições

Seja ético e contribua para uma comunidade de desenvolvedores mais honesta e colaborativa 🤝
