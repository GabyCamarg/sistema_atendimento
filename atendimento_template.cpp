#include <iostream>
#include <string>
using namespace std;

// Estrutura base do professor - nao modificar
struct No {
    string nome;
    int urgencia;
    No* prox;
    No(const string& n, int u = 0)
        : nome(n), urgencia(u), prox(nullptr) {}
};

// R1 - FILA DE PACIENTES (FIFO)
struct FilaPacientes {
    No* frente = nullptr;
    No* tras = nullptr;

    void enqueue(const string& nome, int urgencia) {
        No* novo = new No(nome, urgencia);
        if (frente == nullptr) {
            frente = novo;
            tras = novo;
        } else {
            tras->prox = novo;
            tras = novo;
        }
    }

    string dequeue() {
        if (frente == nullptr) return "";
        No* temp = frente;
        string nome = temp->nome;
        frente = frente->prox;
        if (frente == nullptr) tras = nullptr;
        delete temp;
        return nome;
    }

    string frente_peek() const {
        if (frente == nullptr) return "";
        return frente->nome;
    }

    bool isEmpty() const {
        return frente == nullptr;
    }

    int tamanho() const {
        int contador = 0;
        No* atual = frente;
        while (atual != nullptr) {
            contador++;
            atual = atual->prox;
        }
        return contador;
    }

    ~FilaPacientes() {
        while (!isEmpty()) dequeue();
    }
};

// R2 - PILHA DE HISTORICO (LIFO)
struct PilhaHistorico {
    No* topo = nullptr;

    void push(const string& nome, int urgencia = 0) {
        No* novo = new No(nome, urgencia);
        novo->prox = topo;
        topo = novo;
    }

    string pop() {
        if (topo == nullptr) return "";
        No* temp = topo;
        string nome = temp->nome;
        topo = topo->prox;
        delete temp;
        return nome;
    }

    string peek() const {
        if (topo == nullptr) return "";
        return topo->nome;
    }

    bool isEmpty() const {
        return topo == nullptr;
    }

    ~PilhaHistorico() {
        while (!isEmpty()) pop();
    }
};

// R3 - LISTA ENCADEADA DE MEDICOS
struct ListaMedicos {
    No* inicio = nullptr;

    void adicionarMedico(const string& nome) {
        No* novo = new No(nome);

        if (inicio == nullptr) {
            inicio = novo;
        } else {
            No* atual = inicio;
            while (atual->prox != nullptr) {
                atual = atual->prox;
            }
            atual->prox = novo;
        }
    }

    string chamarMedico() {
        if (inicio == nullptr) return "";

        No* temp = inicio;
        string nome = temp->nome;
        inicio = inicio->prox;
        delete temp;

        return nome;
    }

    void percorrer() const {
        if (inicio == nullptr) {
            cout << "Nenhum medico cadastrado.\n";
            return;
        }

        No* atual = inicio;
        while (atual != nullptr) {
            cout << atual->nome << "\n";
            atual = atual->prox;
        }
    }

    bool temMedico() const {
        return inicio != nullptr;
    }

    ~ListaMedicos() {
        while (temMedico()) chamarMedico();
    }
};


// R4 - RELATORIO DE ATENDIMENTOS
// Imprime o historico sem destruir os dados da pilha.
void imprimirHistorico(PilhaHistorico& hist) {
    cout << "\n=== RELATORIO DE ATENDIMENTOS ===\n";

    if (hist.isEmpty()) {
        cout << "(nenhum atendimento registrado)\n";
        return;
    }

    PilhaHistorico auxiliar;

    cout << "Atendimentos (mais recente ao mais antigo):\n";

    while (!hist.isEmpty()) {
        string atendimento = hist.pop();
        cout << "- " << atendimento << "\n";
        auxiliar.push(atendimento);
    }

    // Devolve os registros para a pilha original.
    while (!auxiliar.isEmpty()) {
        hist.push(auxiliar.pop());
    }
}

int main() {
    cout << "============================================\n";
    cout << "    SISTEMA DE ATENDIMENTO HOSPITALAR\n";
    cout << "============================================\n";

    FilaPacientes fila;
    PilhaHistorico historico;
    ListaMedicos medicos;

    // R3 - Cadastro dos medicos
    cout << "\n--- Cadastro de medicos ---\n";
    medicos.adicionarMedico("Dra. Ana Lima");
    medicos.adicionarMedico("Dr. Bruno Costa");
    medicos.adicionarMedico("Dra. Carla Ramos");
    cout << "Medicos disponiveis:\n";
    medicos.percorrer();

    // R1 - Chegada dos pacientes
    cout << "\n--- Pacientes chegando ---\n";
    fila.enqueue("Eduardo (urgencia=3)", 3);
    fila.enqueue("Fernanda (urgencia=1)", 1);
    fila.enqueue("Gabriel (urgencia=2)", 2);
    fila.enqueue("Helena (urgencia=1)", 1);

    cout << "Proximo paciente: " << fila.frente_peek() << "\n";
    cout << "Total na fila: " << fila.tamanho() << "\n";

    // Simulacao dos atendimentos
    cout << "\n--- Simulacao de atendimentos ---\n";

    int numero = 1;

    while (!fila.isEmpty() && medicos.temMedico()) {
        string paciente = fila.dequeue();
        string medico = medicos.chamarMedico();

        cout << "[" << numero++ << "] "
             << medico << " atende " << paciente << "\n";

        // R2 - Registra o atendimento na pilha
        historico.push(medico + " atende " + paciente);

        // O medico retorna ao final da lista
        medicos.adicionarMedico(medico);
    }

    // R4 - Relatorio preservando o historico
    string ultimoAntes = historico.peek();

    imprimirHistorico(historico);

    cout << "\n--- Verificacao da preservacao ---\n";
    cout << "Ultimo atendimento antes do relatorio: "
         << ultimoAntes << "\n";
    cout << "Ultimo atendimento depois do relatorio: "
         << historico.peek() << "\n";

    cout << "\n--- Medicos disponiveis ao final ---\n";
    cout << "Medicos disponiveis ao final:\n";
    medicos.percorrer();

    cout << "\n============================================\n";
    cout << "       FIM DO SISTEMA DE ATENDIMENTO\n";
    cout << "============================================\n";

    return 0;
}
