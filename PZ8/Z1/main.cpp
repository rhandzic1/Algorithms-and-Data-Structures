#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

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
struct Cvor
    {
        Cvor* lijevi;
        Cvor* desni;
        Cvor* roditelj;
        Tip1 kljuc;
        Tip2 vrijednost;
    };
template<typename Tip1, typename Tip2>
class BinStabloMapa: public Mapa<Tip1, Tip2>
{
private:
    int broj_elemanata;
    Cvor<Tip1, Tip2>* korijen;
    Cvor<Tip1, Tip2>* trazi(Cvor<Tip1, Tip2>* r, const Tip1& k);
    void brisi(Cvor<Tip1, Tip2>* r);
    bool brisiCvor(Cvor<Tip1, Tip2>* &r, const Tip1& k);
    void kopiraj(Cvor<Tip1, Tip2>* original, Cvor<Tip1, Tip2>* &kopija, Cvor<Tip1, Tip2>* roditelj);
public:
    ~BinStabloMapa();
    BinStabloMapa();
    Tip2& operator[](Tip1 kljuc) override;
    Tip2 operator[](Tip1 kljuc) const override;
    int brojElemenata() override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Tip1& kljuc) override;
    BinStabloMapa(const BinStabloMapa &r);
    BinStabloMapa& operator=(const BinStabloMapa &r);
};

template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1, Tip2>::kopiraj(Cvor<Tip1, Tip2>* original, Cvor<Tip1, Tip2>* &kopija, Cvor<Tip1, Tip2>* roditelj)
{
    if(original!=nullptr)
    {
        kopija=new Cvor<Tip1, Tip2>();
        kopija->kljuc=original->kljuc;
        kopija->vrijednost=original->vrijednost;
        kopija->roditelj=roditelj;
        kopiraj(original->lijevi, kopija->lijevi, kopija);
        kopiraj(original->desni, kopija->desni, kopija);
        
    }
}
template<typename Tip1, typename Tip2>
BinStabloMapa<Tip1, Tip2>::BinStabloMapa(const BinStabloMapa &r)
{
    broj_elemanata=r.broj_elemanata;
    kopiraj(r.korijen, korijen, nullptr);
}
template<typename Tip1, typename Tip2>
BinStabloMapa<Tip1, Tip2>& BinStabloMapa<Tip1, Tip2>::operator=(const BinStabloMapa &r)
{
    if(&r==this) return *this;
    this->obrisi();
    broj_elemanata=r.broj_elemanata;
    
    kopiraj(r.korijen, this->korijen, nullptr);
    return *this;
    
    
}
template<typename Tip1, typename Tip2>
bool BinStabloMapa<Tip1, Tip2>::brisiCvor(Cvor<Tip1, Tip2>* &r, const Tip1& k)
{
    Cvor<Tip1, Tip2> *p=r, *q=nullptr;
    Cvor<Tip1, Tip2> *tmp=nullptr, *pp=nullptr, *rp=nullptr;
    while(p!=nullptr && k!=p->kljuc)
    {
        q=p;
        if(k<p->kljuc)
        {
            p=p->lijevi;
        }
        else p=p->desni;
    }
    if(p==nullptr) return false;
    if(p->lijevi==nullptr) rp=p->desni;
    else if(p->desni==nullptr) rp=p->lijevi;
    else
    {
        pp=p;
        rp=p->lijevi;
        tmp=rp->desni;
        while(tmp!=nullptr)
        {
            pp=rp;
            rp=tmp;
            tmp=rp->desni;
        }
        if(pp!=p)
        {
            pp->desni=rp->lijevi;
            rp->lijevi=p->lijevi;
        }
        rp->desni=p->desni;
    }
    if(q==0) korijen=rp;
    else if(p==q->lijevi) q->lijevi=rp;
    else q->desni=rp;
    delete p;
    return true;
}
template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1, Tip2>::brisi(Cvor<Tip1, Tip2>* r)
{
    if(r)
    {
        brisi(r->lijevi);
        brisi(r->desni);
        delete r;
        r=nullptr;
    }
}
template<typename Tip1, typename Tip2>
Cvor<Tip1, Tip2>* BinStabloMapa<Tip1, Tip2>::trazi(Cvor<Tip1, Tip2>* r, const Tip1& k)
{
    Cvor<Tip1, Tip2>* pom=r;
    while(pom!=nullptr && pom->kljuc!=k)
    {
        if(k<pom->kljuc)
        {
            pom=pom->lijevi;
        }
        else
        pom=pom->desni;
    }
    return pom;
}

template<typename Tip1, typename Tip2>
BinStabloMapa<Tip1, Tip2>::~BinStabloMapa()
{
    brisi(korijen);
    broj_elemanata=0;
}

template<typename Tip1, typename Tip2>
BinStabloMapa<Tip1, Tip2>::BinStabloMapa()
{
    broj_elemanata=0;
    korijen=nullptr;
}

template<typename Tip1, typename Tip2>
Tip2& BinStabloMapa<Tip1, Tip2>::operator[](Tip1 kljuc)
{
    Cvor<Tip1, Tip2>* poc=trazi(korijen, kljuc);
    if(poc==nullptr)
    {
        Cvor<Tip1, Tip2>* temp=new Cvor<Tip1, Tip2>();
        temp->lijevi=nullptr; temp->desni=nullptr;
        temp->roditelj=nullptr; temp->kljuc=kljuc;
        temp->vrijednost=Tip2();
        Cvor<Tip1, Tip2>* prije_p=nullptr;
        Cvor<Tip1, Tip2>* p=korijen;
        while(p!=nullptr)
        {
            prije_p=p;
            if(kljuc<p->kljuc)
            {
                p=p->lijevi;
            }
            else p=p->desni;
        }
        if(prije_p==nullptr)
        {
            korijen=temp;
        }
        else
        {
            if(kljuc<prije_p->kljuc) prije_p->lijevi=temp;
            else prije_p->desni=temp;
            temp->roditelj=prije_p;
        }
        broj_elemanata++;
        return temp->vrijednost;
        
            
    }
    else return poc->vrijednost;
}

template<typename Tip1, typename Tip2>
Tip2 BinStabloMapa<Tip1, Tip2>::operator[](Tip1 kljuc) const
{
    Cvor<Tip1, Tip2>* poc=korijen;
    while(poc)
    {
        if(kljuc==poc->kljuc) return poc->vrijednost;
        else if(kljuc<poc->kljuc) poc=poc->lijevi;
        else poc=poc->desni;
    }
    return Tip2();
}

template<typename Tip1, typename Tip2>
int BinStabloMapa<Tip1, Tip2>::brojElemenata()
{
    return broj_elemanata;
}

template<typename Tip1, typename Tip2>
int BinStabloMapa<Tip1, Tip2>::brojElemenata() const
{
    return broj_elemanata;
}

template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1, Tip2>::obrisi()
{
    brisi(korijen);
    korijen=nullptr;
    broj_elemanata=0;
}

template<typename Tip1, typename Tip2>
void BinStabloMapa<Tip1, Tip2>::obrisi(const Tip1& kljuc) 
{
    brisiCvor(korijen, kljuc);
    if(broj_elemanata>0)
    broj_elemanata--;
}
template<typename Tip1, typename Tip2>
class NizMapa: public Mapa<Tip1, Tip2>
{
private:
    std::pair<Tip1, Tip2> *poc;
    int kapacitet;
    int velicina;
public:
    NizMapa()
    {
        kapacitet=100;
        velicina=0;
        poc=new std::pair<Tip1, Tip2>[100];
    }
    ~NizMapa()
    {
        delete[] poc;
        velicina=0;
        kapacitet=0;
    }
    Tip2& operator[](Tip1 kljuc);
    Tip2 operator[](Tip1 kljuc)const;
    int brojElemenata() override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Tip1& kljuc) override;
    NizMapa(const NizMapa &n);
    NizMapa& operator=(const NizMapa &n);

};
template<typename Tip1, typename Tip2>
int NizMapa<Tip1, Tip2>::brojElemenata()const
{
    return velicina;
}
template<typename Tip1, typename Tip2>
NizMapa<Tip1, Tip2>& NizMapa<Tip1, Tip2>::operator=(const NizMapa &n)
{
    if(&n==this)
    {
        return *this;
    }
    delete[] poc;
    kapacitet=n.kapacitet;
    velicina=n.velicina;
    poc=new std::pair<Tip1, Tip2>[kapacitet];
    for(int i=0; i<velicina; i++)
    {
        poc[i]=std::make_pair(n.poc[i].first, n.poc[i].second);
    }
    return *this;
}
template<typename Tip1, typename Tip2>
NizMapa<Tip1, Tip2>::NizMapa(const NizMapa &n)
{
    kapacitet=n.kapacitet;
    velicina=n.velicina;
    poc=new std::pair<Tip1, Tip2>[kapacitet];
    for(int i=0; i<velicina; i++)
    {
        poc[i]=std::make_pair(n.poc[i].first, n.poc[i].second);
    }
}

template<typename Tip1, typename Tip2>
Tip2& NizMapa<Tip1, Tip2>::operator[](Tip1 kljuc)
{
    if(kapacitet==0)
    {
        poc=new std::pair<Tip1, Tip2>[100];
        kapacitet=100;
        poc[0]=std::make_pair(kljuc, Tip2());
        velicina=1;
        return poc[0].second;
    }
    for(int i=0; i<velicina; i++)
    {
        if(poc[i].first==kljuc)
        {
            return poc[i].second;
        }
    }
    if(velicina==kapacitet)
    {
        std::pair<Tip1, Tip2> *pom=new std::pair<Tip1, Tip2>[kapacitet*2];
        kapacitet*=2;
        for(int i=0; i<velicina; i++)
        {
            pom[i]=std::make_pair(poc[i].first, poc[i].second);
        }
        delete[] poc;
        poc=pom;
    }
    poc[velicina]=std::make_pair(kljuc, Tip2());
    int index=velicina;
    velicina++;
    return poc[index].second;
    
}
template<typename Tip1, typename Tip2>
Tip2 NizMapa<Tip1, Tip2>::operator[](Tip1 kljuc)const 
{
    for(int i=0; i<velicina; i++)
    {
        if(poc[i].first==kljuc)
        {
            return poc[i].second;
        }
    }
    return Tip2();
}
template<typename Tip1, typename Tip2>
int NizMapa<Tip1, Tip2>::brojElemenata()
{
    return velicina;
}
template<typename Tip1, typename Tip2>
void NizMapa<Tip1, Tip2>::obrisi()
{
    delete[] poc;
    poc=nullptr;
    velicina=0;
    kapacitet=0;
}
template<typename Tip1, typename Tip2>
void NizMapa<Tip1, Tip2>::obrisi(const Tip1& kljuc)
{
    if(velicina==1 && poc[0].first==kljuc)
    {
        delete[] poc;
        poc=nullptr;
        velicina=0;
        kapacitet=0;
        return;
    }
    for(int i=0; i<velicina; i++)
    {
        if(poc[i].first==kljuc)
        {
            for(int j=i+1; j<velicina; j++)
            {
                poc[j-1]=poc[j];
            }
            velicina--;
            return;
        }
    }
    throw "NEJMA!";
}
void testni_program()
{
    NizMapa<int, int>niz_mapa;
    BinStabloMapa<int, int>binarno_stablo_mapa;
    srand(time(NULL));
    clock_t t1=clock();
    for(int i=0; i<10000; i++)
    {
        niz_mapa[i]=rand();
    }
    clock_t t2=clock();
    std::cout<<"Vrijeme upisivanja u NizMapu: "<<(t2-t1)/(CLOCKS_PER_SEC/1000.)<<std::endl;
    srand(time(NULL));
    t1=clock();
    for(int i=0; i<10000; i++)
    {
        niz_mapa[i]=rand();
    }
    t2=clock();
    std::cout<<"Vrijeme upisivanja u BinStabloMapu: "<<(t2-t1)/(CLOCKS_PER_SEC/1000.)<<std::endl;
    /*Kod NizMape dodavanje elementa ima kompleksnost O(n), jer se prvo prolazi sekvencijalno kroz 
    NizMapu koja ima n elemenata, te se dodaje novi element.
    
    Kod BinStabloMape dodavanje elementa ima kompleksnost O(log(n)), sto zakljucujemo na sljedeci nacin.
    Prvo se vrsi pretraga da li je dati element vec u mapi, sto se izvodi sa logaritamskom kompleksnoscu.
    Zatim se trazi mjesto gdje ce se dodati novi element, sto se također izvodi sa logaritamskom kompleksnoscu.
    Odavdje slijedi gore navedena tvrdnja (log(n) i log(n) se sabiraju = 2log(n))
    */
    
    t1=clock();
    for(int i=0; i<10000; i++)
    {
        niz_mapa[i];
    }
    t2=clock();
    std::cout<<"Vrijeme pristupa elementima NizMape: "<<(t2-t1)/(CLOCKS_PER_SEC/1000.)<<std::endl;
    t1=clock();
    for(int i=0; i<10000; i++)
    {
        binarno_stablo_mapa[i];
    }
    t2=clock();
    std::cout<<"Vrijeme pristupa elementima BinStabloMape: "<<(t2-t1)/(CLOCKS_PER_SEC/1000.)<<std::endl;
    /*Pristup elementu NizMape se izvodi sa vremenskom kompleksnoscu od O(n), s obzirom da se pristup desava sekvencijalno, te
    se porede vrijednosti prosljeđenog parametra i vrijednost kljuca na indeksima elemenata niza.
    
    Pristup elementu BinStabloMape se izvodi sa kompleksnoscu od O(n), sto zakljucujemo iz same strukture binarnog stabla.
    */
}
int main()
{
    testni_program();
    return 0;
}