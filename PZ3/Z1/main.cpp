#include <iostream>
#include <stdexcept>

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
int main() 
{
    Stek<int>s;
    for(int i=0; i<10; i++)
    {
        s.stavi(i+1);
    }
    int duzina=s.brojElemenata();
    for(int i=0; i<duzina; i++)
    {
        std::cout<<s.skini()<<" ";
    }
    std::cout<<std::endl<<"Trenutna duzina je: "<<s.brojElemenata()<<std::endl;
    Stek<int>s1;
    for(int i=0; i<5; i++)
    {
        s1.stavi(1);
    }
    Stek<int>s2(s1);
    s=s1;
    duzina=s2.brojElemenata();
    int duzina1=s1.brojElemenata();
    for(int i=0; i<duzina; i++)
    {
        std::cout<<s2.skini()<<" ";
    }
    std::cout<<std::endl;
    for(int i=0; i<duzina1; i++)
    {
        std::cout<<s.skini()<<" ";
    }
    s.brisi();
    std::cout<<std::endl<<"Trenutni broj elemenata steka s je: "<<s.brojElemenata()<<std::endl;
    return 0;
}
