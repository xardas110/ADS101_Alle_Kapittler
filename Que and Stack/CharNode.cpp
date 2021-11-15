// ADS101 Algoritmer og datastrukturer H2017-2020

#include <string>
#include <sstream>
#include <iostream>
#include "charnode.h"

namespace ADS101 {
int CharNode::s_antall;

CharNode::CharNode(char tegn, CharNode* neste)
    : m_tegn(tegn), m_neste(neste)
{
    //m_tegn = tegn;
    s_antall ++;
}

std::string CharNode::toString() const
{
    std::ostringstream oss;
    oss << m_tegn;
    return oss.str();
}

CharNode* CharNode::hentNeste() const
{
    return m_neste;
}
void CharNode::skrivBaklengs() const
{
    if (m_neste)
        m_neste->skrivBaklengs();           // Main: liste->skrivBaklengs();
    std::cout << m_tegn;
}
int CharNode::hentAntall()
{
    return s_antall;
}

CharNode::~CharNode()
{
    s_antall --;
}

char CharNode::hentData() const
{
    return m_tegn;
}
}
