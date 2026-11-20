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

        if (frente == nullptr) {
            tras = nullptr;
        }

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
        while (!isEmpty()) {
            dequeue();
        }
    }
};

int main() {
    FilaPacientes fila;

    cout << "=== R1 - FILA DE PACIENTES ===\n";

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

    cout << "\nTotal restante: " << fila.tamanho() << "\n";

    return 0;
}
