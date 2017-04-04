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
T�H�N HARJOITUSTY�H�N ON TOTEUTETTU AINOASTAAN PERUSTOIMINNOT, JOLLOIN VAALIVUOSIA TAI VAALLILIITTOJA EI K�SITELL�
KAIKKI LUOKAT ON JAETTU OMIKSI H/CPP TIEDOSTOIKSEEN LUKEMISEN HELPOTTAMISEKSI
*/

int main(int argc, char *argv[])
{
    //annetulle sy�tteelle muuttujia, komento-osalle ja kommennon sis�ll�lle
    //lippumuuttuja tuloksen laskemisesta ja ohjelman ajamisen lopettamisesta
    string komento;
    string kasky;
    bool lopeta = false;
    bool tulosLaskettu = false;
    //olioiden tallentamiseksi luodut vektorit
    vector<Puolue> puolueLista;
    vector<Ehdokas> ehdokasLista;
    vector<Vaalipiiri> vaalipiiriLista;
    
    //Otetaan sy�tett�,  kunne luetaan lopeta komento
    while (lopeta == false)
    {
        getline(cin, komento);
        istringstream iss(komento);
        iss>>kasky;
        if(kasky == "lisaaPuolue")
        {
            iss>>kasky;
            //tarkistetaan l�ytyyk� listalta jo kyseist� puoluetta. Jos ei, lis�t��n uusi puolue puoluelistaan
            if(!(cpp_utils::tarkistaKopiot(puolueLista, kasky.c_str())))
            {
            puolueLista.push_back(cpp_puolue::Puolue(kasky.c_str(),0));
              
            }
            //j�rjestet��n puolueet nimen mukaan
            sort(puolueLista.begin(), puolueLista.end(), Puolue::vertaa);
            
        }
        
        else if (kasky == "lisaaVaalipiiri")
        {   
            //mit� kohtaa sy�tett� luetaan
            int moneskoOsa = 0;
            //jos nimi tai vaalipiiri, jossa monta osaa
            int moniOsainen = 0;
            string vpNimi;
            string valimerkki;
            int edustajienLkm;
            
            while (iss>>kasky)
          {
              //tiedet��n monesko tietue menossa, ja ollaanko jo erotinmerkiss�
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
                //Edustajien ��nim��r�
                else if (moneskoOsa == 1)
                {
                    edustajienLkm = atoi(kasky.c_str());
                }
                //Koska merkki ei ollut erotinmerkki, kasvatetaan moniosaisuuden lukum��r��
                moniOsainen++;
                
              }
              //jos saavutettiin erotinmerkki, kasvatetaan tarkastetltavaa komentoa, ja nollataan sy�tteen pituuslasku
              else
              {
                  moneskoOsa++; 
                  moniOsainen = 0;
              }
          }
          
         //tarkastetaan onko kyseess� jo listalla oleva vaalipiiri
         if(!(cpp_utils::tarkistaKopiot(vaalipiiriLista, vpNimi.c_str())))
            {
              vaalipiiriLista.push_back(Vaalipiiri(vpNimi.c_str(), edustajienLkm, 0));
            }
            //mik�li vaalipiiri l�ytyy listalta, korvataan ainoastaan valittavien ehdokkaiden lkm
            else
            {
                cpp_utils::palautaListalta(vaalipiiriLista, vpNimi.c_str()).asetaLkm(edustajienLkm);
            }
            //j�rjestet��n vaalipiirit nimen mukaan
            sort(vaalipiiriLista.begin(), vaalipiiriLista.end(), Vaalipiiri::vertaaVp);
        }
        
        else if (kasky == "lisaaEhdokas")
        {
          /*otetaan talteen ehdokkaan nimi, puolue, 
            vaalipiiri ja ��nim��r�. 
            Poistetaan sy�tteest� /-merkit */
          string ehdokkaanNimi="";
          string ehdokkaanPuolue = "";
          string ehdokkaanVp = "";
          int ehdokkaanAanet=0;
          //mit� kohtaa sy�tett� luetaan
          int moneskoOsa = 0;
          //jos nimi tai vaalipiiri, jossa monta osaa
          int moniOsainen = 0;
          while (iss>>kasky)
          {
            //tiedet��n monesko tietue menossa

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
                //Talletetaan ehdokkaan ��net
                else if (moneskoOsa == 3)
                {
                    ehdokkaanAanet = atoi(kasky.c_str());
                }
                moniOsainen = moniOsainen + 1;
              }
              //erotinmerkiss� kasvateteaan osalaskuria ja nollataan usean osan muuttuja
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
        
            //j�rjestet��n ehdokkaat j�rjestykseen VP>Puolue>nimi
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaa);
        }
        
        else if (kasky == "laskeTulos")
        {
            //merkit��n tulosten laskeminen tehdyksi
            tulosLaskettu = true;
            
            //asetetaan ehdokkaat jarjestykseen puolue>aanet
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaAanet);
            //lasketaan puolueittan ��net ehdokkaille
            cpp_utils::laskePuolueenAanet(ehdokasLista, puolueLista, vaalipiiriLista);
            /*
            j�rjestet��n ehdokkaat vaalipiiri>vertailuluku j�rjestykseen,
            jotta voidaan suoraan valita listalta oikea m��r� ehdokkaita  
            */
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaVertailu);
            
            //muutetaan valittujen ehdokkaiden valintastatus
            for (unsigned int i = 0; i<vaalipiiriLista.size(); i++)
            {
                string vaalipiiri = vaalipiiriLista[i].palautaNimi();
                //otetaan vaalipiirist� valittavien ehdokkaiden m��r�, ja alustetaan apu-muuttuja joka tarkkailee valittujen m��r��
                int vaalipiirinEhdokkaat = vaalipiiriLista[i].palautaLkm();
                int apu = 1;
                for (unsigned int j = 0; j<ehdokasLista.size(); j++)
                {
                    //jos henkil�n vaalipiiri on oikea, ja vaalipiirist� ei ole viel� valittu oikeaa m��r�� ehdokkaita (aiemman sorttauksen j�lkeinen j�rjestys)
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
          //tulostetaan Puolueet: ja mik�li tulos on laskettu tulostetaan vain puolueet j�rjestyksess�
          cout<<"Puolueet:"<<endl;
          if(tulosLaskettu == false)
          {
            for(unsigned int i = 0; i < puolueLista.size(); i++){
                cout<<puolueLista[i].palautaNimi()<<endl;
            }
          }
          //mik�li tulos on laskettu, tulostetaan puolueiden valitut ehdokkaat
          else
          {
              cpp_utils::puolueTulostus(puolueLista, ehdokasLista);
          }
        }

        //Tulostetaan vaalipiirit
        else if (kasky == "vaalipiirit")
        {
            cout<< "Vaalipiirit:"<<endl;
            //j�rjestet��n ehdokkaat puolue>nimi
            sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaaNimi);
            cpp_utils::vpTulostus(vaalipiiriLista, ehdokasLista, tulosLaskettu);
        }        
        
        //Tulosteetaan ehdokkaat
        else if (kasky == "ehdokkaat")
        {
             //j�rjestet��n vp>puolue>nimi   
             sort(ehdokasLista.begin(), ehdokasLista.end(), Ehdokas::vertaa);             
             cout<< "Ehdokkaat:"<<endl;
             
             //k�yd��n kaikki ehdokkaat l�pi
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
                //muuten vain vaihdetaan rivi�
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
        //nollataan k�skymuuttuja
        
        kasky = "";        
    }
    return 0;
}
