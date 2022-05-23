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
    static const int ELEMENT_NOT_FOUND = -1;

    void expand();


public:
    Queue();
    Queue(const Queue& queue);
    ~Queue();
    Queue& operator=(const Queue& queue);

    void pushBack(T newItem);
    T& front() const;
    void popFront();
    int size() const;

    template<class Apply>
    void transform(Apply applyFunc);
    
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    class EmptyQueue{};
};



template<class T>
Queue<T>::Queue(): m_data(new T[INITIAL_SIZE]), m_size(0),m_maxSize(INITIAL_SIZE){}

template<class T>
Queue<T>::Queue(const Queue<T>& queue): 
    m_data(new T[queue.m_size()]),
    m_size(queue.m_size()),
    m_maxSize(queue.size())
    {
        try
        {
            for(int i=0; i< queue.m_size();i++)
            {
                m_data[i]=queue.m_data[i];
            }
        }
        catch(const std::bad_alloc& e)
        {
            delete []m_data;
            throw();
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
    catch(const std::bad_alloc& e)
    {
        delete []tempData;
        throw;
    }
    

    delete [] m_data;
    m_maxSize = newMaxSize;
    m_data = tempData;
    return *this;

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
    catch(const std::bad_alloc& e)
    {
        delete []tempData;
        throw();
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
void Queue<T>::pushBack(T newItem)
{
     if (m_size==m_maxSize)
     {
        this->expand();
     }
     m_data[size] = newItem;
     size++;
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
    if(size<=0)
    {
        return;
    }

    for (int i=1; i<m_size; i++)
    {
        m_data[i-1]=m_data[i];
    }
    size--;
} 


template<class T,class Condition>
Queue<T> filter(const Queue<T>& queue, Condition filterCondition) 
{
    Queue<T> filtered = Queue<T>();
    for(const T& item: *this)
    {
        if(filterCondition(item))
        {
            filtered.pushBack(item);
        }
    }
    return filtered;
}

template<class T>
template<class Apply>
void Queue<T>::transform(Apply applyFunc) 
{
    for(const T& item: *this)
    {
        applyFunc(item);
    }
}

template<class T>
typename Queue<T>::Iterator Queue<T>::begin() const 
{
    return Iterator(this,0);
}

template<class T>
typename Queue<T>::Iterator Queue<T>::end() const 
{
    return Iterator(this,m_size);
}


template<class T>
class Queue<T>::Iterator {

    const Queue* m_queue;
    int m_index;
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;
public:
    const T& operator*() const;
    Iterator& operator++();
    Iterator& operator++(int);
    bool operator!=(const Iterator& iterator) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};
};


template<class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index):
    queue(queue), index(index){}

template<class T>
const T&  Queue<T>::Iterator::operator*() const
{
    return m_queue->m_data[m_index];
}
template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++() 
{
    if(m_queue->m_size < m_index)
    {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(int) 
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

#endif