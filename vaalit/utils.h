#ifndef UTILS
#define UTILS
#include <string>
#include <vector>
using namespace std;
//Yleisesti eri luokilla toteutettavia funktioita
namespace cpp_utils{
    
    //vaalipiirin tietojen tulostus
    template <typename T, typename Y>
    void vpTulostus(vector <T> &vpLista, vector <Y> &eLista, bool tulosLaskettu)
    {
        //jos ehdokkaita ei vielä ole asetettu, tulostetaan vain vaalipiirien nimet ja valittavat ehdokkaat
        if (eLista.size()==0)
        {
            for(unsigned int i = 0; i < vpLista.size(); i++){

                if(vpLista[i].palautaLkm() > 1){
                    cout << vpLista[i].palautaNimi()<< " (" << vpLista[i].palautaLkm() <<" edustajaa)"<<endl;
                }
                else{
                    cout <<  vpLista[i].palautaNimi()<< " (" << vpLista[i].palautaLkm() <<" edustaja)"<<endl;
                } 
            }

        }
        //jos ehdokkaat on asetettu, tulostetaan vaalipiirin nimi, valittavat ehdokkaat ja kunkin vaalipiirin ehdokkaat
        else
        {
            for(unsigned int i = 0; i < vpLista.size(); i++)
            {
                //mikäli valittavia on enemmän kuin yksi, tulostetaan monikko
                if(vpLista[i].palautaLkm() > 1)
                {
                    cout << vpLista[i].palautaNimi()<< " (" << vpLista[i].palautaLkm() <<" edustajaa)"<<endl;
                }
                //jos valittavia vain yksi, tulostetaan yksikkö
                else
                {
                    cout <<  vpLista[i].palautaNimi()<< " (" << vpLista[i].palautaLkm() <<" edustaja)"<<endl;
                } 
                //tulostetaan vaalipiirien ehdokkaat
                for(unsigned int j = 0; j < eLista.size(); j++)
                {
                    if (vpLista[i].palautaNimi() == eLista[j].palautaVaalipiiri() && eLista[j].palautaValittu() == true) 
                    {
                        cout<<"  "<<eLista[j].palautaNimi()<<" "<<eLista[j].palautaPuolue()<< " "<< eLista[j].palauta_Aanet()<<endl;
                    }                
                }            
            }
        }
    }
    
    //puolueiden tulostusfunktio
    template <typename T, typename Y>
    void puolueTulostus(vector <T> &puolue, vector <Y> &valitutEhdokkaat)
    {
        //lasketaan puolueen hyväksytyt ehdokkaat
        for (unsigned int i=0; i<puolue.size(); i++)
        {
            int apu = 0;
            string tarkasteltava = puolue[i].palautaNimi();
            for(unsigned int j = 0; j<valitutEhdokkaat.size(); j++)
            {
                //mikäli puolueelta on valittu ehdokas, kasvatetaan apulaskuria
                if (valitutEhdokkaat[j].palautaPuolue() == tarkasteltava && valitutEhdokkaat[j].palautaValittu() == true )
                {
                    apu++;
                }                               
            }
            //tulostetaan käsitelttävä puolue, ja sen ehdokasmäärä
            cout<<tarkasteltava<<" ("<<apu<<")"<<endl;
            
            //tulostetaan valittujen ehdokkaiden tiedot oman puoleensa alle
            for (unsigned int k = 0; k<valitutEhdokkaat.size(); k++)
            {                
                if (valitutEhdokkaat[k].palautaPuolue() == tarkasteltava && valitutEhdokkaat[k].palautaValittu() == true )
                {
                    cout<<"  "<<valitutEhdokkaat[k].palautaNimi()<<" "<<valitutEhdokkaat[k].palautaVaalipiiri()<<" "<<valitutEhdokkaat[k].palauta_Aanet()<<endl;
                }                
            }
        }
    }
    
    //tarkistetaan löytyykö listalta alkiota, jolla on haluttu nimi
    template<typename T>
    bool tarkistaKopiot(std::vector<T> &lista, string a){
        bool loytyyListalta = false;
        //mikäli listalla on alkioita tarkastetaan kunkin listan olion nimi
        if (lista.size() > 0){
            for (unsigned int i = 0; i<lista.size(); i++)
            {
                //jos listalta löytyy olio, jonka nimi täsmää palautetaan true
                if (lista[i].palautaNimi() == a)
                {                    
                    loytyyListalta = true;
                }                
            }
        }
        //muuten palautetaan false
        return loytyyListalta;
    }
    
    //palautetaan olio, jolla on haluttu nimi
    template<typename T>
    T palautaListalta(std::vector<T> &lista, string a){
        //mikäli lista ei ole tyhjä
        if (lista.size() > 0){
            for (unsigned int i = 0; i<lista.size(); i++)
            {
                //jos täsmäävä oli löytyy, palautetaan viite siihen
                if (lista[i].palautaNimi() == a)
                {                    
                    return lista[i];
                }                
            }
        }
        //muuten palautetaan listan ensimmäinen alkio (virheentarkistus jota ei tarvinnutkaan toteuttaa)
        return lista[0];
    }
    
    //lasketaan ehdokkaiden vertailuluvut
    template <typename T, typename Y, typename R>        
    void laskePuolueenAanet(vector<T> &ehdokasLista, vector<Y> &puolueLista, vector<R> &Vpiiri)
    {
        //vaalipiiri kerrallaan, lasketaan puolueiden saamat äänet
        for (unsigned int i=0; i<Vpiiri.size(); i++)
        {
            string vp = Vpiiri[i].palautaNimi();
            for (unsigned int j = 0; j<puolueLista.size(); j++)
            {
                //lasketaan ensin jokaisen vaalipiirin puoluekohtaiset äänet
                double aanetYhteensa = 0;
                string kasiteltavaPuolue = puolueLista[j].palautaNimi();
                for (unsigned int k = 0; k<ehdokasLista.size(); k++)
                {
                    //mikäli ehdokas on oikeasta puolueesta ja oikeasta vaalipiiristä, lasketaan hänen äänet
                    if (ehdokasLista[k].palautaPuolue() == kasiteltavaPuolue && ehdokasLista[k].palautaVaalipiiri() == vp)
                    {
                        aanetYhteensa += ehdokasLista[k].palauta_Aanet();                        
                    }                 
                }
                //kun äänet on laskettu, lasketaan ehdokkaiden vertailuluvut (äänet/jarjestysLuku)
                double jarjestysLuku = 1;
                for (unsigned int l = 0; l<ehdokasLista.size(); l++)
                {
                    //jos ehdokas on oikeasta puolueesta ja vaalipiiristä, lasketaan ehdokkaan vertailuluku
                    if (ehdokasLista[l].palautaPuolue() == kasiteltavaPuolue && ehdokasLista[l].palautaVaalipiiri() == vp)  
                    {                      
                      ehdokasLista[l].asetaVertailu(aanetYhteensa/jarjestysLuku);
                      jarjestysLuku++;
                    }
                }
            }
        }        
    }
}    
#endif
