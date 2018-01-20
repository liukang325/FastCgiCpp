/////////////////////////////////////////////////////////////
/// COPYRIGHT NOTICE
/// Copyright (c) 2018
/// All rights reserved.
///
/// @file Singleton.h
/// @brief 单例类模版
///
/// @version 1.1
/// @author kang
/// @date 2016-12-02
/////////////////////////////////////////////////////////////

#ifndef SINGLETON_H
#define SINGLETON_H
#include <assert.h>
/// 单例类模版
template <class T>
class Singleton
{
public:
    static T* Instance()
    {
        static T m_Instance;
        return &m_Instance;
    }
protected:
    Singleton();
    ~Singleton();
private:
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
};
//template <class T> T* Singleton<T>::m_Instance=NULL;
#endif // SINGLETON_H
