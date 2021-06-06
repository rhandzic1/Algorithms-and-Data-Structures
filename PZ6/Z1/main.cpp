#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

template<typename Tip>
void selection_sort(Tip* niz, int vel)
{
    for(int i=0; i<vel-1; i++)
    {
        Tip min=niz[i];
        int pmin=i;
        for(int j=i+1; j<vel; j++)
        {
            if(niz[j]<min)
            {
                min=niz[j];
                pmin=j;
            }
        }
        niz[pmin]=niz[i];
        niz[i]=min;
    }
}
template<typename Tip>
void bubble_sort(Tip* niz, int vel)
{
    for(int i=vel-1; i>=1; i--)
    {
        for(int j=1; j<=i; j++)
        {
            if(niz[j-1]>niz[j])
            {
                Tip temp=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=temp;
            }
        }
    }
}
template<typename Tip>
int particija(Tip* niz, const int prvi, const int zadnji)
{
    Tip pivot=niz[prvi];
    int p=prvi+1;
    while(p<=zadnji)
    {
        if(niz[p]<=pivot) p++;
        else break;
    }
    for(int i=p+1; i<=zadnji; i++)
    {
        if(niz[i]<pivot)
        {
            Tip temp=niz[i];
            niz[i]=niz[p];
            niz[p]=temp;
            p++;
        }
    }
    Tip temp=niz[prvi];
    niz[prvi]=niz[p-1];
    niz[p-1]=temp;
    return p-1;
}
template<typename Tip>
void quick_sort(Tip* niz, int l, int u)
{
    if(l<u)
    {
        int j=particija(niz, l, u);
        quick_sort(niz, l, j-1);
        quick_sort<Tip>(niz, j+1, u);
    }
}
template<typename Tip>
void quick_sort(Tip* niz, int vel)
{
    quick_sort(niz, 0, vel-1);   
}

template<typename Tip>
void merge(Tip* niz, int l, int p, int q, int u)
{
    int i=0;
    int j=q-l;
    int k=l;
    Tip *B=new Tip[u-l+1];
    for(int m=0; m<u-l+1; m++)
    {
        B[m]=niz[l+m];
    }
    while(i<=p-l && j<=u-l)
    {
        if(B[i]<B[j])
        {
            niz[k]=B[i];
            i++;
        }
        else
        {
            niz[k]=B[j];
            j++;
        }
        k++;
    }
    while(i<=p-l)
    {
        niz[k]=B[i];
        k++;
        i++;
    }
    while(j<=u-l)
    {
        niz[k]=B[j];
        k++;
        j++;
    }
    delete[] B;
}
template<typename Tip>
void merge_sort(Tip* niz, int l, int u)
{
    if(u>l)
    {
        int p=(l+u-1)/2;
        int q=p+1;
        merge_sort(niz, l, p);
        merge_sort(niz, q, u);
        merge(niz, l, p, q, u);
        
    }
}
template<typename Tip>
void merge_sort(Tip* niz, int vel)
{
    merge_sort(niz, 0, vel-1);
}
void ucitaj(std::string filename, int*& niz, int& vel)
{
    std::ifstream ulaz(filename);
    if(!ulaz)
    {
        vel=0;
        return;
    }
    std::vector<int>povratni;
    for(;;)
    {
        int pomocna;
        ulaz>>pomocna;
        if(!ulaz) break;
        povratni.push_back(pomocna);
    }
    vel=povratni.size();
    niz=new int[vel];
    for(int i=0; i<vel; i++)
    {
        niz[i]=povratni[i];
    }
}
void generisi(std::string filename, int vel)
{
    std::ofstream izlaz(filename);
    if(!izlaz)
    {
        return;
    }
    for(int i=0; i<vel; i++)
    {
        int random_broj=(rand()%1000);
        izlaz<<random_broj<<" ";
    }
}
void testna_funkcija()
{
    generisi("randomBrojevi.txt", 20);
    int* poc=nullptr; 
    int velicina=0;
    ucitaj("randomBrojevi.txt", poc, velicina);
    std::cout<<"Izaberite algoritam sortiranja: "<<std::endl;
    std::cout<<"1--> Bubble sort"<<"\n"<<"2--> Selection sort"<<"\n"<<
    "3--> Quick sort"<<"\n"<<"4--> Merge sort"<<std::endl;
    int unos;
    std::cin>>unos;
    while(!(unos>0 && unos<5))
    {
        std::cout<<"Greska! Unesite opet: ";
        std::cin>>unos;
    }
    int vrijeme=0;
    switch(unos)
    {
        case 1:
        {
        clock_t v1=clock();
        bubble_sort<int>(poc, velicina);
        clock_t v2=clock();
        vrijeme=(v2-v1)/(CLOCKS_PER_SEC/1000.);
        break;
        }
        
        case 2:
        {
        clock_t v1=clock();
        selection_sort<int>(poc, velicina);
        clock_t v2=clock();
        vrijeme=(v2-v1)/(CLOCKS_PER_SEC/1000.);
        break;
        }
        
        case 3:
        {
        clock_t v1=clock();
        quick_sort<int>(poc, velicina);
        clock_t v2=clock();
        vrijeme=(v2-v1)/(CLOCKS_PER_SEC/1000.);
        break;
        }
            
        case 4:
        {
        clock_t v1=clock();
        merge_sort<int>(poc, velicina);
        clock_t v2=clock();
        vrijeme=(v2-v1)/(CLOCKS_PER_SEC/1000.);
        break;
        }
    }
    std::cout<<"Vrijeme izvrsavanja algoritma je: "<<vrijeme<<" ms."<<std::endl;
    bool provjera=true;
    for(int i=1; i<velicina; i++)
    {
        if(poc[i-1]>poc[i]) 
        {
            provjera=false;
            break;
        }
    }
    if(provjera)
    {
        std::cout<<"Niz je sortiran korektno!"<<std::endl;
    }
    else
    {
        std::cout<<"Niz nije sortiran!"<<std::endl;
    }
    std::ofstream izlaz("sortiranNiz.txt");
    izlaz<<"Sortiran niz: "<<std::endl;
    for(int i=0; i<velicina; i++)
    {
        izlaz<<poc[i]<<" ";
    }
}


int main() 
{
    testna_funkcija();
    return 0;
}
