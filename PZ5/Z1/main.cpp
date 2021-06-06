#include <iostream>

int fib2_0(int n, int prvi=0, int drugi=1)
{
    if(n==0) return prvi;
    if(n==1) return drugi;
    return fib2_0(n-1, drugi, drugi+prvi);
}
int nzd(int x, int y)
{
    if(y==0) return x;
    return nzd(y, x%y);
}
double power(double a, unsigned int n)
{
    if(n==0) return 1;
    if(n%2==0)
    {
        return power(a, n/2)*power(a, n/2);
    }
    else
    {
        return a*power(a, n/2)*power(a, n/2);
    }
}
bool daLiJePotencija(int broj, int baza)
{
    if(broj==baza) return true;
    else if(broj%baza==1)return false;
    return daLiJePotencija(broj/baza, baza);
}

int main() {
    std::cout<<fib2_0(6)<<std::endl;
    std::cout<<nzd(4, 8)<<std::endl;
    std::cout<<power(2, 6);
    std::cout<<std::boolalpha<<daLiJePotencija(32, 2);
    
    return 0;
}
