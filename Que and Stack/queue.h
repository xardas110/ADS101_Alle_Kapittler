// ADS101 Algoritmer og datastrukturer 180903
#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

namespace ADS101 {

template <class T>
class queue
{
private:
    Node<T>* m_front;
    Node<T>* m_bak;

public:
    queue();
    void push(T data);
    T front() const;
    void pop();
    int size();
};

template <class T>
queue<T>::queue()
{
    m_front = m_bak = nullptr;
}

template <class T>
void queue<T>::push(T data)
{
    Node<T>* ny = new Node<T>(data);
    if (m_bak)
        m_bak->settNeste(ny);
    m_bak = ny;

    if (m_front == nullptr)
        m_front = m_bak;
}

template <class T>
void queue<T>::pop()
{
    if (m_front != nullptr)
    {
        Node<T>* ut = m_front;
        m_front = m_front->hentNeste();
        delete ut;
    }
    // Hvis vi sletter siste node, blir
    // m_bak en dingle-peker :-(
    if (m_front == nullptr)
        m_bak = nullptr;
}

template <class T>
T queue<T>::front() const
{
    return m_front->hentData();
}

template <class T>
int queue<T>::size() { return m_front->hentAntall(); }
}
#endif // QUEUE_H
