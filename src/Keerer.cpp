#include "Keerer.h"
#include "Airplane.h"
#include "Train.h"
#include "Car.h"
#include "Exceptions.h"
#include <iostream>
#include <fstream>

Keerer::Keerer()
    : items_(nullptr), count_(0), capacity_(0) {
    std::cout << "Keerer: конструктор по умолчанию\n";
}

Keerer::Keerer(const Keerer& other)
    : items_(nullptr), count_(0), capacity_(0) {
    if (other.count_ > 0) {
        items_ = new Base*[other.capacity_];
        for (int i = 0; i < other.count_; ++i) {
            // Клонируем каждый объект через его собственный тип
            Airplane* a = dynamic_cast<Airplane*>(other.items_[i]);
            if (a) { items_[i] = new Airplane(*a); continue; }
            Train* t = dynamic_cast<Train*>(other.items_[i]);
            if (t) { items_[i] = new Train(*t); continue; }
            Car* c = dynamic_cast<Car*>(other.items_[i]);
            if (c) { items_[i] = new Car(*c); continue; }
            items_[i] = nullptr;
        }
        count_ = other.count_;
        capacity_ = other.capacity_;
    }
    std::cout << "Keerer: конструктор копирования\n";
}

Keerer::~Keerer() {
    clear();
    delete[] items_;
    std::cout << "Keerer: деструктор\n";
}

Keerer& Keerer::operator=(const Keerer& other) {
    if (this == &other) return *this;
    clear();
    delete[] items_;
    items_ = nullptr;
    count_ = 0;
    capacity_ = 0;

    if (other.count_ > 0) {
        items_ = new Base*[other.capacity_];
        for (int i = 0; i < other.count_; ++i) {
            Airplane* a = dynamic_cast<Airplane*>(other.items_[i]);
            if (a) { items_[i] = new Airplane(*a); continue; }
            Train* t = dynamic_cast<Train*>(other.items_[i]);
            if (t) { items_[i] = new Train(*t); continue; }
            Car* c = dynamic_cast<Car*>(other.items_[i]);
            if (c) { items_[i] = new Car(*c); continue; }
            items_[i] = nullptr;
        }
        count_ = other.count_;
        capacity_ = other.capacity_;
    }
    std::cout << "Keerer: оператор присваивания\n";
    return *this;
}

Base* Keerer::operator[](int index) const {
    return get(index);
}

void Keerer::ensureCapacity() {
    if (count_ < capacity_) return;
    int newCap = (capacity_ == 0) ? 4 : capacity_ * 2;
    Base** newArr = new Base*[newCap];
    for (int i = 0; i < count_; ++i) newArr[i] = items_[i];
    delete[] items_;
    items_ = newArr;
    capacity_ = newCap;
}

void Keerer::add(Base* item) {
    if (item == nullptr)
        throw InvalidArgumentException("попытка добавить nullptr в контейнер");
    ensureCapacity();
    items_[count_++] = item;
}

void Keerer::remove(int index) {
    if (index < 0 || index >= count_)
        throw IndexOutOfRangeException("индекс " + std::to_string(index) +
                                       " вне диапазона [0, " + std::to_string(count_ - 1) + "]");
    delete items_[index];
    for (int i = index; i < count_ - 1; ++i)
        items_[i] = items_[i + 1];
    --count_;
}

void Keerer::clear() {
    for (int i = 0; i < count_; ++i)
        delete items_[i];
    count_ = 0;
}

Base* Keerer::get(int index) const {
    if (index < 0 || index >= count_)
        throw IndexOutOfRangeException("индекс " + std::to_string(index) +
                                       " вне диапазона [0, " + std::to_string(count_ - 1) + "]");
    return items_[index];
}

void Keerer::printAll() const {
    if (count_ == 0) {
        std::cout << "Контейнер пуст.\n";
        return;
    }
    std::cout << "Всего объектов: " << count_ << "\n";
    for (int i = 0; i < count_; ++i) {
        std::cout << "--- [" << i << "] ---\n";
        items_[i]->print();
    }
}

void Keerer::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open())
        throw FileOpenException(filename);

    out << count_ << "\n";
    for (int i = 0; i < count_; ++i) {
        out << items_[i]->type() << "\n";
        items_[i]->save(out);
    }
    out.close();
    std::cout << "Сохранено объектов: " << count_ << " в файл " << filename << "\n";
}

void Keerer::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
        throw FileOpenException(filename);

    clear();  

    int n = 0;
    in >> n;
    in.ignore();

    for (int i = 0; i < n; ++i) {
        std::string t;
        std::getline(in, t);

        Base* obj = nullptr;
        if (t == "Airplane")      obj = new Airplane();
        else if (t == "Train")    obj = new Train();
        else if (t == "Car")      obj = new Car();
        else throw InvalidArgumentException("неизвестный тип объекта в файле: " + t);

        obj->load(in);
        add(obj);
    }
    in.close();
    std::cout << "Загружено объектов: " << count_ << " из файла " << filename << "\n";
}