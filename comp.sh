

#g++ -Wall -Wextra -pedantic-errors -c sources/mvector.cpp -o build/mvector.o
#g++ -Wall -Wextra -pedantic-errors sources/test.cpp build/mvector.o -o build/a
g++ -Wall -Wextra -pedantic-errors -std=c++17 sources/test.cpp -o build/a

./build/a
