#include <ostream>

#ifndef HEALTH_POINTS_MATAM
#define HEALTH_POINTS_MATAM



class HealthPoints{
private:

    int m_currValue;
    int m_maxValue;

     /*
     * Compares between two healthPoints objects.
     *
     * @param hp1 - 1st HealthPoints object.
     * @param hp2 - 2nd HealthPoints object.
     * @return
     *      A boolean value.
    */
    friend bool operator==(const HealthPoints& hp1,const HealthPoints& hp2);

     /*
     * Compares between two healthPoints objects
     *
     * @param hp1 - 1st HealthPoints object.
     * @param hp2 - 2nd HealthPoints object.
     * @return
     *      A boolean value.
    */
    friend bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);

     /*
     * Prints out hp.
     *
     * @param os - output channel.
     * @param hp - hp value to print.
     * @return
     *      ostream.
    */
    friend std::ostream& operator<<(std::ostream& os,const HealthPoints& hp);
    
public:

    /*
     * C'tor of HealthPoints
     *
     * @param maxHp - The maximum hp for the hp object.
     * @return
     *      A new instance of HealthPoints.
    */
    HealthPoints(int maxHp = 100);

     /*
     * Copy c'tor of HealthPoints class
     *
     * @param hp - hp Object to duplicate.
     * @return
     *      A new instance of HealthPoints.
    */
    HealthPoints(const HealthPoints& hp);

     /*
     * D'tor of HealthPoints class.
     * Here we are explicitly telling the compiler to use the default methods
     * @return
     *      no return.
    */
   ~HealthPoints()=default;

    HealthPoints& operator=(const HealthPoints& hp);

    class InvalidArgument{};

    /*
    * Standard addition/substraction arithmetic operations.
    * @return
    *      HealthPoints object.
    */
    HealthPoints& operator+=(const int hpAdd);
    HealthPoints& operator-=(const int hpSub);
    HealthPoints operator+(const int hpAdd);
    HealthPoints operator-(const int hpSub); 

};

HealthPoints operator+(const int hpAdd,const HealthPoints& hp);
HealthPoints operator-(const int hpSub,const HealthPoints& hp);



/*
* Standard addition/substraction arithmetic operations.
* @return
*      boolean value.
*/
bool operator!=(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator>(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator<(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator>=(const HealthPoints& hp1,const HealthPoints& hp2);
bool operator<=(const HealthPoints& hp1,const HealthPoints& hp2);

#endif

