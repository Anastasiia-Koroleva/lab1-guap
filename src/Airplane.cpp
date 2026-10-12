#include "Airplane.h"
#include <stdexcept>

Airplane::Airplane()
    : Base(), type_("неизвестно"), name_("неизвестно"),
      cargoVolume_(0), length_(0), width_(0), height_(0),
      cities_(nullptr), citiesCount_(0) {
    std::cout << "Airplane: конструктор по умолчанию\n";
}

Airplane::Airplane(const std::string& type, const std::string& name,
                   double cargoVolume, double length, double width, double height)
    : Base(), type_(type), name_(name),
      cargoVolume_(cargoVolume), length_(length), width_(width), height_(height),
      cities_(nullptr), citiesCount_(0) {
    if (cargoVolume < 0) throw std::invalid_argument("Объём груза не может быть отрицательным");
    if (length <= 0 || width <= 0 || height <= 0)
        throw std::invalid_argument("Габариты должны быть положительными");
    std::cout << "Airplane: конструктор с параметрами (" << name_ << ")\n";
}

Airplane::Airplane(const Airplane& other)
    : Base(other), type_(other.type_), name_(other.name_),
      cargoVolume_(other.cargoVolume_),
      length_(other.length_), width_(other.width_), height_(other.height_),
      cities_(nullptr), citiesCount_(0) {
    if (other.citiesCount_ > 0) {
        cities_ = new std::string[other.citiesCount_];
        for (int i = 0; i < other.citiesCount_; ++i)
            cities_[i] = other.cities_[i];
        citiesCount_ = other.citiesCount_;
    }
    std::cout << "Airplane: конструктор копирования (" << name_ << ")\n";
}

Airplane::~Airplane() {
    delete[] cities_;
    std::cout << "Airplane: деструктор (" << name_ << ")\n";
}

Airplane& Airplane::operator=(const Airplane& other) {
    if (this == &other) return *this;
    delete[] cities_;
    cities_ = nullptr;
    citiesCount_ = 0;

    type_ = other.type_;
    name_ = other.name_;
    cargoVolume_ = other.cargoVolume_;
    length_ = other.length_;
    width_ = other.width_;
    height_ = other.height_;

    if (other.citiesCount_ > 0) {
        cities_ = new std::string[other.citiesCount_];
        for (int i = 0; i < other.citiesCount_; ++i)
            cities_[i] = other.cities_[i];
        citiesCount_ = other.citiesCount_;
    }
    std::cout << "Airplane: оператор присваивания\n";
    return *this;
}

void Airplane::setType(const std::string& t) { type_ = t; }
void Airplane::setName(const std::string& n) { name_ = n; }

void Airplane::setCargoVolume(double v) {
    if (v < 0) throw std::invalid_argument("Объём груза не может быть отрицательным");
    cargoVolume_ = v;
}

void Airplane::setDimensions(double l, double w, double h) {
    if (l <= 0 || w <= 0 || h <= 0)
        throw std::invalid_argument("Габариты должны быть положительными");
    length_ = l; width_ = w; height_ = h;
}

void Airplane::addCity(const std::string& city) {
    std::string* newArr = new std::string[citiesCount_ + 1];
    for (int i = 0; i < citiesCount_; ++i) newArr[i] = cities_[i];
    newArr[citiesCount_] = city;
    delete[] cities_;
    cities_ = newArr;
    ++citiesCount_;
}

void Airplane::clearCities() {
    delete[] cities_;
    cities_ = nullptr;
    citiesCount_ = 0;
}

std::string Airplane::getCity(int i) const {
    if (i < 0 || i >= citiesCount_)
        throw std::out_of_range("Индекс города вне диапазона");
    return cities_[i];
}

void Airplane::print() const {
    std::cout << "=== Самолёт ===\n";
    std::cout << "  Тип: " << type_ << "\n";
    std::cout << "  Наименование: " << name_ << "\n";
    std::cout << "  Объём груза: " << cargoVolume_ << " т\n";
    std::cout << "  Габариты (ДxШxВ): " << length_ << " x " << width_ << " x " << height_ << " м\n";
    std::cout << "  Города (" << citiesCount_ << "): ";
    if (citiesCount_ == 0) std::cout << "нет";
    for (int i = 0; i < citiesCount_; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << cities_[i];
    }
    std::cout << "\n";
}

std::ostream& operator<<(std::ostream& os, const Airplane& a) {
    os << "[Самолёт] " << a.type_ << " " << a.name_
       << ", груз " << a.cargoVolume_ << " т, городов: " << a.citiesCount_;
    return os;
}

void Airplane::save(std::ofstream& out) const {
    out << type_ << "\n" << name_ << "\n"
        << cargoVolume_ << "\n"
        << length_ << " " << width_ << " " << height_ << "\n"
        << citiesCount_ << "\n";
    for (int i = 0; i < citiesCount_; ++i)
        out << cities_[i] << "\n";
}

void Airplane::load(std::ifstream& in) {
    std::getline(in, type_);
    std::getline(in, name_);
    in >> cargoVolume_ >> length_ >> width_ >> height_;
    in >> citiesCount_;
    in.ignore();
    delete[] cities_;
    cities_ = nullptr;
    if (citiesCount_ > 0) {
        cities_ = new std::string[citiesCount_];
        for (int i = 0; i < citiesCount_; ++i)
            std::getline(in, cities_[i]);
    }
}