#include <iostream>
#include <utility>
#include <vector>

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

void test1()
{
    NizMapa<std::string, int>m;
    m["Sarajevo"]=1;
    m["Mostar"]=2;
    m["Tuzla"]=3;
    m["Bihac"]=4;
    std::cout<<m.brojElemenata()<<std::endl;
    std::cout<<m["Gorazde"]<<std::endl;
    std::cout<<m.brojElemenata()<<std::endl;
}
void test2()
{
    Mapa<int, int>* m=new NizMapa<int, int>;
    for(int i=0; i<10; i++)
    {
        (*m)[i]=i+1;
    }
    for(int i=0; i<10; i++)
    {
        std::cout<<(*m)[i]<<" ";
    }
}
void test3()
{
    NizMapa<int, std::string>m;
    for(int i=0; i<10; i++)
    {
        m[i]=i+1;
    }
    std::cout<<"Trenutni broj elemenata je: "<<m.brojElemenata()<<std::endl;
    m.obrisi(0);
    m.obrisi(1);
    std::cout<<"Trenutni broj elemenata je: "<<m.brojElemenata()<<std::endl;
    m.obrisi();
    std::cout<<"Broj elemenata nakon brisanja je: "<<m.brojElemenata()<<std::endl;
}
void test4()
{
    NizMapa<int, double>m;
    for(int i=0; i<10; i++)
    {
        m[i]=i+1;
    }
    for(int i=0; i<10; i++)
    {
        std::cout<<m[i]<<" ";
    }
    std::cout<<std::endl;
    const NizMapa<int, double>m2=m;
    for(int i=0; i<m2.brojElemenata(); i++)
    {
        std::cout<<m2[i]<<" ";
    }
}
void test5()
{
    std::vector<std::string>pom={"plava","crvena","zuta","zelena","bijela"};
    NizMapa<int, std::vector<std::string>>m;
    m[0]=pom;
    pom={"januar","februar","mart","april","maj"};
    m[1]=pom;
    for(int i=0; i<m.brojElemenata(); i++)
    {
        for(int j=0; j<m[i].size(); j++)
        {
            std::cout<<m[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    m.obrisi();
    std::cout<<"Broj elemenata nakon brisanja je: "<<m.brojElemenata()<<std::endl;
}
int main() 
{
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}
