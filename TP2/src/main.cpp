#include <iostream>
#include "graphs/graph.hpp"

int main(int argc, char* argv[]){
    Graph* reseau = new Graph("../reseau.txt");
    std::cout << *reseau << std::endl;
    return 0;
}