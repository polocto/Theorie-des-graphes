#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include "components/sommet.hpp"

class Graph{
    public:
        // build a graph based on a file
        Graph(const std::filesystem::path file);
        // delete graph and all of its sommets
        ~Graph();

        // parse a graph through its width
        void BFS(const int sommetId);
        //parse a graph through its length
        void DSF(const int sommetId);
        //parse a graph through its length recusivly
        void DSF_R(const int sommetId);
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