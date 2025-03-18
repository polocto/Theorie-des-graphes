#include "sommet.hpp"


Sommet::Sommet(const int id): m_num(id){
    m_marked = false;
};



void Sommet::mark(){
    m_marked=true;
}

bool Sommet::isMarked() const{
    return m_marked;
}


void Sommet::reset(){
    m_marked=false;
}


void Sommet::addNeighbour(Sommet* adj){
    if( adj != NULL && std::find(m_adjacents.begin(),m_adjacents.end(),adj)!=m_adjacents.end()){
        throw std::runtime_error("The added adjacent sommet had allready been added.");
    }
    m_adjacents.push_back(adj);
}



std::ostream& operator<<(std::ostream& out, const Sommet& s){
    out << "id=" << s.m_num << "  Adjacents=";
    for (const Sommet* const a : s.m_adjacents)
        out << a->m_num << " ";
    out << std::endl;
    return out;
}