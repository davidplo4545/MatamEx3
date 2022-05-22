#include "HealthPoints.h"
using std::ostream;

HealthPoints::HealthPoints(int maxHp)
{
    if (maxHp<=0)
    {
        throw HealthPoints::InvalidArgument();
    }
    m_currValue=maxHp;
    m_maxValue=maxHp;
}
HealthPoints::HealthPoints(const HealthPoints& hp)
{
    m_currValue=hp.m_currValue;
    m_maxValue=hp.m_maxValue;
}

HealthPoints& HealthPoints::operator+=(const int hpAdd) 
{
    m_currValue+=hpAdd;
}
HealthPoints& HealthPoints::operator-=(const int hpSub) // do not let the substractiongo below zero/max
{
    m_currValue-=hpSub;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& hp) 
{
    m_currValue=hp.m_currValue;
    m_maxValue=hp.m_maxValue;
    return *this;
}
HealthPoints operator+(const int hpAdd, HealthPoints& hp)
{
    hp+=hpAdd;
    return hp;
}
HealthPoints operator-(const int hpSub, HealthPoints& hp) // Check limits later
{
    hp-=hpSub;
    return hp;
}
HealthPoints operator+(HealthPoints& hp ,const int hpAdd) // Check limits later
{
    return hpAdd + hp;
}
HealthPoints operator-(HealthPoints& hp, const int hpSub)
{
    return hpSub - hp;
}


bool operator==(const HealthPoints& hp1,const HealthPoints& hp2)
{
        return hp1.m_currValue == hp2.m_currValue;
}
bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return !(hp1==hp2);
}
bool operator>(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return !(hp1 < hp2) && !(hp1 == hp2);
}
bool operator<(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return hp1.m_currValue < hp2.m_currValue;
}
bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2)
{
    return !(hp1<hp2);
}
bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2) 
{
    return !(hp1>hp2);
}
 
ostream& operator<<(ostream& os, const HealthPoints& hp)
{
    os << hp.m_currValue << "(" << hp.m_maxValue << ")";
    return os;
}


