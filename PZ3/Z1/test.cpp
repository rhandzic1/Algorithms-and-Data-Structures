#include <iostream>
#include <vector>

std::vector<double> generisiPodnizove(std::vector<double>v)
{
    if (v.size() == 2) return v;
    std::vector<std::vector<double>>povratni;
    std::vector<double>pomocni;
    for (int i = 1; i < v.size()-1; i++)
    {
        int donjaGranica = i, gornjaGranica = v.size() - i - 1;
        int offset=donjaGranica;
        if (donjaGranica > gornjaGranica)
        {
            offset = gornjaGranica;
        }
        std::cout << "Offset: " << offset << std::endl;
        for (int j = i - offset; j <= i + offset; j++)
        {
            std::cout << v[j] << " ";
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::vector<double>niz{1,2,3,4,5,6,7,8,9};
    generisiPodnizove(niz);


}