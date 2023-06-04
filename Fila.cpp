#include <queue>
#include <iostream>
#include "Processo.cpp"

using namespace std;

class Fila
{
private:
    int quantum;
    int id_fila; // se for 0, é round robin, se for 1, é fcfs
    queue<Processo> fila_de_processo;

public:
    Fila(int quantum) : quantum(quantum), id_fila(0) {}
    Fila() : quantum(0), id_fila(1) {}

    void set_quantum(int quantum)
    {
        this->quantum = quantum;
    }
    int get_quantum()
    {
        return this->quantum;
    }
    int get_tamanho_fila()
    {
        return this->fila_de_processo.size();
    }
    void adicionar(Processo novo)
    {
        this->fila_de_processo.push(novo);
    }
    void remover()
    {
        this->fila_de_processo.pop();
    }
    Processo processo_atual()
    {
        Processo atual = this->fila_de_processo.front();
        return atual;
    }

    bool empty() const {
        return fila_de_processo.empty();
    }

    int executar_processoTLE(int tle)
    {
        int burst = fila_de_processo.front().get_burst();
        fila_de_processo.front().set_burst(max(0, burst - tle));

        return min(burst, tle);
    }

    int executar_processo(int limiteIO)
    {
        if (fila_de_processo.empty())
            return 0;

        int tempo_percorrido;

        if (id_fila == 0)
        {
            int tempo_limite = fila_de_processo.front().get_quantumatual();

            if (limiteIO)
            {
                tempo_limite = min(tempo_limite, limiteIO);
            }

            tempo_percorrido = executar_processoTLE(tempo_limite);

            fila_de_processo.front().set_quantumatual(max(0, fila_de_processo.front().get_quantumatual() - tempo_percorrido));

            // se o processo nao terminou e o quantum sim, tem que mudar de fila
            if (fila_de_processo.front().get_burst() != 0 && fila_de_processo.front().get_quantumatual() == 0)
            {
                fila_de_processo.front().set_mudar_de_fila(true);
            }
            else
            {
                fila_de_processo.front().set_mudar_de_fila(false);
            }

            return tempo_percorrido;
        }
        // quando nao for round robin:
        fila_de_processo.front().set_mudar_de_fila(false);

        if (limiteIO)
            return executar_processoTLE(limiteIO);

        // o tempo vai ser igual ao burst atual
        tempo_percorrido = fila_de_processo.front().get_burst();
        fila_de_processo.front().set_burst(0);
        return tempo_percorrido;
    }

};

class FilaFCFS : public Fila
{
};

class FilaRR : public Fila
{
};