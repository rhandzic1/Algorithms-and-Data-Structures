#include <iostream>

template<typename Tip>
class DvostraniRed
{
    struct Cvor
    {
        Tip element;
        Cvor *prethodni;
        Cvor *sljedeci;
        Cvor(Tip el, Cvor *pre, Cvor *slj):element(el), prethodni(pre), sljedeci(slj){}
    };
    Cvor *pocetak;
    Cvor *kraj;
    int duzina;
    void kopiraj(const DvostraniRed &r);
public:
    DvostraniRed();
    ~DvostraniRed();
    DvostraniRed(const DvostraniRed &r);
    DvostraniRed &operator=(const DvostraniRed &r);
    void brisi();
    int brojElemenata();
    void staviNaVrh(const Tip &el);
    Tip skiniSaVrha();
    void staviNaCelo(const Tip &el);
    Tip skiniSaCela();
    Tip &vrh();
    Tip &celo();
};
template<typename Tip>
DvostraniRed<Tip>::~DvostraniRed()
{
    brisi();
}
template<typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip &el)
{
    Cvor *novi=new Cvor(el, nullptr, nullptr);
    if(duzina==0)
    {
        pocetak=novi;
        kraj=novi;
    }
    else
    {
        kraj->sljedeci=novi;
        novi->prethodni=kraj;
        kraj=novi;
    }
    duzina++;
}
template<typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip &el)
{
    Cvor *novi=new Cvor(el, nullptr, nullptr);
    if(duzina==0)
    {
        pocetak=novi;
        kraj=novi;
    }
    else
    {
        novi->sljedeci=pocetak;
        pocetak->prethodni=novi;
        pocetak=novi;
    }
    duzina++;
}
template<typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha()
{
    if(duzina==0) throw "Prazan DvostraniRed";
    Tip pom=kraj->element;
    Cvor *pomocni=kraj->prethodni;
    delete kraj;
    kraj=pomocni;
    duzina--;
    if(duzina==0)
    {
        pocetak=nullptr;
        kraj=nullptr;
    }
    return pom;
}
template<typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela()
{
    if(duzina==0) throw "Prazan DvostraniRed";
    Tip pom=pocetak->element;
    Cvor *pomocni=pocetak->sljedeci;
    delete pocetak;
    pocetak=pomocni;
    duzina--;
    if(duzina==0)
    {
        pocetak=nullptr;
        kraj=nullptr;
    }
    return pom;
}
template<typename Tip>
Tip& DvostraniRed<Tip>::vrh()
{
    if(duzina==0) throw "Prazan DvostraniRed";
    return kraj->element;
}
template<typename Tip>
Tip& DvostraniRed<Tip>::celo()
{
    if(duzina==0) throw "Prazan DvostraniRed";
    return pocetak->element;
}
template<typename Tip>
DvostraniRed<Tip>::DvostraniRed()
{
    pocetak=nullptr;
    kraj=nullptr;
    duzina=0;
    
}
template<typename Tip>
DvostraniRed<Tip>::DvostraniRed(const DvostraniRed &r)
{
    kopiraj(r);
}
template<typename Tip>
DvostraniRed<Tip> &DvostraniRed<Tip>::operator=(const DvostraniRed &r)
{
    if(&r==this) return *this;
    brisi();
    kopiraj(r);
    return *this;
}
template<typename Tip>
void DvostraniRed<Tip>::kopiraj(const DvostraniRed &r)
{
    Cvor *pomocni, *b(r.pocetak);
    pocetak=nullptr;
    duzina=r.duzina;
    while(b!=nullptr)
    {
        Cvor *novi=new Cvor(b->element, nullptr, nullptr);
        if(pocetak==nullptr)
        {
            pocetak=novi;
            kraj=novi;
        }
        else
        {
            pomocni->sljedeci=novi;
            novi->prethodni=kraj;
            kraj=novi;
        }
        pomocni=novi;
        b=b->sljedeci;
    }
}
template<typename Tip>
void DvostraniRed<Tip>::brisi()
{
    while(duzina!=0)
    {
        Cvor *pomocni=pocetak->sljedeci;
        delete pocetak;
        pocetak=pomocni;
        duzina--;
    }
    pocetak=nullptr;
    kraj=nullptr;
    duzina=0;
}
template<typename Tip>
int DvostraniRed<Tip>::brojElemenata()
{
    return duzina;
}
int main() {
    DvostraniRed<int>dr;
    for(int i=0; i<10; i++)
    {
        dr.staviNaVrh(i+1);
    }
    //ISPIS
    for(int i=0; i<10; i++)
    {
        int el=dr.skiniSaCela();
        std::cout<<el<<" ";
        dr.staviNaVrh(el);
    }
    //PROVJERA BROJA ELEMENATA
    std::cout<<std::endl<<"Broj elemenata je: "<<dr.brojElemenata();
    for(int i=0; i<10; i++)
    {
        dr.staviNaCelo((i+1)*2);
    }
    //ISPIS
    std::cout<<std::endl;
    for(int i=0; i<20; i++)
    {
        int el=dr.skiniSaCela();
        std::cout<<el<<" ";
        dr.staviNaVrh(el);
    }
    //KOPIRAJUCI KONSTRUKTOR
    DvostraniRed<int>drugiRed(dr);
    //ISPIS UNAZAD
    std::cout<<std::endl;
    for(int i=0; i<20; i++)
    {
        int el=drugiRed.skiniSaVrha();
        std::cout<<el<<" ";
        drugiRed.staviNaCelo(el);
    }
    drugiRed.brisi();
    std::cout<<std::endl<<"Broj elemenata je: "<<drugiRed.brojElemenata()<<std::endl;
    //IZUZECI
    try
    {
        drugiRed.vrh();
    }
    catch(...)
    {
        std::cout<<"IZUZETAK"<<std::endl;
    }
    try
    {
        drugiRed.celo();
    }
    catch(...)
    {
        std::cout<<"IZUZETAK"<<std::endl;
    }
    try
    {
        drugiRed.skiniSaVrha();
    }
    catch(...)
    {
        std::cout<<"IZUZETAK"<<std::endl;
    }
    try
    {
        drugiRed.skiniSaCela();
    }
    catch(...)
    {
        std::cout<<"IZUZETAK"<<std::endl;
    }
    //OPERATOR DODJELE
    drugiRed=dr;
    //ISPIS I IZMJENA CELA I VRHA
    for(int i=0; i<drugiRed.brojElemenata(); i++)
    {
        int pomocni=drugiRed.skiniSaCela();
        std::cout<<pomocni<<" ";
        drugiRed.staviNaVrh(pomocni);
    }
    std::cout<<std::endl;
    std::cout<<"Prvi element je "<<drugiRed.celo()<<", a posljednji "<<drugiRed.vrh()<<std::endl;
    drugiRed.celo()=555;
    drugiRed.vrh()=666;
    std::cout<<"Nakon izmjene respektivno: "<<drugiRed.celo()<<" i "<<drugiRed.vrh()<<std::endl;
    return 0;
}
