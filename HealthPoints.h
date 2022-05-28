#include <ostream>

#ifndef HEALTH_POINTS_MATAM
#define HEALTH_POINTS_MATAM



class HealthPoints{
private:
    int m_currValue;
    int m_maxValue;
    friend bool operator==(const HealthPoints& hp1,const HealthPoints& hp2);
    friend bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);
    friend std::ostream& operator<<(std::ostream& os,const HealthPoints& hp);
    
public:
    HealthPoints(int maxHp = 100);
    HealthPoints(const HealthPoints& hp);
   ~HealthPoints()=default;


    class InvalidArgument{};

    HealthPoints& operator=(const HealthPoints& hp);
    HealthPoints& operator+=(const int hpAdd);
    HealthPoints& operator-=(const int hpSub);

    HealthPoints operator+(const int hpAdd);
    HealthPoints operator-(const int hpAdd);

};


HealthPoints operator+(const int hpAdd,const HealthPoints& hp);
HealthPoints operator-(const int hpAdd,const HealthPoints& hp);


bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator>(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2);

#endif

