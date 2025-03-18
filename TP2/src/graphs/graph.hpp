#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <map>
#include "components/sommet.hpp"

class Graph{
    public:
        // build a graph based on a file
        Graph(const std::filesystem::path file);
        // delete graph and all of its sommets
        ~Graph();

        void reset();

        // parse a graph through its width
        std::map<int,std::vector<const int>> BFS(const int sommetId);
        //parse a graph through its length
        std::map<int,std::vector<const int>> DSF(const int sommetId);
        //parse a graph through its length recusivly
        std::map<int,std::vector<const int>> DSF_R(const int id, std::vector<const int> pred);
        // affiche les composantes connexes d'un graph
        void composantesConnexes();
        // retourne vrai si le graph et non orienté et possède un cycle ou chaîne eulerienne
        bool euler();
        // Ordre du graph
        const int getOrdre() const;

        // print the graph override method
        friend std::ostream& operator<<(std::ostream& out, const Graph& g);

    private:
        std::vector<Sommet*> m_sommets;
        bool m_isOriented;
};

#endif