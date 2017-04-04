#include <string>
#include <vector>
#include "ehdokas.h"
using namespace std;
//ehdokasluokan toteutus
namespace cpp_ehdokas 
{
        std::string nimi;
        std::string puolue;
        std::string vaalipiiri;
        double aanet;
        bool valittu = false;
        double vertailu;

        Ehdokas::Ehdokas(std::string Enimi, std::string Epuolue, 
                         std::string Evaalipiiri, int Eaanet, bool valinta, double verr)
        {
            nimi = Enimi;
            puolue = Epuolue;
            vaalipiiri = Evaalipiiri;
            aanet = Eaanet;
            valittu = valinta;
            vertailu  = verr;
        }
        Ehdokas::~Ehdokas()
        {
            
        }
        //setterit ja getterit
        void Ehdokas::asetaValittu(bool tulos)
        {
            valittu = tulos;
        }
        void Ehdokas::asetaNimi(std::string nimiSyote)
        {
            nimi = nimiSyote;            
        }
        void Ehdokas::asetaPuolue(std::string syote)
        {
            puolue = syote;
        }
        void Ehdokas::asetaVaalipiiri(std::string vp)
        {
            vaalipiiri = vp;
        }
        void Ehdokas::aseta_Aanet(double aanimaara)
        {
            aanet = aanimaara;
        }
        bool Ehdokas::palautaValittu()
        {
            return valittu;
        }        
        void Ehdokas::asetaVertailu(double vert)
        {
            vertailu = vert;
        }
        double Ehdokas::palautaVertailu()
        {
            return vertailu;
        }
        std::string Ehdokas::palautaNimi()
        {
            return nimi;
        }
        std::string Ehdokas::palautaPuolue()
        {
            return puolue;
        }
        std::string Ehdokas::palautaVaalipiiri()
        {
            return vaalipiiri;
        }
        double Ehdokas::palauta_Aanet()
        {
            return aanet;
        }
        
        //sort() funktiota varten tehdy vertailumetodit
        //vaalipiiri>puolue>nimi
        bool Ehdokas::vertaa(const Ehdokas &a, const Ehdokas &b)
        {  
            if (a.vaalipiiri != b.vaalipiiri)
            {
               return (a.vaalipiiri < b.vaalipiiri);
            }
            else if (a.puolue != b.puolue)
            {
               return (a.puolue < b.puolue);
            }
            else
            {
                return (a.nimi < b.nimi);
            }
        }
        //Puolue>ehdokkaan aanet
        bool Ehdokas::vertaaAanet(const Ehdokas &a, const Ehdokas &b)
        {
            if (a.puolue != b.puolue)
            {
                return a.puolue > b.puolue;
            }
           
            else
            {
                return a.aanet > b.aanet;
            }   
        } 
        //vaalipiiri>vertailuluku
        bool Ehdokas::vertaaVertailu(const Ehdokas &a, const Ehdokas &b)
        {
            if (a.vaalipiiri != b.vaalipiiri)
            {
            return a.vaalipiiri < b.vaalipiiri;
            }
            else
            {
            return a.vertailu > b.vertailu;
            }
        }        
        //puolue>nimi
        bool Ehdokas::vertaaNimi(const Ehdokas &a, const Ehdokas &b)
        {
            if(a.puolue != b.puolue)
            {
                return a.puolue<b.puolue;
            }
            else{
                return a.nimi<b.nimi;
            }
        }
}