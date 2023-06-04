#include <iostream>
#include "Escalonador.cpp"

using namespace std;

int totalProcessos, burstCPU, totalIO;

void gantt(int tempo_escalonador, vector<pair<int, pair<int, int>>> historico)
{
    vector<pair<string, int>> diagGantt;

    // preencher o diagrama de gantt com as tarefas e períodos vazios
    int lastEnd = 0;
    for (const auto& processo : historico)
    {
        int id = processo.first;
        int inicio = processo.second.first;
        int fim = processo.second.second;

        if (inicio > lastEnd)
        {
            diagGantt.push_back(make_pair("Nenhum Processo", lastEnd));
            diagGantt.push_back(make_pair("", inicio));
        }

        diagGantt.push_back(make_pair("P" + to_string(id), inicio));
        diagGantt.push_back(make_pair("[" + to_string(inicio) + "-" + to_string(fim) + "]", fim));

        lastEnd = fim;
    }

    // Adicionar a última parte do diagrama de Gantt se necessário
    if (lastEnd < tempo_escalonador)
    {
        diagGantt.push_back(make_pair("Nenhum Processo", lastEnd));
        diagGantt.push_back(make_pair("", tempo_escalonador));
    }

    // Exibir o diagrama de Gantt
    cout << "Diagrama de Gantt:\n";

    int i = 0;
    while (i < diagGantt.size())
    {
        string nome = diagGantt[i].first;
        int inicio = diagGantt[i].second;
        int fim = diagGantt[i + 1].second;

        cout << "+";
        for (int j = 0; j < fim - inicio; ++j)
        {
            cout << "-";
        }
        cout << "+\n";

        cout << "|" << nome;
        int padding = fim - inicio - nome.length();
        for (int j = 0; j < padding; ++j)
        {
            cout << " ";
        }
        cout << "|\n";

        cout << "|" << diagGantt[i + 1].first;
        padding = fim - inicio - diagGantt[i + 1].first.length();
        for (int j = 0; j < padding; ++j)
        {
            cout << " ";
        }
        cout << "|\n";

        ++i;
        ++i;
    }

    cout << "+";
    for (int j = 0; j < tempo_escalonador; ++j)
    {
        cout << "-";
    }
    cout << "+\n\n";
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

    gantt(e.get_tempo_atual(), e.CPU);

    return 0;
}