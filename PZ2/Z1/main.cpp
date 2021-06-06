#include <iostream>
#include <stdexcept>
using namespace std;

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
class NizLista : public Lista<Tip>
{
protected:
    int trenutni_el;
    int kapacitet;
    int broj_elemenata;
    /*Tip *l;*/
    Tip **l;
public:
    NizLista()
    {
        /*l=new Tip[10];*/
        l=new Tip*[10];
        kapacitet=10;
        broj_elemenata=0;
    }
    NizLista(const NizLista &lista)
    {
        /*l=new Tip[lista.broj_elemenata];*/
        l=new Tip*[lista.broj_elemenata];
        for(int i=0; i<lista.broj_elemenata; i++)
        {
            /*l[i]=lista.l[i];*/
            l[i]=new Tip(*lista.l[i]);
        }
        kapacitet=lista.kapacitet;
        broj_elemenata=lista.broj_elemenata;
        trenutni_el=lista.trenutni_el;
    }
    NizLista& operator=(const NizLista &lista)
    {
        /*Tip *pomocni=new Tip[lista.broj_elemenata];*/
        Tip **pomocni=new Tip*[lista.broj_elemenata];
        for(int i=0; i<lista.broj_elemenata; i++)
        {
            /*pomocni[i]=lista.l[i];*/
            pomocni[i]=new Tip(*lista.l[i]);
        }
        /*delete[] l;*/
        for(int i=0; i<broj_elemenata; i++)
        {
            delete l[i];
        }
        delete[] l;
        l=pomocni;
        pomocni=nullptr;
        broj_elemenata=lista.broj_elemenata;
        kapacitet=lista.kapacitet;
        trenutni_el=lista.trenutni_el;
        return *this;
    }
    ~NizLista()
    {
        for(int i=0; i<broj_elemenata; i++)
        {
            delete l[i];
        }
        delete[] l;
        /*delete[] l;*/
    }
    int brojElemenata()
    {
        return broj_elemenata;
    }
    int brojElemenata()const
    {
        return broj_elemenata;
    }
    Tip& trenutni()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        return *l[trenutni_el];
    }
    Tip trenutni() const
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        return *l[trenutni_el];
    }
    bool prethodni()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        if(trenutni_el>0)
        {
            trenutni_el--;
            return true;
        }
        return false;
    }
    bool sljedeci()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        if(trenutni_el<broj_elemenata-1)
        {
            trenutni_el++;
            return true;
        }
        return false;
    }
    void pocetak()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        trenutni_el=0;
    }
    void kraj()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        trenutni_el=broj_elemenata-1;
       
    }
    void obrisi()
    {
        if(broj_elemenata==0)
        {
            throw std::domain_error("Prazna lista!");
        }
        if(trenutni_el==broj_elemenata-1)
        {
            delete l[trenutni_el];
            l[trenutni_el]=nullptr;
            broj_elemenata--;
            trenutni_el--;
        }
        else
        {
            delete l[trenutni_el];
            l[trenutni_el]=nullptr;
            for(int i=trenutni_el; i<broj_elemenata-1; i++)
            {
                l[i]=l[i+1];
            }
            broj_elemenata--;
        }
    }
    void dodajIspred(const Tip& el)
    {
        if(broj_elemenata==0)
        {
            /*l[0]=el;*/
            l[0]= new Tip(el);
            broj_elemenata++;
            trenutni_el=0;
        }
        else
        {
            if(broj_elemenata==kapacitet)
            {
                /*Tip *pomocni=new Tip[kapacitet+10];*/
                Tip **pomocni=new Tip*[kapacitet+int(kapacitet/2)]{};
                for(int i=0; i<broj_elemenata; i++)
                {
                    pomocni[i]=new Tip(*l[i]);
                }
                /*delete[] l;*/
                for(int i=0; i<broj_elemenata; i++)
                {
                    delete l[i];
                }
                delete[] l;
                l=pomocni;
                pomocni=nullptr;
                kapacitet+=int(kapacitet/2);
        }
        for(int i=broj_elemenata-1; i>=trenutni_el; i--)
        {
            /*l[i+1]=l[i];*/
            l[i+1]=l[i];
        }
        l[trenutni_el++]=new Tip(el);
        broj_elemenata++;
        }
    }
    void dodajIza(const Tip& el){
        if(broj_elemenata==0)
        {
            
            l[0]=new Tip(el);
            broj_elemenata++;
            trenutni_el=0;
        }
        else
        {
            if(broj_elemenata==kapacitet)
            {
                /*Tip *pomocni=new Tip[kapacitet+10];*/
                Tip **pomocni=new Tip*[kapacitet+int(kapacitet/2)];
                for(int i=0; i<broj_elemenata; i++)
                {
                    pomocni[i]=new Tip(*l[i]);
                }
                l=pomocni;
                pomocni=nullptr;
                kapacitet+=int(kapacitet/2);
            }
            for(int i=broj_elemenata-1; i>trenutni_el; i--)
            {
                l[i+1]=l[i];
            }
            l[++trenutni_el]=new Tip(el);
            trenutni_el--;
            broj_elemenata++;
        }
        
    }
    Tip& operator[](int i){
        if(!(i>=0 && i<broj_elemenata))
        {
            throw std::domain_error("Ilegalan indeks!");
        }
        return *l[i];
    }
    Tip operator[](int i)const
    {
        if(!(i>=0 && i<broj_elemenata))
        {
            throw std::domain_error("Ilegalan indeks!");
            
        }
        return *l[i];
    }
};
template<typename Tip>
struct Cvor
{
    Tip element;
    Cvor* veza;
};
template<typename Tip>
class JednostrukaLista : public Lista<Tip>
{
protected:
    Cvor<Tip> *pocetak_el, *trenutni_el, *kraj_el;
    int broj_elemenata;
     
public:
    JednostrukaLista()
    {
        broj_elemenata=0;
        pocetak_el=nullptr;
        trenutni_el=nullptr;
        kraj_el=nullptr;
    }
    void ispisUnazad()
    {
        
        if(broj_elemenata==0)
        {
            std::cout<<"\n";
            return;
        }
        kraj();
        Tip a=trenutni();
        std::cout<<a<<" ";
        obrisi();
        ispisUnazad();
        dodajIza(a);
        sljedeci();
    }
    int brojElemenata() const
    {
        return broj_elemenata;
    }
    int brojElemenata()
    {
        return broj_elemenata;
    }
    JednostrukaLista(const JednostrukaLista &lista)
    {
        pocetak_el=nullptr;
        trenutni_el=nullptr;
        kraj_el=nullptr;
        Cvor<Tip>*poc=lista.pocetak_el;
        while(poc!=nullptr)
        {
            Cvor<Tip>* novi=new Cvor<Tip>{poc->element, nullptr};
            if(pocetak_el==nullptr)
            {
                pocetak_el=novi;
                kraj_el=novi;
                trenutni_el=novi;
            }
            else
            {
                kraj_el->veza=novi;
            }
            kraj_el=novi;
            poc=poc->veza;
        }
        broj_elemenata=lista.broj_elemenata;
        
    }
    ~JednostrukaLista()
    {
        Cvor<Tip>* pomocni=pocetak_el;
        Cvor<Tip>* pomocni2;
        while(pomocni!=nullptr)
        {
            pomocni2=pomocni->veza;
            delete pomocni;
            pomocni=pomocni2;
                
        }
        pocetak_el=nullptr;
    }
    JednostrukaLista& operator=(const JednostrukaLista &lista)
    {
        Cvor<Tip>*pomocni=pocetak_el;
        while(pocetak_el!=kraj_el)
        {
            pocetak_el=pocetak_el->veza;
            delete pomocni;
            pomocni=pocetak_el;
        }
        delete pocetak_el;
        pomocni=lista.pocetak_el;
        pocetak_el=nullptr;
        trenutni_el=nullptr;
        kraj_el=nullptr;
        while(pomocni!=nullptr)
        {
            Cvor<Tip>* novi=new Cvor<Tip>{pomocni->element, nullptr};
            if(pocetak_el==nullptr)
            {
                pocetak_el=novi;
                kraj_el=novi;
            }
            else
            {
                kraj_el->veza=novi;
            }
            kraj_el=novi;
            pomocni=pomocni->veza;
        }
        broj_elemenata=lista.broj_elemenata;
        return *this;
    }
    Tip &trenutni()
    {
        return trenutni_el->element;
    }
    Tip trenutni() const
    {
        return trenutni_el->element;
    }
    void dodajIza(const Tip& el) override
    {
        if(pocetak_el==nullptr)
        {
            pocetak_el=new Cvor<Tip>{el, nullptr};
            trenutni_el=pocetak_el;
        }
        else if(trenutni_el==kraj_el)
        {
            Cvor<Tip>* novi=new Cvor<Tip>{el, nullptr};
            kraj_el->veza=novi;
            kraj_el=novi;
            novi->veza=nullptr;
            
        }
        else
        {
            Cvor<Tip>* novi=new Cvor<Tip>{el, nullptr};
            Cvor<Tip>* pomocni=trenutni_el->veza;
            trenutni_el->veza=novi;
            novi->veza=pomocni;
        }
        broj_elemenata++;
    }
    void dodajIspred(const Tip& el) override
    {
        if(pocetak_el==nullptr)
        {
            pocetak_el=new Cvor<Tip>{el, nullptr};
            trenutni_el=pocetak_el;
            kraj_el=pocetak_el;
            broj_elemenata++;
            return;
        }
        if(pocetak_el==trenutni_el || broj_elemenata==1)
        {
            Cvor<Tip>* novi=new Cvor<Tip>{el, nullptr};
            novi->veza=trenutni_el;
            pocetak_el=novi;
            broj_elemenata++;
            return;
        }
        else
        {
            Cvor<Tip>* pomocni=pocetak_el;
            while(pomocni->veza!=trenutni_el)
            {
                pomocni=pomocni->veza;
            }
            Cvor<Tip>* novi=new Cvor<Tip>{el, nullptr};
            pomocni->veza=novi;
            novi->veza=trenutni_el;
 
            broj_elemenata++;
        }
        
    }
    void pocetak() override
    {
        if(broj_elemenata==0)
        {
            throw std::range_error("Prazna lista!");
        }
        trenutni_el=pocetak_el;
    }
    void kraj() override
    {
        if(broj_elemenata==0)
        {
            throw std::range_error("Prazna lista!");
        }
        auto pomocni=pocetak_el;
        while(pomocni->veza!=nullptr)
        {
            pomocni=pomocni->veza;
        }
        trenutni_el=pomocni;
        
    }
    void obrisi() override
    {
        if(broj_elemenata==0)
        {
            throw std::range_error("Prazna lista!");
        }
        else if(broj_elemenata==1)
        {
            delete pocetak_el;
            pocetak_el=nullptr;
            kraj_el=nullptr;
            trenutni_el=nullptr;
            broj_elemenata=0;
        }
        else if(trenutni_el==pocetak_el)
        {
            Cvor<Tip>* pomocni=trenutni_el->veza;
            delete trenutni_el;
            pocetak_el=pomocni;
            trenutni_el=pomocni;
            broj_elemenata--;
        }
        
        else if(trenutni_el==kraj_el)
        {
            Cvor<Tip> *pomocni=pocetak_el;
            while(pomocni->veza!=trenutni_el)
            {
                pomocni=pomocni->veza;
            }
            delete trenutni_el;
            pomocni->veza=nullptr;
            trenutni_el=pomocni;
            kraj_el=pomocni;
            broj_elemenata--;
        }
        else
        {
            Cvor<Tip> *pomocni=pocetak_el;
            while(pomocni->veza!=trenutni_el && pomocni->veza!=nullptr)
            {
                pomocni=pomocni->veza;
            }
            pomocni->veza=trenutni_el->veza;
            pomocni=trenutni_el->veza;
            delete trenutni_el;
            trenutni_el=pomocni;
            broj_elemenata--;
        }
        
    }
    Tip& operator[](int indeks)
    {
        if(!(indeks>=0 && indeks<broj_elemenata))
        {
            throw std::domain_error("Ilegalan indeks");
        }
        Cvor<Tip> *povratni=pocetak_el;
        for(int i=0; i<indeks; i++)
        {
            povratni=povratni->veza;
        }
        return povratni->element;
    }
    Tip operator[](int indeks) const
    {
        if(!(indeks>=0 && indeks<broj_elemenata))
        {
            throw std::domain_error("Ilegalan indeks");
        }
        Cvor<Tip> *povratni=pocetak_el;
        for(int i=0; i<indeks; i++)
        {
            povratni=povratni->veza;
        }
        return povratni->element;
    }
    bool sljedeci() override
    {
        if(trenutni_el->veza==nullptr)
        {
            return false;
        }
        else
        trenutni_el=trenutni_el->veza;
        return true;
    }
    bool prethodni() override
    {
        if(trenutni_el!=pocetak_el)
        {
            Cvor<Tip>* pomocni=pocetak_el;
            while(pomocni->veza!=trenutni_el)
            {
                pomocni=pomocni->veza;
            }
            trenutni_el=pomocni;
            return true;
        }
        return false;
    }
};
int main() 
{
    
    NizLista<int> niz1;
    niz1.dodajIspred(1);
    niz1.dodajIspred(2);
    niz1.dodajIspred(3);
    niz1.dodajIspred(4);
    niz1.dodajIspred(5);
    std::cout<<"Broj elemenata je: "<<niz1.brojElemenata()<<std::endl;
    for(int i=0; i<niz1.brojElemenata(); i++)
    {
        std::cout<<niz1[i]<<" ";
    }
    niz1.kraj();
    std::cout<<std::endl;
    std::cout<<"Trenutni element je: "<<niz1.trenutni()<<std::endl;
    niz1.dodajIza(6);
    niz1.dodajIza(7);
    niz1.dodajIza(8);
    niz1.dodajIza(9);
    niz1.dodajIza(10);
    for(int i=0; i<niz1.brojElemenata(); i++)
    {
        std::cout<<niz1[i]<<" ";
    }
    std::cout<<std::endl;
    niz1.pocetak();
    niz1.obrisi();
    niz1.obrisi();
    for(int i=0; i<niz1.brojElemenata(); i++)
    {
        std::cout<<niz1[i]<<" ";
    }
    std::cout<<std::endl;
    try
    {
        std::cout<<niz1[niz1.brojElemenata()];
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what();
    }
    NizLista<int> niz2(niz1);
    NizLista<int> niz3=niz2;
    std::cout<<std::endl;
    for(int i=0; i<niz2.brojElemenata(); i++)
    {
        std::cout<<niz2[i]<<" ";
    }
    std::cout<<std::endl;
    for(int i=0; i<niz3.brojElemenata(); i++)
    {
        std::cout<<niz3[i]<<" ";
    }
    std::cout<<std::endl;
    //BRISANJE niz1
    niz1.pocetak();
    std::cout<<niz1.brojElemenata()<<std::endl;
    for(int i=0; i<8; i++)
    {
        niz1.obrisi();
    }
    std::cout<<"Broj elemenata niz1: "<<niz1.brojElemenata()<<std::endl;
    for(int i=0; i<niz1.brojElemenata(); i++)
    {
        std::cout<<niz1[i]<<" ";
    }
    try
    {
        niz1.trenutni();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        niz1.sljedeci();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        niz1.prethodni();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        niz1.obrisi();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        niz1.pocetak();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        niz1.kraj();
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    //TESTIRANJE JEDNOSTRUKE LISTE
    JednostrukaLista<int>l1;
    std::cout<<"Broj elemenata jednostruke liste je: "<<l1.brojElemenata()<<std::endl;
    for(int i=1; i<=10; i++)
    {
        l1.dodajIza(i);
    }
    std::cout<<std::endl;
    for(int i=0; i<l1.brojElemenata(); i++)
    {
        std::cout<<l1[i]<<" ";
    }
    std::cout<<std::endl<<"Trenutni element je: "<<l1.trenutni()<<std::endl;
    l1.kraj();
    std::cout<<"Trenutni element je: "<<l1.trenutni()<<std::endl;
    JednostrukaLista<int> l2(l1);
    for(int i=0; i<l2.brojElemenata(); i++)
    {
        std::cout<<l2[i]<<" ";
    }
    while(l2.brojElemenata()!=0)
    {
        l2.obrisi();
    }
    std::cout<<std::endl<<"Trenutni broj elemenata l2: "<<l2.brojElemenata()<<std::endl;
    try
    {
        l2.pocetak();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        l2.kraj();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        l2.trenutni();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        l2.obrisi();
    }
    catch(std::range_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    try
    {
        std::cout<<l2[15];
    }
    catch(std::domain_error izuzetak)
    {
        std::cout<<izuzetak.what()<<std::endl;
    }
    for(int i=0; i<10; i++)
    {
        l2.dodajIspred(10);
        std::cout<<l2[i]<<" ";
    }
    std::cout<<std::endl;
    for(int i=0; i<10; i++)
    {
        l2[i]=i+5;
        std::cout<<l2[i]<<" ";
    }
    std::cout<<std::endl<<"Trenutni element: "<<l2.trenutni();
    l2.prethodni();
    std::cout<<std::endl<<"Trenutni element "<<l2.trenutni();
    l2.pocetak();
    std::cout<<std::endl<<"Trenutni element "<<l2.trenutni();
    const JednostrukaLista<int>konstantna(l2);
    std::cout<<std::endl;
    for(int i=0; i<konstantna.brojElemenata(); i++)
    {
        std::cout<<konstantna[i]<<" ";
    }
    std::cout<<std::endl<<"Lista unazad: ";
    l2.ispisUnazad();
    for(int i=0; i<10; i++)
    {
        std::cout<<l2[i]<<" ";    
    }
    
 
}
