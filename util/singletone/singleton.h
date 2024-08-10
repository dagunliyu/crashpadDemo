#pragma once

template <class T>
class Singleton
{
public:
    static T& instance()
    {
        static T single;
        return single;
    }

private:
    Singleton() {}
    virtual ~Singleton() {}

    Singleton(const Singleton& single) = delete;
    const Singleton& operator=(const Singleton& single) = delete;
};


