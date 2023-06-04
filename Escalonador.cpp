#include <bits/stdc++.h>
#include "Fila.cpp"

using namespace std;
class Escalonador
{
private:
    vector<Fila> filas;
    Fila filaIO;
    int tempo_atual;
    Fila EscalonadorIO;

public:
    vector<pair<int, pair<int, int>>> CPU, IO;

    Escalonador() : tempo_atual(0), filas({Fila(10), Fila(15), Fila()}), EscalonadorIO(Fila()) {}

    void set_tempo_atual(int tempo_atual)
    {
        this->tempo_atual = tempo_atual;
    }

    int get_tempo_atual()
    {
        return tempo_atual;
    }

    void adicionar(Processo novo)
    {
        novo.set_quantumatual(filas[0].get_quantum());
        filas[0].adicionar(novo);
    }

    void colocar_na_fila(Processo atual)
    {
        atual.set_burst(atual.get_burstinicial());
        adicionar(atual);
        EscalonadorIO.remover();
    }

    void enviar_IO(int fila, Processo atual)
    {
        atual.set_burst(atual.get_totalIOinicial());
        atual.set_totalIO(atual.get_totalIO() - 1);
        EscalonadorIO.adicionar(atual);
    }

    int escalonar_processo()
    {
        for (int i = 0; i < 3; i++)
        {
            if (!filas[i].empty()) 
            {
                int limiteIO = 0;
                if (!EscalonadorIO.empty()) 
                {
                    limiteIO = EscalonadorIO.processo_atual().get_burst();
                }
                int tempo_percorrido = filas[i].executar_processo(limiteIO);

                Processo atual = filas[i].processo_atual();
                pair<int, int> tempos = make_pair(tempo_atual, tempo_atual + tempo_percorrido);
                pair<int, pair<int, int>> par = make_pair(atual.get_id(), tempos);
                CPU.push_back(par);

                executar_ultimaIO(tempo_percorrido);

                if (atual.get_mudar_de_fila())
                {
                    filas[i].remover();
                    atual.set_quantumatual(filas[i + 1].get_quantum());
                    filas[i + 1].adicionar(atual);
                }
                else if (atual.get_burst() == 0)
                {
                    filas[i].remover();

                    if (atual.get_totalIO())
                    {
                        enviar_IO(i, atual);
                    }
                }
                return tempo_percorrido;
            }
        }
        return -1;
    }

    int executarIO()
    {
        int tempo_percorrido = EscalonadorIO.executar_processo(0);

        if (tempo_percorrido == 0)
            return 0;

        Processo atual = EscalonadorIO.processo_atual();
        pair<int, int> tempos = make_pair(tempo_atual, tempo_atual + tempo_percorrido);
        pair<int, pair<int, int>> par = make_pair(atual.get_id(), tempos);
        IO.push_back(par);

        colocar_na_fila(atual);

        return tempo_percorrido;
    }

    void executar_ultimaIO(int limite)
    {
        while (limite > 0 && !EscalonadorIO.empty())
        {
            int tempo_percorrido = EscalonadorIO.executar_processoTLE(limite);
            Processo atual = EscalonadorIO.processo_atual();

            pair<int, int> tempos = make_pair(tempo_atual, tempo_atual + tempo_percorrido);
            pair<int, pair<int, int>> par = make_pair(atual.get_id(), tempos);
            IO.push_back(par);

            if (atual.get_burst() == 0)
                colocar_na_fila(atual);
            limite -= tempo_percorrido;
        }
    }

    bool checar_filas()
    {
        bool check = !EscalonadorIO.empty(); 

        for (int i = 0; i < 3; i++)
        {
            check = check || !filas[i].empty(); 
        }

        return check;
    }
};
