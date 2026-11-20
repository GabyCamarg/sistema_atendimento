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

int main() {
    cout << "=== R1 - FILA DE PACIENTES ===\n";

    FilaPacientes fila;
    fila.enqueue("Eduardo", 3);
    fila.enqueue("Fernanda", 1);
    fila.enqueue("Gabriel", 2);
    fila.enqueue("Helena", 1);

    cout << "Proximo paciente: " << fila.frente_peek() << "\n";
    cout << "Total na fila: " << fila.tamanho() << "\n";

    cout << "\nAtendimento dos pacientes:\n";
    while (!fila.isEmpty()) {
        cout << fila.dequeue() << "\n";
    }
    cout << "Total restante: " << fila.tamanho() << "\n";

    cout << "\n=== R2 - PILHA DE HISTORICO ===\n";

    PilhaHistorico historico;
    historico.push("Eduardo");
    historico.push("Fernanda");
    historico.push("Gabriel");

    cout << "Ultimo atendimento registrado: "
         << historico.peek() << "\n";

    cout << "\nHistorico (mais recente primeiro):\n";
    while (!historico.isEmpty()) {
        cout << historico.pop() << "\n";
    }


    cout << "\n=== R3 - LISTA ENCADEADA DE MEDICOS ===\n";

    ListaMedicos medicos;
    medicos.adicionarMedico("Dra. Ana");
    medicos.adicionarMedico("Dr. Bruno");
    medicos.adicionarMedico("Dra. Carla");

    cout << "Medicos cadastrados:\n";
    medicos.percorrer();

    cout << "Proximo medico chamado: "
         << medicos.chamarMedico() << "\n";

    cout << "Medicos restantes:\n";
    medicos.percorrer();

    cout << "Existe medico disponivel? "
         << (medicos.temMedico() ? "Sim" : "Nao") << "\n";

    return 0;
}