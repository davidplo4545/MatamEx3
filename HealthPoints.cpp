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
    if(m_currValue + hpAdd > m_maxValue)
    {
        m_currValue = m_maxValue;
    }
    else if(m_currValue+hpAdd < 0)
    {
        m_currValue = 0;
    }
    else
    {
        m_currValue = m_currValue + hpAdd;
    }
    return *this;
}
HealthPoints& HealthPoints::operator-=(const int hpSub) 
{
    if(m_currValue - hpSub > m_maxValue)
    {
        m_currValue = m_maxValue;
    }
    else if(m_currValue-hpSub < 0)
    {
        m_currValue = 0;
    }
    else
    {
        m_currValue = m_currValue - hpSub;
    }
    return *this;
}

HealthPoints& HealthPoints::operator=(const HealthPoints& hp) 
{
    m_currValue=hp.m_currValue;
    m_maxValue=hp.m_maxValue;
    return *this;
}

HealthPoints HealthPoints::operator+(const int hpAdd) // Check limits later
{
    HealthPoints result = *this;
    result+=hpAdd;
    return result;
}
HealthPoints HealthPoints::operator-(const int hpSub)
{
    HealthPoints result = *this;
    result-=hpSub;
    return result;
}

HealthPoints operator+(const int hpAdd, const HealthPoints& hp)
{
    HealthPoints result = hp;
    result+=hpAdd;
    return result;
}

HealthPoints operator-(const int hpSub, const HealthPoints& hp) // Check limits later
{
    HealthPoints result = hp;
    result-=hpSub;
    return result;
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


