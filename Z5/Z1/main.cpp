#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <utility>
#include <iterator>
#include <stdexcept>

using namespace std;


template<typename Tip>
class Grana;

template<typename Tip>
class Cvor;

template<typename Tip>
class GranaIterator;


template<typename Tip1, typename Tip2>
class Mapa
{
public:
    Mapa() {}
    virtual ~Mapa(){}
    virtual Tip2& operator[](Tip1 kljuc)=0;
    virtual Tip2 operator[](Tip1 kljuc)const=0;
    virtual int brojElemenata()=0;
    virtual int brojElemenata()const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const Tip1& kljuc)=0;
};


template<typename Tip1, typename Tip2>
class HashMapaLan: public Mapa<Tip1, Tip2>
{
private:
    int max;
    int velicina;
    unsigned int(*pocNaFun)(Tip1, unsigned int)=nullptr;
    /*Koliziju rjesavamo pomocu metode ulancavanja, za koju nam od pomoci mogu biti liste.
    Kako svaki element ima kljuc i vrijednost, to ce biti lista parova.
    Liste parova mozemo drzati u vektoru.*/
    std::vector<std::list<std::pair<Tip1, Tip2>>>hashMapa;
public:
    HashMapaLan();
    //Destruktor nam ne treba, jer koristimo bibliotecne kontejnerske tipove koji imaju svoj destruktor
    //HashMapaLan(const HashMapaLan& m); Kopirajuci konstruktor nam ne treba, jer se pozivaju kopirajuci konstruktori koristenih bibliotevnih tipova.
    //HashMapaLan& operator=(const HashMapaLan& m); Ista stvar kao i za kopirajuci konstruktor, naravno ne dolazi do plitkog kopranja
    void definisiHashFunkciju(unsigned int (*fun)(Tip1, unsigned int));  
    Tip2& operator[](Tip1 kljuc) override;
    Tip2 operator[](Tip1 kljuc) const override;
    int brojElemenata() override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Tip1& kljuc) override;
    
};

template<typename Tip1, typename Tip2>
HashMapaLan<Tip1, Tip2>::HashMapaLan()
{
    velicina=0;
    max=10000;
    hashMapa=std::vector<std::list<std::pair<Tip1, Tip2>>>(10000, std::list<std::pair<Tip1, Tip2>>());
    
}

template<typename Tip1, typename Tip2>
void HashMapaLan<Tip1, Tip2>::definisiHashFunkciju(unsigned int (*fun)(Tip1, unsigned int))
{
    pocNaFun=fun;
}

template<typename Tip1, typename Tip2>
Tip2& HashMapaLan<Tip1, Tip2>::operator[](Tip1 kljuc)
{
    if(pocNaFun==nullptr) throw "Nije inicijalizirana hash funkcija!";
    int pocetniIndeks=pocNaFun(kljuc, hashMapa.size());
    typename std::list<std::pair<Tip1, Tip2>>::iterator it=hashMapa[pocetniIndeks].begin();
    while(it!=hashMapa[pocetniIndeks].end() && it->first<kljuc)
    {
        it++;
    }
    if(it!=hashMapa[pocetniIndeks].end() && it->first==kljuc)
    {   
        return it->second;
    }
    
    it=hashMapa[pocetniIndeks].insert(it, std::make_pair(kljuc, Tip2()));
    velicina++;
    return it->second;
}

template<typename Tip1, typename Tip2>
Tip2 HashMapaLan<Tip1, Tip2>::operator[](Tip1 kljuc) const
{
    if(pocNaFun==nullptr) throw "Nije inicijalizirana hash funkcija!";
    int pocetniIndeks=pocNaFun(kljuc, hashMapa.size());
    typename std::list<std::pair<Tip1, Tip2>>::const_iterator it=hashMapa[pocetniIndeks].begin();
    while(it!=hashMapa[pocetniIndeks].end() && it->first<kljuc)
    {
        it++;
    }
    if(it!=hashMapa[pocetniIndeks].end() && it->first==kljuc)
    {   
        return it->second;
    }
    return Tip2();
}

template<typename Tip1, typename Tip2>
int HashMapaLan<Tip1, Tip2>::brojElemenata()
{
    return velicina;
}

template<typename Tip1, typename Tip2>
int HashMapaLan<Tip1, Tip2>::brojElemenata() const
{
    return velicina;
}

template<typename Tip1, typename Tip2>
void HashMapaLan<Tip1, Tip2>::obrisi(const Tip1& kljuc)
{
    if(pocNaFun==nullptr) throw "Nije inicijalizirana hash funkcija!";
    int pocetniIndeks=pocNaFun(kljuc, hashMapa.size());
    typename std::list<std::pair<Tip1, Tip2>>::const_iterator it=hashMapa[pocetniIndeks].begin();
    while(it!=hashMapa[pocetniIndeks].end() && it->first<kljuc)
    {
        it++;
    }
    if(!(it!=hashMapa[pocetniIndeks].end() && it->first==kljuc))
    {   
        throw "Element se ne nalazi u HashMapi";
    }
    it=hashMapa[pocetniIndeks].erase(it);
    velicina--;
}

template<typename Tip1, typename Tip2>
void HashMapaLan<Tip1, Tip2>::obrisi()
{
    /*Kada imamo izraz oblika x::y gdje x zavisi od templejta, pisemo typename ispred*/
    for(int i=0; i<hashMapa.size(); i++)
    {
        hashMapa[i].clear();
    }
    velicina=0;
}


template<typename Tip>
class UsmjereniGraf
{
public:
    UsmjereniGraf(int brojCvorova) {}
    virtual ~UsmjereniGraf() {}
    virtual int dajBrojCvorova() const=0;
    virtual void postaviBrojCvorova(int brojCvorova)=0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina)=0;
    virtual void obrisiGranu(int polazni, int dolazni)=0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina)=0;
    virtual float dajTezinuGrane(int polazni, int dolazni)=0;
    virtual bool postojiGrana(int polazni, int dolazni)=0;
    virtual void postaviOznakuCvora(int cvor, Tip oznaka)=0;
    virtual Tip dajOznakuCvora(int cvor) const=0;
    virtual void postaviOznakuGrane(int polazni, int dolazni, Tip oznaka)=0;
    virtual Tip dajOznakuGrane(int polazni, int dolazni) const=0;
    Grana<Tip> dajGranu(int polazni, int dolazni)
    {
        return Grana<Tip>(this, polazni, dolazni);
    }
    Cvor<Tip> dajCvor(int cvor)
    {
        return Cvor<Tip>(this, cvor);
    }
    virtual GranaIterator<Tip> dajGranePocetak()=0;
    virtual GranaIterator<Tip> dajGraneKraj()=0;
    virtual GranaIterator<Tip>dajSljedecuGranu(int polazni, int dolazni)=0;
};


template<typename Tip>
class Grana
{
    UsmjereniGraf<Tip>* graf;
    int polazni, dolazni;
public:
    Grana(UsmjereniGraf<Tip>* graf, int polazni, int dolazni): graf(graf), polazni(polazni),
    dolazni(dolazni) {}

    float dajTezinu() const
    {
        return graf->dajTezinuGrane(polazni, dolazni);
    }
    void postaviTezinu(float tezina)
    {
        graf->postaviTezinuGrane(polazni, dolazni, tezina);
    }
    Tip dajOznaku() const
    {
        return graf->dajOznakuGrane(polazni, dolazni);
    }
    void postaviOznaku(Tip oznaka)
    {
        graf->postaviOznakuGrane(polazni, dolazni, oznaka);
    }
    Cvor<Tip> dajPolazniCvor() const
    {
        return graf->dajCvor(polazni);
    }
    Cvor<Tip> dajDolazniCvor() const
    {
        return graf->dajCvor(dolazni);
    }
};




template<typename Tip>
class Cvor
{
        UsmjereniGraf<Tip>* graf;
        int redniBroj;
public: 
    Cvor(UsmjereniGraf<Tip>* graf, int redniBroj): graf(graf), redniBroj(redniBroj) {}
    Tip dajOznaku() const
    {
        return graf->dajOznakuCvora(redniBroj);
    }
    void postaviOznaku(Tip oznaka)
    {
        graf->postaviOznakuCvora(redniBroj, oznaka);
    }
    int dajRedniBroj() const
    {
        return redniBroj;
    }
};


template<typename Tip>
class GranaIterator
{
    UsmjereniGraf<Tip>* graf;
    int polazni, dolazni;
public:
    GranaIterator(UsmjereniGraf<Tip>* g, int polazni, int dolazni): graf(g), polazni(polazni), dolazni(dolazni) {}   
    Grana<Tip> operator*()
    {
        return Grana<Tip>(graf, polazni, dolazni);
    }
    bool operator==(const GranaIterator& iter) const
    {
        return (graf==iter.graf && polazni==iter.polazni && dolazni==iter.dolazni);
    }
    bool operator!=(const GranaIterator& iter) const
    {
        return !(*this==iter);
    }
    GranaIterator& operator++()
    {
        if(polazni==-1 && dolazni==-1)
        {
            throw "iterator iza kraja";
        }
        GranaIterator g=graf->dajSljedecuGranu(polazni, dolazni);
        polazni=g.polazni;
        dolazni=g.dolazni;
        return *this;
    }
    GranaIterator operator++(int)
    {
        GranaIterator tmp(*this);
        ++(*this);
        return tmp;
    }
    Cvor<Tip> dajPolazniCvor() const
    {
        return graf->dajCvor(polazni);
    }
    Cvor<Tip> dajDolazniCvor() const
    {
        return graf->dajCvor(dolazni);
    }
    double dajTezinu()
    {
        return graf->dajTezinuGrane();
    }
};

template<typename Tip>
class ListaGraf: public UsmjereniGraf<Tip>
{
    struct PodaciGrane
    {
        Tip oznaka;
        float tezina;
        int dolazni;
    };
    std::vector<std::list<PodaciGrane>> lista;
    std::vector<Tip> oznakeCvorova;
public:
    ListaGraf(int brojCvorova): UsmjereniGraf<Tip>(brojCvorova)
    {
        lista=std::vector<std::list<PodaciGrane>>(brojCvorova, std::list<PodaciGrane>());
        oznakeCvorova=std::vector<Tip>(brojCvorova);
    }
    int dajBrojCvorova() const override
    {
        return lista.size();
    }
    void postaviBrojCvorova(int brojCvorova) override
    {
        if(brojCvorova<lista.size()) throw "Greska!";
        lista.resize(brojCvorova);
        oznakeCvorova.resize(brojCvorova);
    }
    void dodajGranu(int polazni, int dolazni, float tezina) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw "Nemoguca grana";
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni<dolazni)
        {
            it++;
        }
        lista[polazni].insert(it, PodaciGrane{Tip(), tezina, dolazni});
    }
    void obrisiGranu(int polazni, int dolazni) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw "Nemoguca grana";
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni!=dolazni) it++;
        if(it==lista[polazni].end()) throw "Nemoguca grana";
        it=lista[polazni].erase(it);
        
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw "Nemoguca grana";
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni!=dolazni) it++;
        if(it==lista[polazni].end()) throw "Nemoguca grana";
        it->tezina=tezina;
          
    }
    float dajTezinuGrane(int polazni, int dolazni) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw "Nemoguca grana";
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni!=dolazni) it++;
        if(it==lista[polazni].end()) throw "Nema dolaznog";
        return it->tezina;
    }
    bool postojiGrana(int polazni, int dolazni) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) return false;
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end())
        {
            if(it->dolazni==dolazni) return true;
            it++;
        }
        return false;
    }
    void postaviOznakuCvora(int cvor, Tip oznaka) override
    {
        if(!(cvor>=0 && cvor<oznakeCvorova.size())) throw "Cvor ne postoji";
        oznakeCvorova[cvor]=oznaka;
    }
    Tip dajOznakuCvora(int cvor) const override
    {
        return oznakeCvorova[cvor];
    }
    void postaviOznakuGrane(int polazni, int dolazni, Tip oznaka) override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw "Nemoguca grana";
        typename std::list<PodaciGrane>::iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni!=dolazni) it++;
        if(it==lista[polazni].end()) throw "Nemoguca grana";
        it->oznaka=oznaka;
          
    }
    Tip dajOznakuGrane(int polazni, int dolazni) const override
    {
        if(!(polazni>=0 && polazni<lista.size() && dolazni>=0 && dolazni<lista.size())) throw std::domain_error("Nemoguca grana");
        typename std::list<PodaciGrane>::const_iterator it=lista[polazni].begin();
        while(it!=lista[polazni].end() && it->dolazni!=dolazni) it++;
        if(it==lista[polazni].end()) throw std::domain_error("Nemoguca grana");
        return it->oznaka;    
    }
    
    GranaIterator<Tip> dajGranePocetak() override
    {
        GranaIterator<Tip> it(this, 0, -1);
        return ++it;
    }
    GranaIterator<Tip> dajGraneKraj() override
    {
        GranaIterator<Tip> it(this, -1, -1);
        return it;
    }
    GranaIterator<Tip> dajSljedecuGranu(int polazni, int dolazni)  override
    {
        for(int i=polazni; i<lista.size(); i++)
        {
            auto it=lista[i].begin();
            for(int j=0; j<lista[i].size(); j++)
            {
                if(i==polazni && it->dolazni<=dolazni)
                {
                    it++; continue;
                }
                else
                {
                    return GranaIterator<Tip>(this, i, it->dolazni);
                }
                it++;
                
            }
        }
        return GranaIterator<Tip>(this, -1, -1);
    }
    
};


template<typename Tip>
void dfs(UsmjereniGraf<Tip>* graf, std::vector<Cvor<Tip>> &dfs_obilazak, Cvor<Tip> cvor)
{
    cvor.postaviOznaku(1);
    dfs_obilazak.push_back(cvor);
        for(GranaIterator<Tip> gr=graf->dajGranePocetak(); gr!=graf->dajGraneKraj(); gr++)
        {
            Cvor<Tip>dostupniCvor=gr.dajDolazniCvor();
            if(dostupniCvor.dajOznaku()!=1  && gr.dajPolazniCvor().dajRedniBroj()==cvor.dajRedniBroj()) dfs(graf, dfs_obilazak, dostupniCvor);
            
        }
}

template<typename Tip>
void bfs(UsmjereniGraf<Tip>* graf, std::vector<Cvor<Tip>> &bfs_obilazak, Cvor<Tip> pocetni_cvor)
{
    std::queue<Cvor<Tip>> red;
    pocetni_cvor.postaviOznaku(1);
    bfs_obilazak.push_back(pocetni_cvor);
    red.push(pocetni_cvor);
    while(!red.empty())
    {
        Cvor<Tip>cvor=red.front();
        red.pop();
        for(GranaIterator<Tip> gr=graf->dajGranePocetak(); gr!=graf->dajGraneKraj(); gr++)
        {
            Cvor<Tip>dostupniCvor=gr.dajDolazniCvor();
            if(dostupniCvor.dajOznaku()!=1 && gr.dajPolazniCvor().dajRedniBroj()==cvor.dajRedniBroj())
            {
                dostupniCvor.postaviOznaku(1);
                red.push(dostupniCvor);
                bfs_obilazak.push_back(dostupniCvor);
            }
        }
    }
}

int main() {
  UsmjereniGraf<bool> *g = new ListaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 2, 1.2);
    g->dodajGranu(1, 3, 0.1);
    g->dodajGranu(2, 4, 3.14);
    g->dodajGranu(2, 3, 2.73);
    g->dodajGranu(3, 5, 1);
    g->dodajGranu(5, 2, -5.0);
    std::vector<Cvor<bool> > bfs_obilazak;
    bfs(g, bfs_obilazak, g->dajCvor(0));
    for (int i = 0; i < bfs_obilazak.size(); i++)
      cout << bfs_obilazak[i].dajRedniBroj() << ",";
  delete g;
}
