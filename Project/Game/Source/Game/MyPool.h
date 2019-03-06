#pragma once
#include <vector>

class GameObject;

//template <class MyType> class PooledObject
//{
//protected:
//    MyPool<MyType>* m_pPool;
//
//public:
//    PooledObject(MyPool<MyType>* pPool)
//    {
//        assert(pPool != nullptr);
//        m_pPool = pPool;
//        m_pPool->AddObjectToPool((MyType)this);
//    }
//
//    void ReturnToPool()
//    {
//        if (m_pPool)
//        {
//            m_pPool->ReturnObjectToPool((MyType)this);
//        }
//    }
//};


template <class TYPE> class MyPool
{
protected:
    std::vector <TYPE> m_Objects;
public:
    MyPool() {}
    ~MyPool() 
    {
        while (m_Objects.empty() == false)
        {
            delete m_Objects.back();    // only delete the address
            m_Objects.pop_back();   //delete the stuff as well as shrink down the vector size
        }
    }
    TYPE GetObjectFromPool()
    {
        // safety check: if we have object or not in the pool
        TYPE pObject = m_Objects.back();
        if (pObject != nullptr)
        {
            m_Objects.pop_back();
        }
        /* if (m_Objects.empty())
        {
        return nullptr;
        }*/
        return pObject;
    }
    void AddObjectToPool(TYPE obj)
    {


        // if the searching can get to the end, which means obj not in the pool 
        // so that we can add it
        if (std::find(m_Objects.begin(), m_Objects.end(), obj) == m_Objects.end())
        {
            
            m_Objects.push_back(obj);
        }
        
    }
};
