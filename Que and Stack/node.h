// ADS101 170829
// Omskriving av CharNode klassen til template klasse
#ifndef NODE_H
#define NODE_H

namespace ADS101 {

template <class T>
class Node
{
public:
    Node(T tegn, Node* neste=nullptr);
    Node<T>* hentNeste() const;
    void settNeste(Node<T>* neste);
    static int hentAntall();
    T hentData() const;
    ~Node();
private:
    T m_tegn;            // Data-del
    static int s_antall;
    Node<T>* m_neste;      // Datastruktur-del
};

template <class T>
int Node<T>::s_antall;

template <class T>
Node<T>::Node(T tegn, Node<T>* neste)
    : m_tegn(tegn), m_neste(neste)
{
    s_antall ++;
}

template <class T>
Node<T>* Node<T>::hentNeste() const { return m_neste; }

template <class T>
void Node<T>::settNeste(Node<T>* neste) { m_neste = neste; }

template <class T>
int Node<T>::hentAntall() { return s_antall; }

template <class T>
Node<T>::~Node() { s_antall --; }

template <class T>
T Node<T>::hentData() const { return m_tegn; }
}

#endif // TNODE_H
