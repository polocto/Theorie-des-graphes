#include <iostream>
#include <map>
#include "graphs/graph.hpp"

int main(int argc, char* argv[]){

    // définition d'un fichier par défaut
    std::filesystem::path file= argc > 1 ? argv[1] : "../reseau.txt"; 
    try{
        Graph* reseau = new Graph(file);
        std::cout << *reseau << std::endl;

        reseau->reset();
        std::map<int,std::vector<const int>> l_pred = reseau->BFS(3);
        std::cout<<"BFS"<<std::endl;
        for(int i=0; i<reseau->getOrdre();i++){
            std::cout<< i << ":\t";
            for(const int id: l_pred[i]){
                std::cout<< id <<"\t";
            }
            std::cout<<std::endl;
        }
        reseau->reset();
        l_pred = reseau->DSF(3);
        std::cout<<"DFS"<<std::endl;
        for(int i=0; i<reseau->getOrdre();i++){
            std::cout<< i << ":\t";
            for(const int id: l_pred[i]){
                std::cout<< id <<"\t";
            }
            std::cout<<std::endl;
        }
        reseau->reset();
        l_pred = reseau->DSF_R(3,std::vector<const int>());
        std::cout<<"DFS"<<std::endl;
        for(int i=0; i<reseau->getOrdre();i++){
            std::cout<< i << ":\t";
            for(const int id: l_pred[i]){
                std::cout<< id <<"\t";
            }
            std::cout<<std::endl;
        }
    }catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }
    return 0;
}