#include "graph.hpp"
#include "components/sommet.hpp"


Graph::Graph(const std::filesystem::path file){
    std::ifstream ifs(file);
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + file.string() );

    bool oriented;
    ifs >> oriented;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture dmin entre stations");
    m_isOriented = oriented;
    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int taille;
    ifs >> taille;

    for (int i=0; i<ordre; ++i)
        m_sommets.push_back( new Sommet(i) );

    for(int i=0; i<taille; i++){
        int id1, id2;
        ifs >> id1 >> id2;
        m_sommets[id1]->addNeighbour(m_sommets[id2]);
        if(!oriented){
            m_sommets[id2]->addNeighbour(m_sommets[id1]);
        }
    }
}

Graph::~Graph(){
    for(Sommet* s: m_sommets){
        delete s;
    }
}


void Graph::BFS(const int id){

}

void Graph::DSF(const int id){

}

void Graph::DSF_R(const int id){

}

const int Graph::getOrdre() const{
    return m_sommets.size();
}

void Graph::composantesConnexes(){

}

std::ostream& operator<<(std::ostream& out, const Graph& g){
    if(g.m_isOriented){
        out << "Reseau orienté" << std::endl;
    }else{
        out << "Reseau non orienté" << std::endl;
    }
    out << "Reseau d'ordre " << g.getOrdre() << " :" << std::endl;
    for (const Sommet* const s : g.m_sommets)
        out << *s;
    out << std::endl;
    return out;
}