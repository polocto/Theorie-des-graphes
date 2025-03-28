/* code ralis par Mr. Fercoq */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "paths.h"

/// Retourne la norme d'un vecteur : utilisé par le calcule de distance entre stations
inline double norme(double vx, double vy)
{
    return sqrt(vx*vx + vy*vy);
}

/// La classe Station représente un sommet du graphe
/// Les adjacences sont déduites des positions x,y des stations
/// durant le chargement du fichier, en fonction du paramétre
class Station
{
    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Station*> m_adjacents;

        /// Données spécifiques du sommet
        int m_id;        // Indice numérique pour l'affichage
        double m_x, m_y; // Position sur le terrain
        int m_frequence; // Fréquence affectée (ou 0 si pas encore de fréquence)

    public:

        /// La construction se fait directement depuis le fichier ouvert en cours de lecture...
        Station(std::istream& is)
        {
            is >> m_id >> m_x >> m_y;
            if ( is.fail() )
                throw std::runtime_error("Probleme lecture id,x,y d'une station");
            m_frequence = 0;
        }

        /// Méthode de calcul de distance à une autre station (pour déterminer le voisinage)
        double distance(const Station* autre) const
        {
            return norme( autre->m_x - m_x, autre->m_y - m_y  );
        }

        /// Méthode de détermination des stations adjacentes ( distance < dmin )
        void determineAdjacents(const std::vector<Station*>& stations, double dmin)
        {
            for (const Station* s : stations)
                if ( distance(s)<dmin && s!=this )
                    m_adjacents.push_back(s);
        }

        /// Retourne le degré du sommet ( = nombre d'arêtes incidentes = nombre de sommets adjacents )
        int getDegre() const
        {
            return (int)m_adjacents.size();
        }

        /// Retourne la frequence (numéro de fréquence) actuellement affecté à la station
        /// Par convention la valeur 0 indique "pas encore de fréquence affectée"
        int getFrequence() const
        {
            return m_frequence;
        }

        /// Affecte une fréquence à la station
        void setFrequence(int frequence)
        {
            m_frequence = frequence;
        }

        /// Test l'affectation d'une fréquence
        /// retourne vrai si la fréquence n'est pas en conflit avec une station adjacente
        /// faux sinon
        bool testFrequence(int frequence)
        {
            for (const Station* const s : m_adjacents)
                if ( s->m_frequence && s->m_frequence == frequence )
                    return false;

            return true;
        }

        /// Surcharge de l'opérateur d'insertion vers un flot de sortie
        /// c'est la "méthode d'affichage" des objets de type Station
        friend std::ostream& operator<<(std::ostream& out, const Station& s)
        {
            out << "id=" << std::setw(2) << s.m_id << "  x=" << s.m_x << "  y=" << s.m_y << "  freq=" << s.m_frequence << "  Adjacents=";
            for (const Station* const a : s.m_adjacents)
                out << a->m_id << " ";
            out << std::endl;
            return out;
        }

};

/// La classe Reseau représente un graphe dans son ensemble
class Reseau
{
    private:
        /// Le rseau est constitué d'une collection de stations
        std::vector<Station*> m_stations;

    public:
        /// La construction du réseau se fait à partir d'un fichier
        /// dont le nom est passé en paramètre
        Reseau(const std::string nomFichier)
        {
            std::ifstream ifs(nomFichier);
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

            double dmin;
            ifs >> dmin;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture dmin entre stations");

            int ordre;
            ifs >> ordre;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");

            for (int i=0; i<ordre; ++i)
                m_stations.push_back( new Station(ifs) );

            for (Station* s : m_stations)
                s->determineAdjacents(m_stations, dmin);
        }

        /// Destructeur du réseau. Les stations ont été alloues dynamiquement
        /// lors de la création d'une instance reseau, le réseau est responsable de leur libération
        ~Reseau()
        {
            for (Station* s : m_stations)
                delete s;
        }

        /// Retourne l'odre du graphe (ordre = nombre de sommets)
        int getOrdre() const
        {
            return (int)m_stations.size();
        }

        /// Remet toutes les fréquences des stations à 0 (non affectes)
        void resetFrequences()
        {
            for (Station* s : m_stations)
                s->setFrequence(0);
        }

        /// Surcharge de l'oprateur d'insertion vers un flot de sortie
        /// c'est la "méthode d'affichage" des objets de type Reseau
        friend std::ostream& operator<<(std::ostream& out, const Reseau& r)
        {
            out << "Reseau d'ordre " << r.getOrdre() << " :" << std::endl;
            for (const Station* const s : r.m_stations)
                out << *s;
            out << std::endl;
            return out;
        }

        /// ************* CODE ETUDIANT *************
        void attribuerNaif(int& nbFrequences)
        {
           for(Station* s : m_stations){
            int frequence = 0;
            do{
                frequence++;
            }while(!s->testFrequence(frequence));
            s->setFrequence(frequence);
            if(frequence>nbFrequences){
                nbFrequences=frequence;
            }
           }
        }

        void attribuerWelshPowell(int& nbFrequences)
        {
           std::sort(m_stations.begin(),m_stations.end(),[](Station* a,Station* b){return a->getDegre() < b->getDegre();});

           int colored = 0;
           int frequence = 0;
            while(colored!=m_stations.size()){
                frequence++;
                for(Station* s:m_stations){
                    if(s->getFrequence()==0 && s->testFrequence(frequence)){
                        s->setFrequence(frequence);
                        colored++;
                    }
                }
           }
           nbFrequences=frequence;
        }
        /// ************* FIN CODE ETUDIANT *************

        /// Méthode "optimale", dtermination du nombre chromatique.
        /// Voir implmentation après le main
        void attribuerSystematique(int& nbFrequences);
};


int main(int argc, char* argv[])
{
    // définition d'un fichier par défaut
    std::filesystem::path file= argc > 1 ? argv[1] : "../reseau3.txt"; 

    try
    {
        /// Chargement du réseau et affichage avant coloration
        Reseau reseau(file);
        std::cout << reseau;

        /// Coloration algorithme "naïf" et affichage
        int nbFreqNaif=0;
        reseau.attribuerNaif(nbFreqNaif);
        std::cout << "Naif : " << nbFreqNaif << " frequences utilisees" << std::endl;
        std::cout << reseau;

        reseau.resetFrequences();

        /// Coloration algorithme "Welsh et Powell" et affichage
        int nbFreqWP=0;
        reseau.attribuerWelshPowell(nbFreqWP);
        std::cout << "Welsh & Powell : " << nbFreqWP << " frequences utilisees" << std::endl;
        std::cout << reseau;

        reseau.resetFrequences();
        /// Coloration algorithme "Systmatique" et affichage
        int nbFreqSyst=0;
        reseau.attribuerSystematique(nbFreqSyst);
        std::cout << "Nombre chromatique : " << nbFreqSyst << " frequences utilisees (optimal)" << std::endl;
        std::cout << reseau;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Attention : " << e.what() << std::endl;
    }

    return 0;
}



/// L'algorithme suivant trouve une colloration
/// en essayant systmatiquement toutes les combinaisons
/// d'affectations avec 1 couleur, puis 2 couleurs, puis 3 ...
/// Cet algorithme garantit donc une meilleure coloration
/// ( nombre de couleur utilises = nombre chromatique )
/// mais il prsente un grave inconvnient... Lequel ?
void Reseau::attribuerSystematique(int& nbFrequences)
{
    nbFrequences = 0;

    // Pour chaque nombre de fréquences à utiliser
    while ( true )
    {
        ++nbFrequences;

        // On va tester les "nbFrequences puissance ordre" combinaisons
        // Exemple : pour répartir 3 couleurs sur 4 sommets il y a 3^4 = 81 cas à étudier
        // Ceci est quivalent à un comptage en base 3 sur 4 chiffres : 0000 0001 0002 0010 0011 0012 0020 ...
        // On va tester les affectations correspondantes              : 1111 1112 1113 1121 1122 1123 1131 ...
        int nbCas = std::pow(nbFrequences, getOrdre());
        for (int k=0; k<nbCas; ++k)
        {
            // On va tester l'affectation de nbFrequences correspondant au k tudi
            resetFrequences();
            int nbAffecte = 0;
            int combi = k;
            // dcomposition de l'entier k en base nbFrequences et affectations correspondante
            for (Station* s : m_stations)
            {
                // Rcupration du chiffre suivant en base nbFrequences, +1 pour viter le 0 (0 => pas encore de frquence)
                int freq = combi%nbFrequences + 1;
                // Si on trouve une incompatibilit dans l'affectation alors on va passer au k suivant
                // en sortant de la boucle d'affection des sommets du k actuel
                if ( !s->testFrequence(freq) )
                    break;
                // Sinon l'affectation de ce sommet est pour l'instant possible...
                s->setFrequence(freq);
                ++nbAffecte;
                // Prparation de l'extraction du chiffre suivant en base nbFrequences
                combi /= nbFrequences;
            }

            // Tous les sommets sont affects : c'est gangn on a bien une affectation globale optimale !
            if ( nbAffecte == getOrdre() )
                return;
        }
    }
}
