#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include "puolue.h"
#include "ehdokas.h"
#include "vaalipiiri.h"
#include "utils.h"

using namespace std;
using namespace cpp_utils;
using namespace cpp_puolue;
using namespace cpp_ehdokas;
using namespace cpp_vaalipiiri;

/*
TÄHÄN HARJOITUSTYÖHÖN ON TOTEUTETTU AINOASTAAN PERUSTOIMINNOT, JOLLOIN VAALIVUOSIA TAI VAALLILIITTOJA EI KÄSITELLÄ
KAIKKI LUOKAT ON JAETTU OMIKSI H/CPP TIEDOSTOIKSEEN LUKEMISEN HELPOTTAMISEKSI
*/

int main(int argc, char *argv[])
{
    //annetulle syötteelle muuttujia, komento-osalle ja kommennon sisällölle
    //lippumuuttuja tuloksen laskemisesta ja ohjelman ajamisen lopettamisesta
    string komento;
    string kasky;
    bool lopeta = false;
    bool tulosLaskettu = false;
    //olioiden tallentamiseksi luodut vektorit
    vector<Puolue> puolueLista;
    vector<Ehdokas> ehdokasLista;
    vector<Vaalipiiri> vaalipiiriLista;
    
    //Otetaan syötettä,  kunne luetaan lopeta komento
    while (lopeta == false)
    {
        getline(cin, komento);
        istringstream iss(komento);
        iss>>kasky;
        if(kasky == "lisaaPuolue")
        {
            iss>>kasky;
            //tarkistetaan löytyykö listalta jo kyseistä puoluetta. Jos ei, lisätään uusi puolue puoluelistaan
            if(!(cpp_utils::tarkistaKopiot(puolueLista, kasky.c_str())))
            {
            puolueLista.push_back(cpp_puolue::Puolue(kasky.c_str(),0));
              
            }
            //järjestetään puolueet nimen mukaan
            sort(puolueLista.begin(), puolueLista.end(), Puolue::vertaa);
            
        }
        
        else if (kasky == "lisaaVaalipiiri")
        {   
            //mitä kohtaa syötettä luetaan
            int moneskoOsa = 0;
            //jos nimi tai vaalipiiri, jossa monta osaa
            int moniOsainen = 0;
            string vpNimi;
            string valimerkki;
            int edustajienLkm;
            
            while (iss>>kasky)
          {
              //tiedetään monesko tietue menossa, ja ollaanko jo erotinmerkissä
              if (kasky != "/")
              {
                //nimi
                if (moneskoOsa == 0)
                {
                    if (moniOsainen == 0)
                    {
                        vpNimi += kasky;
                    }
                    //Otetaan kaikki nimen osat talteen, ja asetetaan ne vpNimi-muuttujaan
                    else
                    {
                         vpNimi = vpNimi + " " + kasky;
                    }
                }
                //Edustajien äänimäärä
                else if (moneskoOsa == 1)
                {
                    edustajienLkm = atoi(kasky.c_str());
                }
                //Koska merkki ei ollut erotinmerkki, kasvatetaan moniosaisuuden lukumäärää
                moniOsainen++;
                
              }
              //jos saavutettiin erotinmerkki, kasvatetaan tarkastetltavaa komentoa, ja nollataan syötteen pituuslasku
              else
              {
                  moneskoOsa++; 
                  moniOsainen = 0;
              }
          }
          
         //tarkastetaan onko kyseessä jo listalla oleva vaalipiiri
         if(!(cpp_utils::tarkistaKopiot(vaalipiiriLista, vpNimi.c_str())))
            {
              vaalipiiriLista.push_back(Vaalipiiri(vpNimi.c_str(), edustajienLkm, 0));
            }
            //mikäli vaalipiiri löytyy listalta, korvataan ainoastaan valittavien ehdokkaiden lkm
            else
            {
                cpp_utils::palautaListalta(vaalipiiriLista, vpNimi.c_str()).asetaLkm(edustajienLkm);
            }
            //järjestetään vaalipiirit nimen mukaan
            sort(vaalipiiriLista.begin(), vaalipiiriLista.end(), Vaalipiiri::vertaaVp);
        }
        
        else if (kasky == "lisaaEhdokas")
        {
          /*otetaan talteen ehdokkaan nimi, puolue, 
            vaalipiiri ja äänimäärä. 
            Poistetaan syötteestä /-merkit */
          string ehdokkaanNimi="";
          string ehdokkaanPuolue = "";
          string ehdokkaanVp = "";
          int ehdokkaanAanet=0;
          //mitä kohtaa syötettä luetaan
          int moneskoOsa = 0;
          //jos nimi tai vaalipiiri, jossa monta osaa
          int moniOsainen = 0;
          while (iss>>kasky)
          {
            //tiedetään monesko tietue menossa

            if (kasky != "/")
            {
                //talletetaan ehdokkaan nimi
                if (moneskoOsa == 0)
                {
                    if (moniOsainen == 0)
                    {
                        ehdokkaanNimi += kasky;
                    }
                    else
                    {
                         ehdokkaanNimi = ehdokkaanNimi + " " + kasky;
                    }
                }
                //talletetaan puolue
                else if (moneskoOsa == 1)
                {
                    ehdokkaanPuolue = kasky;
                }
                //talletetaan koko vaalipiirin nimi
                else if (moneskoOsa == 2)
                {
                    if (moniOsainen == 0)
                    {
                        ehdokkaanVp += kasky;
                    }
                    else
                    {
                         ehdokkaanVp = ehdokkaanVp +" " + kasky;
                    }
                }
                //Talletetaan ehdokkaan äänet
                else if (moneskoOsa == 3)
                {
                    ehdokkaanAanet = atoi(kasky.c_str());
                }
                moniOsainen = moniOsainen + 1;
              }
              //erotinmerkissä kasvateteaan osalaskuria ja nollataan usean osan muuttuja
              else if (kasky == "/")
              {
                  moneskoOsa = moneskoOsa + 1;
                  moniOsainen = 0;
              }
              kasky = "";              
          }
          
            //luodaan saaduilla tiedoilla uusi ehdokas
            ehdokasLista.push_back(Ehdokas(ehdokkaanNimi,ehdokkaanPuolue, 
                         ehdokkaanVp,ehdokkaanAanet, false, 0));
        
            //järjestetään ehdokkaat järjestykseen VP>Puolue>nimi
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaa);
        }
        
        else if (kasky == "laskeTulos")
        {
            //merkitään tulosten laskeminen tehdyksi
            tulosLaskettu = true;
            
            //asetetaan ehdokkaat jarjestykseen puolue>aanet
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaAanet);
            //lasketaan puolueittan äänet ehdokkaille
            cpp_utils::laskePuolueenAanet(ehdokasLista, puolueLista, vaalipiiriLista);
            /*
            järjestetään ehdokkaat vaalipiiri>vertailuluku järjestykseen,
            jotta voidaan suoraan valita listalta oikea määrä ehdokkaita  
            */
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaVertailu);
            
            //muutetaan valittujen ehdokkaiden valintastatus
            for (unsigned int i = 0; i<vaalipiiriLista.size(); i++)
            {
                string vaalipiiri = vaalipiiriLista[i].palautaNimi();
                //otetaan vaalipiiristä valittavien ehdokkaiden määrä, ja alustetaan apu-muuttuja joka tarkkailee valittujen määrää
                int vaalipiirinEhdokkaat = vaalipiiriLista[i].palautaLkm();
                int apu = 1;
                for (unsigned int j = 0; j<ehdokasLista.size(); j++)
                {
                    //jos henkilön vaalipiiri on oikea, ja vaalipiiristä ei ole vielä valittu oikeaa määrää ehdokkaita (aiemman sorttauksen jälkeinen järjestys)
                    if (ehdokasLista[j].palautaVaalipiiri() == vaalipiiri && apu<=vaalipiirinEhdokkaat)
                    {
                        ehdokasLista[j].asetaValittu(true);
                        apu++;
                    }                                    
                }                
            }
        }
        
        //tulosteaan puolueet
        else if (kasky == "puolueet")
        {
          //tulostetaan Puolueet: ja mikäli tulos on laskettu tulostetaan vain puolueet järjestyksessä
          cout<<"Puolueet:"<<endl;
          if(tulosLaskettu == false)
          {
            for(unsigned int i = 0; i < puolueLista.size(); i++){
                cout<<puolueLista[i].palautaNimi()<<endl;
            }
          }
          //mikäli tulos on laskettu, tulostetaan puolueiden valitut ehdokkaat
          else
          {
              cpp_utils::puolueTulostus(puolueLista, ehdokasLista);
          }
        }

        //Tulostetaan vaalipiirit
        else if (kasky == "vaalipiirit")
        {
            cout<< "Vaalipiirit:"<<endl;
            //järjestetään ehdokkaat puolue>nimi
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaNimi);
            cpp_utils::vpTulostus(vaalipiiriLista, ehdokasLista, tulosLaskettu);
        }        
        
        //Tulosteetaan ehdokkaat
        else if (kasky == "ehdokkaat")
        {
             //järjestetään vp>puolue>nimi   
             sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaa);             
             cout<< "Ehdokkaat:"<<endl;
             
             //käydään kaikki ehdokkaat läpi
             for(unsigned int i =0; i < ehdokasLista.size(); i++)
             {
                //tulostaa listan alkiot
                cout<<ehdokasLista[i].palautaNimi()<<" "<< ehdokasLista[i].palautaPuolue()<<" "
                <<ehdokasLista[i].palautaVaalipiiri()<<" "<< ehdokasLista[i].palauta_Aanet();
                //jos tulos on laskettu ja ehdokas on valittu, tulostetaan se
                if(ehdokasLista[i].palautaValittu() == true && tulosLaskettu)
                {
                    cout<<" (valittu)"<<endl;
                }
                //muuten vain vaihdetaan riviä
                else
                {
                    cout<<endl;
                }                
            }            
        }
        
        else if (kasky == "lopeta")
        {
            lopeta = true;
        }
        //nollataan käskymuuttuja
        
        kasky = "";        
    }
    return 0;
}
