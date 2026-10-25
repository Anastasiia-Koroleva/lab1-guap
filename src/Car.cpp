#include "Car.h"
#include <stdexcept>

Car::Car()
    : Base(), year_(0), brand_("неизвестно"), model_("неизвестно"),
      deliveries_(nullptr), deliveriesCount_(0) {
    std::cout << "Car: конструктор по умолчанию\n";
}

Car::Car(int year, const std::string& brand, const std::string& model)
    : Base(), year_(year), brand_(brand), model_(model),
      deliveries_(nullptr), deliveriesCount_(0) {
    if (year < 1800 || year > 2100)
        throw std::invalid_argument("Год выпуска должен быть в диапазоне 1800-2100");
    std::cout << "Car: конструктор с параметрами (" << brand_ << " " << model_ << ")\n";
}

Car::Car(const Car& other)
    : Base(other), year_(other.year_), brand_(other.brand_), model_(other.model_),
      deliveries_(nullptr), deliveriesCount_(0) {
    if (other.deliveriesCount_ > 0) {
        deliveries_ = new Delivery[other.deliveriesCount_];
        for (int i = 0; i < other.deliveriesCount_; ++i)
            deliveries_[i] = other.deliveries_[i];
        deliveriesCount_ = other.deliveriesCount_;
    }
    std::cout << "Car: конструктор копирования (" << brand_ << " " << model_ << ")\n";
}

Car::~Car() {
    delete[] deliveries_;
    std::cout << "Car: деструктор (" << brand_ << " " << model_ << ")\n";
}

Car& Car::operator=(const Car& other) {
    if (this == &other) return *this;
    delete[] deliveries_;
    deliveries_ = nullptr;
    deliveriesCount_ = 0;

    year_ = other.year_;
    brand_ = other.brand_;
    model_ = other.model_;

    if (other.deliveriesCount_ > 0) {
        deliveries_ = new Delivery[other.deliveriesCount_];
        for (int i = 0; i < other.deliveriesCount_; ++i)
            deliveries_[i] = other.deliveries_[i];
        deliveriesCount_ = other.deliveriesCount_;
    }
    std::cout << "Car: оператор присваивания\n";
    return *this;
}

void Car::setYear(int y) {
    if (y < 1800 || y > 2100)
        throw std::invalid_argument("Год выпуска должен быть в диапазоне 1800-2100");
    year_ = y;
}

void Car::setBrand(const std::string& b) { brand_ = b; }
void Car::setModel(const std::string& m) { model_ = m; }

void Car::addDelivery(const std::string& city, int hours, double cargoVolume) {
    if (hours <= 0)
        throw std::invalid_argument("Количество часов доставки должно быть положительным");
    if (cargoVolume < 0)
        throw std::invalid_argument("Объём груза не может быть отрицательным");

    Delivery* newArr = new Delivery[deliveriesCount_ + 1];
    for (int i = 0; i < deliveriesCount_; ++i)
        newArr[i] = deliveries_[i];
    newArr[deliveriesCount_].city = city;
    newArr[deliveriesCount_].hours = hours;
    newArr[deliveriesCount_].cargoVolume = cargoVolume;
    delete[] deliveries_;
    deliveries_ = newArr;
    ++deliveriesCount_;
}

void Car::clearDeliveries() {
    delete[] deliveries_;
    deliveries_ = nullptr;
    deliveriesCount_ = 0;
}

void Car::removeDelivery(int index) {
    if (index < 0 || index >= deliveriesCount_)
        throw std::out_of_range("Индекс доставки вне диапазона");

    Delivery* newArr = new Delivery[deliveriesCount_ - 1];
    for (int i = 0, j = 0; i < deliveriesCount_; ++i) {
        if (i == index) continue;
        newArr[j++] = deliveries_[i];
    }
    delete[] deliveries_;
    deliveries_ = newArr;
    --deliveriesCount_;
}

Delivery Car::getDelivery(int index) const {
    if (index < 0 || index >= deliveriesCount_)
        throw std::out_of_range("Индекс доставки вне диапазона");
    return deliveries_[index];
}

void Car::print() const {
    std::cout << "=== Автомобиль ===\n";
    std::cout << "  Год выпуска: " << year_ << "\n";
    std::cout << "  Марка: " << brand_ << "\n";
    std::cout << "  Модель: " << model_ << "\n";
    std::cout << "  Доставок: " << deliveriesCount_ << "\n";
    for (int i = 0; i < deliveriesCount_; ++i) {
        std::cout << "    " << (i + 1) << ") " << deliveries_[i].city
                  << " — " << deliveries_[i].hours << " ч, "
                  << deliveries_[i].cargoVolume << " т\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Car& c) {
    os << "[Автомобиль] " << c.brand_ << " " << c.model_
       << " (" << c.year_ << "), доставок: " << c.deliveriesCount_;
    return os;
}

void Car::save(std::ofstream& out) const {
    out << year_ << "\n" << brand_ << "\n" << model_ << "\n"
        << deliveriesCount_ << "\n";
    for (int i = 0; i < deliveriesCount_; ++i) {
        out << deliveries_[i].city << "\n"
            << deliveries_[i].hours << " "
            << deliveries_[i].cargoVolume << "\n";
    }
}

void Car::load(std::ifstream& in) {
    in >> year_;
    in.ignore();
    std::getline(in, brand_);
    std::getline(in, model_);
    in >> deliveriesCount_;
    in.ignore();

    delete[] deliveries_;
    deliveries_ = nullptr;
    if (deliveriesCount_ > 0) {
        deliveries_ = new Delivery[deliveriesCount_];
        for (int i = 0; i < deliveriesCount_; ++i) {
            std::getline(in, deliveries_[i].city);
            in >> deliveries_[i].hours >> deliveries_[i].cargoVolume;
            in.ignore();
        }
    }
}