#include <string>
#include <vector>
#include "puolue.h"
using namespace std;
//puolueluokan toteutus
namespace cpp_puolue
{
    string lyhenne;
    int paikkoja;
    double vertailu;
    
    Puolue::Puolue(string nimi, double verta)

    {
        lyhenne = nimi;
        vertailu = verta;
    }
    Puolue::~Puolue()
    {
        
    }
    //setterit ja getterit
    void Puolue::asetaNimi(string syote)
    {
        lyhenne = syote;
    }
    string Puolue::palautaNimi()
    {
        return lyhenne;
    }    
    void Puolue::asetaVertailu (double a)
    {
        vertailu = a;
    }    
    double Puolue::palautaVertailu()
    {
        return vertailu;
    }
    void Puolue::asetaPaikat(int syote)
    {
        paikkoja = syote;
    }    
    int Puolue::palautaPaikat()
    {
        return paikkoja;
    }
    
    //sort metodia varten tarvittava vertailumetodi
    bool Puolue::vertaa(const Puolue &a, const Puolue &b)
    {
        return (a.lyhenne < b.lyhenne);
    }
}