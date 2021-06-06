#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void countSort(std::vector<int> &a, int koeficijent)
{
    std::vector<int>brojac(10, 0);
    for(int i=0; i<a.size(); i++)
    {
        //UZIMAMO SVAKI PUT JEDNU CIFRU BROJA, KRECUCI SE ZDESNA NALIJEVO
        brojac[(a[i]/koeficijent)%10]++;
    }
    for(int i=1; i<10; i++)
    {
        //DOBIJEMO KOLIKO IMA BROJEVA KOJI SU MANJI ILI JEDNAKI DATOM BROJU
        brojac[i]+=brojac[i-1];
    }
    std::vector<int>pomocni(a.size());
    for(int i=a.size()-1; i>=0; i--)
    {
        pomocni[brojac[(a[i]/koeficijent)%10]-1]=a[i];
        brojac[(a[i]/koeficijent)%10]--;
    }
    for(int i=0; i<a.size(); i++)
    {
        a[i]=pomocni[i];
    }
}

void radixSort(std::vector<int> &a)
{
    int max=0;
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]>a[max])
        {
            max=i;
        }
    }
    int najveci=a[max];
    for(int i=1; najveci/i>0; i*=10)
    {
        countSort(a, i);
    }
    
}
bool jeLiList(std::vector<int>&a, int i, int velicina)
{
    return (i>=velicina/2 && i<velicina);
}
void popraviDolje(std::vector<int>&a, int i, int &velicina)
{
    while(!jeLiList(a, i, velicina))
    {
        int veci=2*i+1;
        int dd=2*i+2;
        
        if(dd<velicina && a[dd]>a[veci])
        {
            veci=dd;
        }
        if(a[i]>a[veci]) return;
        int temp=a[i];
        a[i]=a[veci];
        a[veci]=temp;
        i=veci;
    }
}
void popraviGore(std::vector<int>&a, int i)
{
    while(i!=0 and a[i]>a[(i-1)/2])
    {
        std::swap(a[i], a[(i-1)/2]);
        i=(i-1)/2;
    }
}
void stvoriGomilu(std::vector<int> &a)
{
    int velicina=a.size();
    for(int i=velicina/2; i>=0; i--)
    {
        popraviDolje(a, i, velicina);
    }
}
void umetniUGomilu(std::vector<int> &a, int umetnuti, int &velicina)
{
    a.push_back(umetnuti);
    velicina++;
    popraviGore(a, velicina-1);
}
int izbaciPrvi(std::vector<int> &a, int &velicina)
{
    if(velicina==0) throw "Gomila je prazna";
    velicina--;
    std::swap(a[0], a[velicina]);
    if(velicina!=0)
    {
        popraviDolje(a, 0, velicina);
    }
    return a[velicina];
}
void gomilaSort(std::vector<int> &a)
{
    stvoriGomilu(a);
    int velicina=a.size();
    for(int i=0; i<a.size()-1; i++)
    {
        izbaciPrvi(a, velicina);
    }
}
bool gomilaSortTest(std::vector<int>a)
{
    std::vector<int>pom(a);
    gomilaSort(pom);
    std::sort(a.begin(), a.end());
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]!=pom[i])
        {
            std::cout<<"Nije validno!";
            return false;
        }
    }
    std::cout<<"Dobro sortira"<<std::endl;
    return true;
}
bool radixSortTest(std::vector<int>a)
{
    std::vector<int>pom(a);
    radixSort(pom);
    std::sort(a.begin(), a.end());
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]!=pom[i])
        {
            std::cout<<"Nije validno!";
            return false;
        }
    }
    std::cout<<"Dobro sortira"<<std::endl;
    return true;
}
int main() {
    
    std::vector<int>a{99511195, 213, 1, 0, 7987987, 15648, 15, 13, 9};
    radixSortTest(a);
    radixSort(a);
    for(int i=0; i<a.size(); i++) std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    stvoriGomilu(a);
    for(int i=0; i<a.size(); i++) std::cout<<a[i]<<" ";
    std::cout<<std::endl;
    gomilaSortTest(a);
    gomilaSort(a);
    for(int i=0; i<a.size(); i++) std::cout<<a[i]<<" ";
    


    return 0;
}
