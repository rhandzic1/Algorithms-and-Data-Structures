#include <iostream>

template<typename Tip>
class Lista 
{
private:
    void operator=(const Lista&);
    Lista(const Lista&);
public:
    Lista() {}
    virtual ~Lista() {}
    virtual int brojElemenata()=0;
    virtual int brojElemenata()const=0;
    virtual Tip& trenutni()=0;
    virtual Tip trenutni()const=0;
    virtual bool prethodni()=0;
    virtual bool sljedeci()=0;
    virtual void pocetak()=0;
    virtual void kraj()=0;
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip& el)=0;
    virtual Tip& operator[](int i)=0;
    virtual Tip operator[](int i)const=0;
};

template<typename Tip>
class DvostrukaLista : public Lista<Tip>
{
private:
    struct Cvor
    {
        Tip element;
        Cvor *prethodnip;
        Cvor *sljedecip;
        Cvor(const Tip& el, Cvor* prev, Cvor* next):element(el), prethodnip(prev), sljedecip(next)
        {}
    };
    Cvor *trenutnip, *pocetakp, *krajp;
   int duzina;
public:
    DvostrukaLista();
    DvostrukaLista(const DvostrukaLista &lista);
    ~DvostrukaLista();
    DvostrukaLista& operator=(const DvostrukaLista &lista);
    Tip &trenutni() override;
    Tip trenutni() const override;
    void dodajIza(const Tip& el) override;
    void dodajIspred(const Tip& el) override;
    void pocetak() override;
    void kraj() override;
    void obrisi() override;
    Tip& operator[](int indeks);
    Tip operator[](int indeks) const;
    bool sljedeci() override;
    bool prethodni() override ;
    int brojElemenata() const override;
    int brojElemenata() override;
};
template<typename Tip>
DvostrukaLista<Tip> &DvostrukaLista<Tip>::operator=(const DvostrukaLista &lista)
{
    if(&lista==this)
    {
        return *this;    
    }
    if(this->brojElemenata()!=0)
    {
        pocetak();
        int br=this->brojElemenata();
        for(int i=0; i<br; i++)
        {
            obrisi();
        }
    }
    pocetakp=nullptr;
    krajp=nullptr;
    trenutnip=nullptr;
    Cvor*poc =lista.pocetakp;
    while(poc!=nullptr)
    {
        Cvor *novi=new Cvor(poc->element, nullptr, nullptr);
        if(pocetakp==nullptr)
        {
            pocetakp=novi;
            krajp=novi;
            trenutnip=novi;
        }
        else
        {
            krajp->sljedecip=novi;
            novi->prethodnip=krajp;
        }
        krajp=novi;
        poc=poc->sljedecip;
    }
    duzina=lista.duzina;

    return *this;
    
}
template<typename Tip>
DvostrukaLista<Tip>::~DvostrukaLista()
{
    Cvor *pomocni=pocetakp, *pomocni2;
    while(pomocni!=nullptr)
    {
        pomocni2=pomocni->sljedecip;
        delete pomocni;
        pomocni=pomocni2;
    }
    pocetakp=nullptr;
    krajp=nullptr;
    trenutnip=nullptr;
    
}
template<typename Tip>
DvostrukaLista<Tip>::DvostrukaLista(const DvostrukaLista &lista)
{
    pocetakp=nullptr;
    krajp=nullptr;
    trenutnip=nullptr;
    Cvor *poc=lista.pocetakp;
    while(poc!=nullptr)
    {
        Cvor *novi=new Cvor(poc->element, nullptr, nullptr);
        if(pocetakp==nullptr)
        {
            pocetakp=novi;
            krajp=novi;
            trenutnip=novi;
        }
        else
        {
            krajp->sljedecip=novi;
            novi->prethodnip=krajp;
        }
        krajp=novi;
        poc=poc->sljedecip;
    }
    duzina=lista.duzina;
}
template<typename Tip>
Tip& DvostrukaLista<Tip>::operator[](int indeks)
{
    if(!(indeks>=0 && indeks<duzina)) throw std::domain_error("Ilegalan indeks!");
    Cvor* povratni=pocetakp;
    for(int i=0; i<indeks; i++)
    {
        povratni=povratni->sljedecip;
    }
    return povratni->element;
}
template<typename Tip>
Tip DvostrukaLista<Tip>::operator[](int indeks)const
{
    if(!(indeks>=0 && indeks<duzina)) throw std::domain_error("Ilegalan indeks!");
    Cvor* povratni=pocetakp;
    for(int i=0; i<indeks; i++)
    {
        povratni=povratni->sljedecip;
    }
    return povratni->element;    
}
template<typename Tip>
Tip DvostrukaLista<Tip>::trenutni()const
{
    return trenutnip->element;
}
template<typename Tip>
Tip &DvostrukaLista<Tip>::trenutni()
{
    return trenutnip->element;
}
template<typename Tip>
int DvostrukaLista<Tip>::brojElemenata()
{
    return duzina;
}
template<typename Tip>
int DvostrukaLista<Tip>::brojElemenata()const
{
    return duzina;
}
template<typename Tip>
bool DvostrukaLista<Tip>::prethodni()
{
    if(trenutnip->prethodnip==nullptr)
    {
        return false;
    }
    trenutnip=trenutnip->prethodnip;
    return true;
}
template<typename Tip>
bool DvostrukaLista<Tip>::sljedeci()
{
    if(trenutnip->sljedecip==nullptr)
    {
        return false;
    }
    trenutnip=trenutnip->sljedecip;
    return true;
}
template<typename Tip>
void DvostrukaLista<Tip>::obrisi()
{
    if(pocetakp==nullptr) throw std::range_error("prazna lista!");
    if(pocetakp==krajp)
    {
        delete trenutnip;
        trenutnip=nullptr;
        pocetakp=nullptr;
        krajp=nullptr;
        duzina=0;
    }
    else if(trenutnip==pocetakp)
    {
        pocetakp=pocetakp->sljedecip;
        delete trenutnip;
        trenutnip=pocetakp;
        pocetakp->prethodnip=nullptr;
        duzina--;
        
    }
    else if(trenutnip==krajp)
    {
        krajp=krajp->prethodnip;
        delete trenutnip;
        trenutnip=krajp;
        krajp->sljedecip=nullptr;
        duzina--;
    
    }
    else
    {
        Cvor* pomocni=trenutnip->sljedecip;
        (trenutnip->prethodnip)->sljedecip=trenutnip->sljedecip;
        (trenutnip->sljedecip)->prethodnip=trenutnip->prethodnip;
        delete trenutnip;
        trenutnip=pomocni;
        duzina--;
    }
}
template<typename Tip>
void DvostrukaLista<Tip>::pocetak()
{
    if(duzina==0) throw std::range_error("Prazna lista!");
    trenutnip=pocetakp;
}
template<typename Tip>
void DvostrukaLista<Tip>::kraj()
{
    if(duzina==0) throw std::range_error("Prazna lista!");
    trenutnip=krajp;
}
template<typename Tip>
DvostrukaLista<Tip>::DvostrukaLista()
{
    trenutnip=nullptr;
    pocetakp=nullptr;
    krajp=nullptr;
    duzina=0;
}
template<typename Tip>
void DvostrukaLista<Tip>::dodajIza(const Tip &el)
{
    if(duzina==0)
    {
        pocetakp=new Cvor(el, nullptr, nullptr);
        krajp=pocetakp;
        trenutnip=pocetakp;
        duzina++;
    }
    else if(trenutnip->sljedecip==nullptr)
    {
        Cvor *novi=new Cvor(el, trenutnip, nullptr);
        trenutnip->sljedecip=novi;
        krajp=novi;
        duzina++;
    }
    else
    {
        Cvor *novi=new Cvor(el, trenutnip, trenutnip->sljedecip);
        Cvor *pomocni=trenutnip->sljedecip;
        trenutnip->sljedecip=novi;
        pomocni->prethodnip=novi;
        duzina++;
        
    }
    
}
template<typename Tip>
void DvostrukaLista<Tip>::dodajIspred(const Tip &el)
{
    if(duzina==0)
    {
        pocetakp=new Cvor(el, nullptr, nullptr);
        krajp=pocetakp;
        trenutnip=pocetakp;
        duzina++;
    }
    else if(trenutnip->prethodnip==nullptr)
    {
        Cvor *novi=new Cvor(el, nullptr, trenutnip);
        trenutnip->prethodnip=novi;
        pocetakp=novi;
        duzina++;
    }
    else
    {
        Cvor *novi=new Cvor(el, trenutnip->prethodnip, trenutnip);
        Cvor *pomocni=trenutnip->prethodnip;
        trenutnip->prethodnip=novi;
        pomocni->sljedecip=novi;
        duzina++;
    }
}
template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n)
{
    DvostrukaLista<Tip>l((*((DvostrukaLista<Tip>*)(&n))));
    l.pocetak();
    Tip max=l.trenutni();
    while(l.sljedeci())
    {
        if(l.trenutni()>max)
        {
            max=l.trenutni();
        }
    }
    return max;
}
int main()
{
    DvostrukaLista<int>l;
    for(int i=0; i<20; i++)
    {
        l.dodajIza((i+1)*10);
    }
    for(int i=0; i<l.brojElemenata(); i++)
    {
        std::cout<<l[i]<<" ";
    }
    std::cout<<std::endl<<"Dodavanje ispred: ";
    for(int i=0; i<10; i++)
    {
        l.dodajIspred(i+1);
    }
    for(int i=0; i<l.brojElemenata(); i++)
    {
        std::cout<<l[i]<<" ";
    }
    std::cout<<std::endl<<"Trenutni element: "<<l.trenutni()<<std::endl;
    l.pocetak();
    std::cout<<std::endl<<"Trenutni element: "<<l.trenutni()<<std::endl;
    l.kraj();
    std::cout<<std::endl<<"Trenutni element: "<<l.trenutni()<<std::endl;
    l.pocetak();
    int duzina=l.brojElemenata();
    for(int i=0; i<duzina; i++)
    {
        l.obrisi();
    }
    if(l.brojElemenata()==0)
    {
        std::cout<<"USPJESNO BRISANJE"<<std::endl;
    }
    else
    {
        std::cout<<"GRESKA"<<std::endl;
    }
    try
    {
        l.obrisi();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        l.pocetak();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        l.kraj();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    Lista<int>* lista;
    lista=new DvostrukaLista<int>;
    for(int i=0; i<10; i++)
    {
        lista->dodajIza(i+1);
    }
    for(int i=0; i<lista->brojElemenata(); i++)
    {
        std::cout<<(*lista)[i]<<" ";
    }
    try
    {
        std::cout<<(*lista)[lista->brojElemenata()];
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    DvostrukaLista<int> l1;
    for(int i=0; i<100; i++)
    {
        l1.dodajIza(i+1);
    }
    for(int i=0; i<15; i++)
    {
        l1.dodajIza((i+1)*10);
    }
    std::cout<<"Maksimalni element je: "<<dajMaksimum(l1);
    DvostrukaLista<int>l3(l1);
    for(int i=0; i<l3.brojElemenata(); i++)
    {
        std::cout<<l3[i]<<" "; 
    }
    //OPERATOR DODJELE
    l1=l3;
    for(int i=0; i<l3.brojElemenata(); i++)
    {
        std::cout<<l1[i]<<" ";
    }
}

