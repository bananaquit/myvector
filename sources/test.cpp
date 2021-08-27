
#include <iostream>
#include <type_traits>
#include "mvector.hpp"

template<typename T>
void test_arithmetic(){
    const T * const ptr {new T [10] {-1,1,2,3,4,5,6,7,8,9}};
    gm::vector<T> v1(ptr, 10);

    gm::vector<T> v2(10, 7);


    std::cout << "v1 = " << v1 << '\n'
              << "v2 = " << v2 << "\n\n";

    std::cout << "v1 + v2: "<< (v1 + v2) << '\n';
    std::cout << "v1 - v2: "<< (v1 - v2) << '\n';
    std::cout << "v1 * v2: "<< (v1 * v2) << '\n';
    std::cout << "v1 / v2: "<< (v1 / v2) << '\n';
    if constexpr (std::is_integral_v<T>){
        std::cout << "v1 % v2: "<< (v1 % v2) << "\n\n";
    }
    
    std::cout << "v2 + 7: " << (v2 + 7) << '\n';
    std::cout << "7 + v2: " << (v2 + 7) << '\n';
    std::cout << "v2 - 7: " << (v2 - 7) << '\n';
    std::cout << "7 - v2: " << (v2 - 7) << '\n';
    std::cout << "v2 * 7: " << (v2 * 7) << '\n';
    std::cout << "7 * v2: " << (v2 * 7) << '\n';
    std::cout << "v2 / 7: " << (v2 / 7) << '\n';
    std::cout << "7 / v2: " << (v2 / 7) << '\n';
    if constexpr(std::is_integral_v<T>){
        std::cout << "v2 % 7: " << (v2 % 7) << '\n';
        std::cout << "7 % v2: " << (v2 % 7) << "\n\n";
    }
    
    if constexpr(std::is_integral_v<T>){
        v1 += v1;
        std::cout << "v1 = " << v1 << '\n';
        v1 -= v1 + 1;
        std::cout << "v1 = " << v1 << '\n';
        v1 *= v1;
        std::cout << "v1 = " << v1 << '\n';
        v1 /= v2;
        std::cout << "v1 = " << v1 << '\n';
        v1 %= v1 + 1;
        std::cout << "v1 = " << v1 << '\n';
    }
}


int main(int argc, char * argv[]){
    

    test_arithmetic<std::double_t>();

    std::cout << "\nHello world!\n";

    return 0;
}