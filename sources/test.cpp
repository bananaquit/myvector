
#include <iostream>
#include "mvector.hpp"




int main(int argc, char * argv[]){
    std::cout << "There are " << argc << " arguments: " << argv[0] << '\n';

    /*gm::vector<int> m1{1,2,3,4,5};
    gm::vector<int> m2(m1);
    for(std::size_t i=0; i< 5; i++)
        std::cout << m1[i] << ' ';
    std::cout << '\n';
    for(std::size_t i=0; i< 5; i++)
        std::cout << m2[i] << ' ';*/
    double * ptr{ new double [10]{} };
    gm::vector<double> md (ptr, 10);

    for (size_t i = 0; i < 10; i++)
    {
        md[i] = 3.14*i;
    }

    md = md/21;
    
    
    std::cout << md << '\n';
    std::cout << md.length() << ' ' << md.capacity() << '\n';

    std::cout << "\nHello world!\n";

    return 0;
}