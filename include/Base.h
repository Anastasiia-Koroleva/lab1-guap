#pragma once
#include <iostream>
#include <fstream>
#include <string>

class Base {
public:
    Base() {
        std::cout << "Base: конструктор по умолчанию\n";
    }
    Base(const Base& other) {
        std::cout << "Base: конструктор копирования\n";
    }
    virtual ~Base() {
        std::cout << "Base: деструктор\n";
    }

    virtual void print() const = 0;
    virtual void save(std::ofstream& out) const = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual std::string type() const = 0;
};