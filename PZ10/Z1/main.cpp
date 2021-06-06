#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;


template<typename Tip>
class Grana;

template<typename Tip>
class Cvor;

template<typename Tip>
class GranaIterator;


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
class MatricaGraf: public UsmjereniGraf<Tip>
{
    struct PodaciGrane
    {
        Tip oznaka;
        float tezina;
        bool postoji;
    };
    std::vector<std::vector<PodaciGrane>> matrica;
    std::vector<Tip> oznakeCvorova;
public:
    MatricaGraf(int brojCvorova): UsmjereniGraf<Tip>(brojCvorova)
    {
        postaviBrojCvorova(brojCvorova);
    }
    int dajBrojCvorova() const override
    {
        return matrica.size();
    }
    void postaviBrojCvorova(int brojCvorova) override
    {
        if(brojCvorova<matrica.size())
            throw "Greska!";
        PodaciGrane nepostojeca;
        nepostojeca.postoji=false;
        for(int i=0; i<matrica.size(); i++)
        {
            matrica[i].resize(brojCvorova, nepostojeca);
        }
        std::vector<PodaciGrane> prazanRed(brojCvorova, nepostojeca);
        matrica.resize(brojCvorova, prazanRed);
        oznakeCvorova.resize(brojCvorova);
        
        
    }
    void dodajGranu(int polazni, int dolazni, float tezina) override
    {
        PodaciGrane g;
        g.tezina=tezina;
        g.postoji=true;
        matrica[polazni][dolazni]=g;
    }
    void obrisiGranu(int polazni, int dolazni) override
    {
        matrica[polazni][dolazni].postoji=false;
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina) override
    {
        matrica[polazni][dolazni].tezina=tezina;
    }
    float dajTezinuGrane(int polazni, int dolazni) override
    {
        return matrica[polazni][dolazni].tezina;
    }
    bool postojiGrana(int polazni, int dolazni) override
    {
        return matrica[polazni][dolazni].postoji;
    }
    void postaviOznakuCvora(int cvor, Tip oznaka) override
    {
        oznakeCvorova[cvor]=oznaka;
    }
    Tip dajOznakuCvora(int cvor) const override
    {
        return oznakeCvorova[cvor];
    }
    void postaviOznakuGrane(int polazni, int dolazni, Tip oznaka) override
    {
        matrica[polazni][dolazni].oznaka=oznaka;
    }
    Tip dajOznakuGrane(int polazni, int dolazni) const override
    {
        return matrica[polazni][dolazni].oznaka;    
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
        for(int i=polazni; i<matrica.size(); i++)
        {
            for(int j=0; j<matrica.size(); j++)
            {
                if(i==polazni && j<=dolazni) continue;
                if(matrica[i][j].postoji)
                {
                    return GranaIterator<Tip>(this, i, j);
                }
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
    
    UsmjereniGraf<bool> *graf=new MatricaGraf<bool>(5);
    graf->dodajGranu(0, 1, 5);
    graf->dodajGranu(0, 2, 5);
    graf->dodajGranu(0, 3, 5);
    graf->dodajGranu(3, 4, 5);
    std::vector<Cvor<bool>>a;
    return 0;
}
