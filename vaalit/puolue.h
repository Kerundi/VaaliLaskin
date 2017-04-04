#ifndef PUOLUE
#define PUOLUE
#include <string>
#include <vector>
//puolueluoka esittely
namespace cpp_puolue
{
    class Puolue{
        std::string lyhenne;
        int paikkoja;
        double vertailu;
        
        public:        
        Puolue(std::string nimi, double vertaa);
        ~Puolue();
        
        void asetaNimi(std::string syote);
        std::string palautaNimi();
        void asetaPaikat(int syote);
        int palautaPaikat();
        void asetaVertailu (double a);    
        double palautaVertailu();
        static bool vertaa(const Puolue &a, const Puolue &b);  
    };      
}
#endif