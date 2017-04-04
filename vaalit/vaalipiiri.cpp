#include <string>
#include <vector>
#include "vaalipiiri.h"
//vaalipiirin toteutus
using namespace std;
namespace cpp_vaalipiiri
{       
    string nimi;
    int lkm = 0;
    double vertailu;

    Vaalipiiri::Vaalipiiri(string syoteNimi, int syoteLkm, double vertailuLuku)
    {
       nimi = syoteNimi;
       lkm = syoteLkm;
       vertailu = vertailuLuku;
    }
    Vaalipiiri::~Vaalipiiri()
    {
        
    }
    //setterit ja getterit
    void Vaalipiiri::asetaNimi(string syote)
    {
        nimi = syote;
    }
    void Vaalipiiri::asetaLkm (int maara)
    {
        lkm = maara;
    }
    void Vaalipiiri::asetaVertailu(double syote)
    {
        vertailu = syote;
    }  
    double Vaalipiiri::palautaVertailu()
    {
        return vertailu;
    }    
    string Vaalipiiri::palautaNimi()
    {
        return nimi;
    }
    int Vaalipiiri::palautaLkm()
    {
        return lkm;
    }
    //sort() metodia varten tehty vertailu
    bool Vaalipiiri::vertaaVp(const Vaalipiiri &a, const Vaalipiiri &b)
    {
       return (a.nimi < b.nimi);        
    }    
}