#include <iostream>

template<typename Tip>
class Red
{
private:
    struct Cvor
    {
        Tip element;
        Cvor* sljedeci;
        Cvor(Tip el, Cvor* slj): element(el), sljedeci(slj){}
    };
    Cvor* pocetak;
    Cvor* kraj;
    int velicina;
    void kopiraj(const Red &r);
public: 
    Red()
    {
        pocetak=nullptr;
        kraj=nullptr;
        velicina=0;
    }
    
    Red(const Red &r);
    Red& operator=(const Red &r);
    ~Red();
    void brisi();
    void stavi(const Tip &el);
    Tip skini();
    Tip &celo();
    int brojElemenata();
};
template<typename Tip>
void Red<Tip>::kopiraj(const Red &r)
{
    Cvor *pomocni, *b(r.pocetak);
    pocetak=nullptr;
    velicina=r.velicina;
    while(b!=nullptr)
    {
        Cvor *novi=new Cvor(b->element, nullptr);
        if(pocetak==nullptr)
        {
            pocetak=novi;
            kraj=novi;
        }
        else
        {
            pomocni->sljedeci=novi;
            kraj=novi;
        }
        b=b->sljedeci;
        pomocni=novi;
    }
}
template<typename Tip>
Red<Tip>::Red(const Red &r)
{
    kopiraj(r);
}
template<typename Tip>
Red<Tip>& Red<Tip>::operator=(const Red &r)
{
    if(this==&r)
    {
        return *this;
    }
    brisi();
    kopiraj(r);
    return *this;
}
template<typename Tip>
Red<Tip>::~Red()
{
    brisi();
}
template<typename Tip>
void Red<Tip>::brisi()
{
    while(pocetak!=nullptr)
    {
        Cvor* pomocni=pocetak->sljedeci;
        delete pocetak;
        pocetak=pomocni;
    }
    velicina=0;
}
template<typename Tip>
void Red<Tip>::stavi(const Tip &el)
{
    Cvor *pomocni=new Cvor(el, nullptr);
    if(velicina==0){
        pocetak=pomocni;
        kraj=pomocni;
    }
    else
    {
        kraj->sljedeci=pomocni;
        kraj=pomocni;
    }
    velicina++;
}
template<typename Tip>
Tip Red<Tip>::skini()
{
    if(velicina==0) throw "Red je prazan";
    Tip povratni=pocetak->element;
    Cvor* pomocni=pocetak->sljedeci;
    delete pocetak;
    pocetak=pomocni;
    velicina--;
    return povratni;
    
}
template<typename Tip>
Tip& Red<Tip>::celo()
{
    return pocetak->element;
}
template<typename Tip>
int Red<Tip>::brojElemenata()
{
    return velicina;
}

int main()
{
    Red<int>r;
    for(int i=0; i<10; i++)
    {
        r.stavi(i+1);
    }
    std::cout<<"Broj elemenata reda je: "<<r.brojElemenata()<<std::endl;
    r.brisi();
    std::cout<<"Broj elemanata reda je: "<<r.brojElemenata()<<std::endl;
    for(int i=0; i<10; i++)
    {
        r.stavi(i+1);
    }
    std::cout<<"Ispis reda: ";
    for(int i=0; i<10; i++)
    {
        int pomocna=r.skini();
        std::cout<<pomocna<<" ";
        r.stavi(pomocna);
    }
    std::cout<<std::endl<<"Prvi element reda je: "<<r.celo()<<std::endl;
    r.celo()=15;
    std::cout<<r.celo()<<std::endl;
    Red<int>noviRed(r);
    std::cout<<"Ispis novog reda: ";
    for(int i=0; i<noviRed.brojElemenata(); i++)
    {
        int pomocna=noviRed.skini();
        std::cout<<pomocna<<" ";
        noviRed.stavi(pomocna);
    }
    r.brisi();
    for(int i=0; i<10; i++)
    {
        r.stavi((i+1)*10);
    }
    noviRed=r;
    std::cout<<std::endl<<"Novi red nakon operatora dodjele: "<<std::endl;
    for(int i=0; i<10; i++)
    {
        int pomocna=noviRed.skini();
        std::cout<<pomocna<<" ";
        noviRed.stavi(pomocna);
    }
    noviRed.brisi();
    //BROJ ELEMENATA NAKON BRISANJA
    std::cout<<std::endl<<noviRed.brojElemenata();
    
}