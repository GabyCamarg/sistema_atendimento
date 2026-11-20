# Sistema de Atendimento Hospitalar

Projeto desenvolvido em C++ para a disciplina de Programação e Estruturas de Dados.

## Objetivo

Simular um sistema de atendimento hospitalar utilizando estruturas de dados lineares com alocação dinâmica de memória.

## Requisitos implementados

### R1 - Fila de pacientes
- Inserção com enqueue.
- Remoção com dequeue.
- Consulta com frente_peek.
- Contagem de pacientes.

### R2 - Pilha de histórico
- Inserção com push.
- Remoção com pop.
- Consulta com peek.

### R3 - Lista de médicos
- Cadastro de médicos.
- Chamada do primeiro médico disponível.
- Percurso da lista.
- Retorno do médico ao final da lista após o atendimento.

### R4 - Relatório de atendimentos
- Exibição dos atendimentos do mais recente ao mais antigo.
- Utilização de uma pilha auxiliar.
- Preservação do histórico original.

## Estruturas utilizadas
- Fila encadeada.
- Pilha encadeada.
- Lista simplesmente encadeada.

## Tecnologias
- C++
- Compilador g++

## Como compilar

g++ -std=c++17 -Wall -Wextra -pedantic atendimento_template.cpp -o atendimento

## Como executar

./atendimento

## Gerenciamento de memória

O projeto utiliza alocação dinâmica com new e desalocação com delete, incluindo destrutores para liberar os nós das estruturas.

## Exemplo de saída

```text
SISTEMA DE ATENDIMENTO HOSPITALAR

--- Simulacao de atendimentos ---
[1] Dra. Ana Lima atende Eduardo (urgencia=3)
[2] Dr. Bruno Costa atende Fernanda (urgencia=1)
[3] Dra. Carla Ramos atende Gabriel (urgencia=2)
[4] Dra. Ana Lima atende Helena (urgencia=1)

=== RELATORIO DE ATENDIMENTOS ===
Atendimentos (mais recente ao mais antigo):
- Dra. Ana Lima atende Helena (urgencia=1)
- Dra. Carla Ramos atende Gabriel (urgencia=2)
- Dr. Bruno Costa atende Fernanda (urgencia=1)
- Dra. Ana Lima atende Eduardo (urgencia=3)

--- Verificacao da preservacao ---
Ultimo atendimento antes do relatorio:
Dra. Ana Lima atende Helena (urgencia=1)

Ultimo atendimento depois do relatorio:
Dra. Ana Lima atende Helena (urgencia=1)
```
