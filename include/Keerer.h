#pragma once
#include "Base.h"

class Keerer {
private:
    Base** items_;      
    int count_;         
    int capacity_;      

    void ensureCapacity();  

public:
    Keerer();
    Keerer(const Keerer& other);
    ~Keerer();

    Keerer& operator=(const Keerer& other);
    Base* operator[](int index) const; 

    void add(Base* item);      
    void remove(int index);    
    void clear();              

    int size() const { return count_; }
    bool empty() const { return count_ == 0; }
    Base* get(int index) const;
    void printAll() const;     

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};