#include <new>
#ifndef QUEUE_MATAM
#define QUEUE_MATAM

template<class T>
class Queue
{
private:
    T* m_data;
    int m_size;
	int m_maxSize;
	static const int HEAD=0;
    static const int EXPAND_RATE = 2;
    static const int INITIAL_SIZE = 10;

    /*
    * Increases the size of the queue.
    *
    * @return
    *      void.
    */
    void expand();


public:
    Queue(); // constructor
    Queue(const Queue& queue); // copy constructor
    ~Queue(); // D'tor of Queue class

    Queue& operator=(const Queue& queue); // assignment operator

    /*
    * Pushes a new item to the queue.
    *
    * @param newItem - A new item to add.
    * @return
    *      void.
    */
    void pushBack(const T& newItem);

    /*
    * Gets the first item pushed in the queue.
    *
    * @return
    *      A Template object.
    */
    T& front() const;

    /*
    * Removes the first item inside the queue.
    *
    * @return
    *      void.
    */
    void popFront();

    /*
    * Returns the queue length.
    *
    * @return
    *      The size of the queue.
    */
    int size() const;

    // Iterator functions
    class Iterator;
    Iterator begin();
    Iterator end();

    // Const Iterator functions
    class ConstIterator;
    const ConstIterator begin() const;
    const ConstIterator end() const;

    class EmptyQueue{};
};



template<class T>
Queue<T>::Queue(): m_data(new T[INITIAL_SIZE]), m_size(0),m_maxSize(INITIAL_SIZE){}

template<class T>
Queue<T>::Queue(const Queue<T>& queue): 
    m_data(new T[queue.size()]),
    m_size(queue.size()),
    m_maxSize(queue.size())
    {
        try
        {
            for(int i=0; i< queue.size();i++)
            {
                m_data[i]=queue.m_data[i];
            }
        }
        catch(const std::bad_alloc&)
        {
            delete []m_data;
            throw;
        }
    
    }

template<class T>
Queue<T>::~Queue()
{
    delete [] m_data;
}

template<class T>
void Queue<T>::expand()
{
    int newMaxSize=m_maxSize*EXPAND_RATE;
    T* tempData = new T[newMaxSize];
    try
    {
        for (int i=0; i<m_size; i++)
        {
            tempData[i] = m_data[i];
        }
    }
    catch(const std::bad_alloc&)
    {
        delete []tempData;
        throw;
    }
    delete [] m_data;
    m_maxSize = newMaxSize;
    m_data = tempData;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& queue)
{
    if (this == &queue)
    {
        return *this;
    }
    T* tempData = new T[queue.size()];
    try
    {
        for(int i=0; i< queue.size(); i++)
        {
            tempData[i] = queue.m_data[i];
        }
    }
    catch(const std::bad_alloc&)
    {
        delete []tempData;
        throw;
    }
    
    delete[] m_data;
    m_data = tempData;
    m_size = queue.m_size;
    m_maxSize = queue.m_maxSize;
    return *this;
}




template<class T>
int Queue<T>::size() const
{
    return m_size;
}

template<class T>
void Queue<T>::pushBack(const T& newItem)
{
     if (m_size==m_maxSize)
     {
        this->expand();
     }
     m_data[m_size] = newItem;
     m_size++;
}

template<class T>
T& Queue<T>::front() const
{
    if(m_size<=0)
    {
        throw EmptyQueue();
    }

    return m_data[HEAD];
}

template<class T>
void Queue<T>::popFront()
{
    if(m_size<=0)
    {
        throw EmptyQueue();
    }

    for (int i=1; i<m_size; i++)
    {
        m_data[i-1]=m_data[i];
    }
    m_size--;
}


/*
* Filters the queue by a given function object/pointer.
*
* @param queue - A queue to filter.
* @param filterCondition - A Function Object/Pointer
* @return
*      A new queue with the filtered values.
*/
template<class T,class Condition>
Queue<T> filter(const Queue<T>& queue, Condition filterCondition) 
{
    Queue<T> filtered = Queue<T>();
    for(const T item: queue)
    {
        if(filterCondition(item))
        {
            filtered.pushBack(item);
        }
    }
    return filtered;
}

/*
* Maps the queue values and changes them by a given function.
*
* @param queue - A queue to filter.
* @param applyFunc - A Function Object/Pointer
* @return
*      void.
*/
template<class T, class Apply>
void transform(Queue<T>& queue, Apply applyFunc)
{
    for(T& item: queue)
    {
        applyFunc(item);
    }
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this,0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this,m_size);
}

template<class T>
const typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this,0);
}

template<class T>
const typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this,m_size);
}




template<class T>
class Queue<T>::Iterator {

    const Queue* m_queue;
    int m_index;
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
public:
    // Required Iterator operators.
    T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};
};


template<class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index):
    m_queue(queue), m_index(index)
    {}

template<class T>
T&  Queue<T>::Iterator::operator*() const
{
    return m_queue->m_data[m_index];
}
template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(m_queue->m_size <= m_index)
    {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator) const
{
    return m_index!=iterator.m_index;
}

template<class T>
class Queue<T>::ConstIterator {

    const Queue* m_queue;
    int m_index;
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
public:
    // Required ConstIterator operators.
    const T& operator*() const;
    ConstIterator& operator++();
    const ConstIterator operator++(int);
    bool operator!=(const ConstIterator& iterator) const;
    ConstIterator(const ConstIterator&) = default; // constructor
    ConstIterator& operator=(const ConstIterator& iterator) = default; // assignment operator

    class InvalidOperation{};
};


template<class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index):
        m_queue(queue), m_index(index)
{}

template<class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return m_queue->m_data[m_index];
}
template<class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(m_queue->m_size <= m_index)
    {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
const typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    const ConstIterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iterator) const
{
    return m_index!=iterator.m_index;
}

#endif