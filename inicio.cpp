#include <iostream>
#include "Escalonador.cpp"

using namespace std;

int totalProcessos, burstCPU, totalIO;

void gantt(int tempo_escalonador, vector<pair<int, pair<int, int>>> historico)
{
    for (int i = 0; i < historico.size(); i++)
    {
        if (i)
        {
            if (historico[i].second.first != historico[i - 1].second.second)
            {
                cout << "Nenhum Processo: " << historico[i - 1].second.second << " " << historico[i].second.first << "\n";
            }
        }
        else
        {
            if (historico[i].second.first != 0)
            {
                cout << "Nenhum Processo: " << 0 << " " << historico[i].second.first << "\n";
            }
        }
        cout << "P" << historico[i].first << ": " << historico[i].second.first << " " << historico[i].second.second << "\n";
    }
    if (historico.size() && historico.back().second.second != tempo_escalonador)
    {
        cout << "Nenhum Processo: " << historico.back().second.second << " " << tempo_escalonador << "\n";
    }
    cout << "\n";
}

int main()
{
    Escalonador e;
    cout << "Insira o numero de processos: ";
    cin >> totalProcessos;
    for (int i = 0; i < totalProcessos; i++)
    {
        cout << "Insira o tempo de burst e o numero de processos I/O: ";
        cin >> burstCPU >> totalIO;
        Processo p = Processo(i, burstCPU, totalIO);
        p.set_burstinicial(burstCPU);
        p.set_totalIOinicial(20);
        e.adicionar(p);
        cout << "Processo adicionado\n";
    }

    int tempo = 0;
    while (e.checar_filas())
    {
        tempo = e.escalonar_processo();
        if (tempo == -1)
            tempo = e.executarIO();
        e.set_tempo_atual(e.get_tempo_atual() + tempo);
    }
    cout << "Historico da CPU: \n";
    gantt(e.get_tempo_atual(), e.CPU);

    return 0;
}