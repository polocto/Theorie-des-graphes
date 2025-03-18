#include "graph.hpp"
#include "components/sommet.hpp"
#include <map>


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

void Graph::reset(){
    for (Sommet* s : m_sommets){
        s->reset();
    }
}


std::map<int,std::vector<const int>> Graph::BFS(const int id){
    std::queue<Sommet*> queue;
    std::map<int,std::vector<const int>> l_pred;
    if (id < 0 || id >= getOrdre()){
        throw std::runtime_error("id requested as first for BFS is out of range");
    }

    queue.push(m_sommets[id]);
    queue.back()->mark();
    l_pred[id]=std::vector<const int>();
    while(!queue.empty()){
        Sommet* sommet = queue.front();

        for(Sommet* s : sommet->unmarkedNeighbourg()){
            queue.push(s);
            s->mark();
            l_pred[s->getId()] = std::vector<const int>(l_pred[sommet->getId()]);
            l_pred[s->getId()].push_back(sommet->getId());
        }
        queue.pop();
    }

    return l_pred;
}

std::map<int,std::vector<const int>> Graph::DSF(const int id){
    std::stack<Sommet*> stack;
    std::map<int,std::vector<const int>> l_pred;
    if (id < 0 || id >= getOrdre()){
        throw std::runtime_error("id requested as first for DSF is out of range");
    }

    stack.push(m_sommets[id]);
    l_pred[id]=std::vector<const int>();
    while(!stack.empty()){
        Sommet* sommet = stack.top();
        stack.pop();

        if(!sommet->isMarked()){
            sommet->mark();
    
            for(Sommet* s : sommet->unmarkedNeighbourg()){
                stack.push(s);
                l_pred[s->getId()] = std::vector<const int>(l_pred[sommet->getId()]);
                l_pred[s->getId()].push_back(sommet->getId());
            }
        }
    }

    return l_pred;
}

std::map<int,std::vector<const int>> Graph::DSF_R(const int id, std::vector<const int> pred){
    std::map<int,std::vector<const int>> l_pred;
    if (id < 0 || id >= getOrdre()){
        throw std::runtime_error("id requested as first for DFS_R is out of range");
    }
    Sommet* sommet = m_sommets[id];
    sommet->mark();
    pred.push_back(sommet->getId());
    for(Sommet* s : sommet->unmarkedNeighbourg()){
        if(!s->isMarked()){
            std::map<int,std::vector<const int>> temp = DSF_R(s->getId(), pred);
            l_pred[s->getId()]=std::vector<const int>(pred);
            l_pred.insert(temp.begin(),temp.end());
        }
    }

    return l_pred;
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