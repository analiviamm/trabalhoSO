#include <iostream>
using namespace std;

class Processo
{
private:
    int id, burst, totalIO, burstinicial, totalIOinicial, quantumatual;

    bool mudar_de_fila = false;

public:
    Processo(int id = 0, int burst = 0, int totalI0 = 0) : id(id), burst(burst), totalIO(totalI0), quantumatual(0),
                                                           mudar_de_fila(false) {}
    void set_id(int id)
    {
        this->id = id;
    }
    void set_burst(int burst)
    {
        this->burst = burst;
    }
    void set_totalIO(int totalIO)
    {
        this->totalIO = totalIO;
    }
    void set_burstinicial(int burstinicial)
    {
        this->burstinicial = burstinicial;
    }
    void set_totalIOinicial(int totalIOinicial)
    {
        this->totalIOinicial = totalIOinicial;
    }
    void set_quantumatual(int quantumatual)
    {
        this->quantumatual = quantumatual;
    }
    void set_mudar_de_fila(bool mudar_de_fila)
    {
        this->mudar_de_fila = mudar_de_fila;
    }

    int get_id()
    {
        return this->id;
    }
    int get_burst()
    {
        return this->burst;
    }
    int get_totalIO()
    {
        return this->totalIO;
    }
    int get_burstinicial()
    {
        return this->burstinicial;
    }
    int get_totalIOinicial()
    {
        return this->totalIOinicial;
    }
    int get_quantumatual()
    {
        return this->quantumatual;
    }
    bool get_mudar_de_fila()
    {
        return this->mudar_de_fila;
    }
};
