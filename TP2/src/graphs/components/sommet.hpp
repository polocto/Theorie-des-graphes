#ifndef SOMMET_HPP
#define SOMMET_HPP

#include <iostream>

class Sommet{
    public:
        // create a new sommet by passing its id number
        Sommet(const int id);

        // mark the sommet
        void mark();
        // return true if the sommet is marked
        bool isMarked() const;

        // reset all sommet parameters
        void reset();

        // during graph construction only
        void addNeighbour(Sommet* adj);

        // print the sommet override method
        friend std::ostream& operator<<(std::ostream& out, const Sommet& s);

    private:
        // identification number
        const int m_num;

        // set as true if the marked
        bool m_marked;

        // a vector of all adjacent sommet
        std::vector<Sommet*> m_adjacents;
};

#endif