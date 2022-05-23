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
    m_currValue+= (m_currValue+hpAdd)>m_maxValue? m_maxValue : m_currValue+hpAdd;
    return *this;
}
HealthPoints& HealthPoints::operator-=(const int hpSub) 
{
    m_currValue=(m_currValue-hpSub) < 0 ? 0 : m_currValue-hpSub;
    return *this;
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
HealthPoints& HealthPoints::operator+(const int hpAdd) // Check limits later
{
    m_currValue +=hpAdd;
    return *this;
}
HealthPoints& HealthPoints::operator-(const int hpSub)
{
    m_currValue -= hpSub;
    return *this;
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


