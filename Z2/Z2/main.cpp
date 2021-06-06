#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
template<typename Tip>
class Stek
{
private:
    struct Cvor
    {
        Tip element;
        Cvor *sljedeci;
        Cvor(const Tip& el, Cvor* slj): element(el), sljedeci(slj){}
    };
    Cvor* top;
    int velicina;
    void kopiraj(const Stek& s);
public:
    Stek(): top(nullptr), velicina(0) {}
    ~Stek()
    {
        brisi();
    }
    Stek(const Stek& s);
    Stek& operator=(const Stek& s);
    void brisi();
    void stavi(const Tip& el);
    Tip skini();
    Tip& vrh();
    int brojElemenata();
};
template<typename Tip>
void Stek<Tip>::kopiraj(const Stek& s)
{
    Cvor *pomocni, *b(s.top);
    this->top=nullptr;
    velicina=s.velicina;
    while(b!=nullptr)
    {
        Cvor *novi=new Cvor(b->element, nullptr);
        if(this->top==nullptr)
        {
            this->top=novi;
        }
        else
        {
            pomocni->sljedeci=novi;
        }
        b=b->sljedeci;
        pomocni=novi;
    }
}
template<typename Tip>
Stek<Tip>::Stek(const Stek& s)
{
    kopiraj(s);
}
template<typename Tip>
Stek<Tip>& Stek<Tip>::operator=(const Stek& s)
{
    if(this==&s)
    {
        return *this;
    }
    brisi();
    kopiraj(s);
    return *this;
}
template<typename Tip>
void Stek<Tip>::brisi()
{
  
    while(top!=nullptr)
    {
        Cvor *pomocni=top->sljedeci;
        delete top;
        top=pomocni;
    }
    velicina=0;
}
template<typename Tip>
void Stek<Tip>::stavi(const Tip& el)
{
    Cvor *pomocni=new Cvor(el, top);
    top=pomocni;
    velicina++;
}
template<typename Tip>
Tip Stek<Tip>::skini()
{
    if(top==nullptr)
    {
        throw "Stek je prazan!";
    }
    Tip povratni=top->element;
    Cvor* pomocni=top->sljedeci;
    delete top;
    top=pomocni;
    velicina--;
    return povratni;
}
template<typename Tip>
Tip& Stek<Tip>::vrh()
{
    return top->element;
}
template<typename Tip>
int Stek<Tip>::brojElemenata()
{
    return velicina;
}
void pretraga(Stek<std::vector<int>> &s, int trazeni)
{
    if(s.brojElemenata()==0)
    {
        std::cout<<"Nema elementa"<<std::endl;
        return;
    }
    std::vector<int>pomocni=s.vrh();
    int dno=0;
    int vrh=pomocni.size()-1;
    int brojac_ispod=s.brojElemenata()-1;
    while(vrh>=dno)
    {
        int srednji=(vrh+dno)/2;
        if(pomocni[srednji]==trazeni)
        {
            std::cout<<srednji<<" "<<brojac_ispod;
            return;
        }
        else if(pomocni[srednji]>trazeni)
        {
            vrh=srednji-1;
        }
        else
        {
            dno=srednji+1;
        }
    }
    s.skini();
    brojac_ispod--;
    pretraga(s, trazeni);
    s.stavi(pomocni);
}
void ispisiStek(Stek<std::vector<int>>&s)
{
    if(s.brojElemenata()==0)
    {
        std::cout<<"\n";
        return;
    }
    std::vector<int>pomocni=s.skini();
    for(int i=0; i<pomocni.size(); i++)
    {
        std::cout<<pomocni[i]<<" ";
    }
    std::cout<<std::endl;
    ispisiStek(s);
    s.stavi(pomocni);
}
void UspjesnaPretraga(Stek<std::vector<int>> &s, int broj, int a, int b)
{
    std::cout<<"Funkcija za pretragu je ispisala: ";
    pretraga(s, broj);
    std::cout<<std::endl;
    std::cout<<"Ocekivana vrijednost je: "<<a<<" "<<b<<std::endl;
}
void NemaElementa(Stek<std::vector<int>> &s, int el)
{
    std::cout<<"Funkcija za pretragu je ispisala: ";
    pretraga(s, el);
    std::cout<<std::endl;
    std::cout<<"Ocekivani ispis je: Nema elementa"<<std::endl;
}
int main()
{
    Stek<std::vector<int>>s;
    std::vector<int>a{1,2,3,4,5,6};
    std::vector<int>b{8,9,15,16,17};
    std::vector<int>c{22, 27, 33, 39};
    std::vector<int>d{50, 59, 69, 79, 89, 115};
    s.stavi(a);
    s.stavi(b);
    s.stavi(c);
    s.stavi(d);
    std::cout<<"Stek prije pretrazivanja: "<<std::endl;
    ispisiStek(s);
    pretraga(s, 15);
    std::cout<<std::endl<<"Stek poslije pretrazivanja: "<<std::endl;
    ispisiStek(s);
    //REGULARNE PRETRAGE
    pretraga(s, 27);
    std::cout<<std::endl;
    pretraga(s, 115);
    std::cout<<std::endl;
    pretraga(s, 16);
    std::cout<<std::endl;
    //PRETRAGA KADA ELEMENT NIJE U STEKU
    pretraga(s, 215);
    std::cout<<std::endl;
    pretraga(s, 0);
    std::cout<<std::endl;
    pretraga(s, -59);
    std::cout<<std::endl;
    UspjesnaPretraga(s, 4, 3, 0);
    UspjesnaPretraga(s, 17, 4, 1);
    UspjesnaPretraga(s, 50, 0, 3);
    NemaElementa(s, 1111);
    NemaElementa(s, -55);
    NemaElementa(s, -1);
    return 0;
}