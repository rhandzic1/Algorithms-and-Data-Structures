#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

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
        int balans; //IZMJENA
    };

template<typename Tip1, typename Tip2>
class AVLStabloMapa: public Mapa<Tip1, Tip2>
{
private:
    int broj_elemanata;
    Cvor<Tip1, Tip2>* korijen;
    Cvor<Tip1, Tip2>* trazi(Cvor<Tip1, Tip2>* r, const Tip1& k);
    void brisi(Cvor<Tip1, Tip2>* r);
    bool brisiCvor(Cvor<Tip1, Tip2>* &r, const Tip1& k);
    void kopiraj(Cvor<Tip1, Tip2>* original, Cvor<Tip1, Tip2>* &kopija, Cvor<Tip1, Tip2>* roditelj);
    void azurirajBalans(Cvor<Tip1, Tip2>* cv);
    void rotirajUdesno(Cvor<Tip1, Tip2>* cv);
    void rotirajUlijevo(Cvor<Tip1, Tip2>* cv);
public:
    ~AVLStabloMapa();
    AVLStabloMapa();
    Tip2& operator[](Tip1 kljuc) override;
    Tip2 operator[](Tip1 kljuc) const override;
    int brojElemenata() override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Tip1& kljuc) override;
    AVLStabloMapa(const AVLStabloMapa &r);
    AVLStabloMapa& operator=(const AVLStabloMapa &r);
};

template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::kopiraj(Cvor<Tip1, Tip2>* original, Cvor<Tip1, Tip2>* &kopija, Cvor<Tip1, Tip2>* roditelj)
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
AVLStabloMapa<Tip1, Tip2>::AVLStabloMapa(const AVLStabloMapa &r)
{
    broj_elemanata=r.broj_elemanata;
    kopiraj(r.korijen, korijen, nullptr);
}
template<typename Tip1, typename Tip2>
AVLStabloMapa<Tip1, Tip2>& AVLStabloMapa<Tip1, Tip2>::operator=(const AVLStabloMapa &r)
{
    if(&r==this) return *this;
    this->obrisi();
    broj_elemanata=r.broj_elemanata;
    
    kopiraj(r.korijen, this->korijen, nullptr);
    return *this;
    
    
}

template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::rotirajUlijevo(Cvor<Tip1, Tip2>* cv)
{
    if(cv->balans<0 && cv->desni->balans>0)
    {
        rotirajUdesno(cv->desni);
    }
    Cvor<Tip1, Tip2>* pom=cv->desni;
    Cvor<Tip1, Tip2>* pom_r=cv->roditelj;
    if(pom_r==nullptr)
    {
        korijen=cv;
    }
    else if(pom_r->desni==cv) 
    {  
        pom_r->desni=pom;
    }
    else
    {
        pom_r->lijevi=pom;
    }
    cv->desni=nullptr;
    cv->roditelj=pom;
    pom->lijevi=cv;
    pom->roditelj=pom_r;
    pom->balans=0;
    cv->balans=0;
    
    
}

template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::rotirajUdesno(Cvor<Tip1, Tip2>* cv)
{
    if(cv->balans>0 && cv->lijevi->balans<0)
    {
        rotirajUlijevo(cv->lijevi);
    }
    Cvor<Tip1, Tip2>* pom=cv->lijevi;
    Cvor<Tip1, Tip2>* pom_r=cv->roditelj;
    if(pom_r==nullptr)
    {
        korijen=cv;
    }
    else if(pom_r->desni==cv)
    {
        pom_r->desni=pom;
    }
    else
    {
        pom_r->lijevi=pom;        
    }
    
    cv->lijevi=nullptr;
    cv->roditelj=pom;
    pom->desni=cv;
    pom->roditelj=pom_r;
    pom->balans=0;
    cv->balans=0;
}


template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::azurirajBalans(Cvor<Tip1, Tip2>* cv)
{
    if(cv->roditelj==nullptr) return;
    Cvor<Tip1, Tip2>* temp=cv->roditelj;
    if(temp->lijevi==cv)
    {
        temp->balans++;
    }
    else if(temp->desni==cv)
    {
        temp->balans--;
    }
    if(temp->balans==0) return;
    if(temp->balans>1)
    {
        rotirajUdesno(temp);
    }
        //LIJEVA
    else if(temp->balans<-1)
    {
        rotirajUlijevo(temp);
    }
    else azurirajBalans(temp);
}

template<typename Tip1, typename Tip2>
bool AVLStabloMapa<Tip1, Tip2>::brisiCvor(Cvor<Tip1, Tip2>* &r, const Tip1& k)
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
    else if(p==q->lijevi)
    {
        q->lijevi=rp;
        q->balans--; //IZMJENA
    }
    else
    {
        q->desni=rp;
        q->balans++; //IZMJENA
    }
    delete p;
    return true;
}
template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::brisi(Cvor<Tip1, Tip2>* r)
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
Cvor<Tip1, Tip2>* AVLStabloMapa<Tip1, Tip2>::trazi(Cvor<Tip1, Tip2>* r, const Tip1& k)
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
AVLStabloMapa<Tip1, Tip2>::~AVLStabloMapa()
{
    brisi(korijen);
    broj_elemanata=0;
}

template<typename Tip1, typename Tip2>
AVLStabloMapa<Tip1, Tip2>::AVLStabloMapa()
{
    broj_elemanata=0;
    korijen=nullptr;
}

template<typename Tip1, typename Tip2>
Tip2& AVLStabloMapa<Tip1, Tip2>::operator[](Tip1 kljuc)
{
    //Glavna modifikacija u odnosu na binarno stablo je ta da sam koristio
    //kod funkcije trazi u operatoru [], ali sa modifikacijom da se pokazivac prije_p
    //trazi u njoj, tako da je dodavanje smanjeno sa O(log(n)*log(n)) na O(log(n)) 
    Cvor<Tip1, Tip2>* poc=korijen;
    Cvor<Tip1, Tip2>* prije_p=korijen;
    while(poc!=nullptr && poc->kljuc!=kljuc)
    {
        prije_p=poc;
        if(kljuc<poc->kljuc)
        {
            poc=poc->lijevi;
        }
        else
        poc=poc->desni;
    }
    if(poc==nullptr)
    {
       Cvor<Tip1, Tip2>*a=new Cvor<Tip1, Tip2>{nullptr, nullptr, prije_p, kljuc, Tip2(), 0};
        
        if(prije_p==nullptr)
        {
            korijen=a;
            broj_elemanata++;
            return korijen->vrijednost;
        }
        
        else if(kljuc<prije_p->kljuc)
        {
            prije_p->lijevi=a;
            prije_p->balans--;
        }
        else
        {
            prije_p->desni=a;
            prije_p->balans++;
        }

       if(prije_p->lijevi!=nullptr && prije_p->desni!=nullptr)
        {
            prije_p->balans=0;
        }
        else
        {
            azurirajBalans(a);
        }
        broj_elemanata++;
        return a->vrijednost;
    }
    return poc->vrijednost;
}

template<typename Tip1, typename Tip2>
Tip2 AVLStabloMapa<Tip1, Tip2>::operator[](Tip1 kljuc) const
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
int AVLStabloMapa<Tip1, Tip2>::brojElemenata()
{
    return broj_elemanata;
}

template<typename Tip1, typename Tip2>
int AVLStabloMapa<Tip1, Tip2>::brojElemenata() const
{
    return broj_elemanata;
}

template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::obrisi()
{
    brisi(korijen);
    korijen=nullptr;
    broj_elemanata=0;
}

template<typename Tip1, typename Tip2>
void AVLStabloMapa<Tip1, Tip2>::obrisi(const Tip1& kljuc) 
{
    brisiCvor(korijen, kljuc);
    if(broj_elemanata>0)
    broj_elemanata--;
}
int main()
{
AVLStabloMapa <int, int> m;
int vel(500000);
int progress(1000);
for (int i(0); i<vel; i++) {
    m[i] = i;
    if (i==progress) { 
       cout<<"Dodano "<<i<<endl;
       progress *= 2;
    }
}
// Obicno bin. stablo ce uspjeti dodati oko 30000-70000 el. za 10 sekundi
// Korektno AVL stablo ce zavrsiti kompletan test za <1 sekundu

for (int i(0); i>=-vel; i--)
    m[i] = i;
for (int i(-vel); i<vel; i++)
    if (m[i] != i) { cout << i << " NOT OK"; break; }
for (int i(-vel); i<vel; i++)
    m.obrisi(i);
cout << "OK";
return 0;
}
