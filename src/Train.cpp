#include "Train.h"
#include <stdexcept>

Train::Train()
    : Base(), name_("неизвестно"), year_(0), route_("нет"),
      wagonsCount_(0), cargoVolume_(0) {
    std::cout << "Train: конструктор по умолчанию\n";
}

Train::Train(const std::string& name, int year, const std::string& route,
             int wagonsCount, double cargoVolume)
    : Base(), name_(name), year_(year), route_(route),
      wagonsCount_(wagonsCount), cargoVolume_(cargoVolume) {
    if (year < 1800 || year > 2100)
        throw std::invalid_argument("Год выпуска должен быть в диапазоне 1800-2100");
    if (wagonsCount < 0)
        throw std::invalid_argument("Количество вагонов не может быть отрицательным");
    if (cargoVolume < 0)
        throw std::invalid_argument("Объём груза не может быть отрицательным");
    std::cout << "Train: конструктор с параметрами (" << name_ << ")\n";
}

Train::Train(const Train& other)
    : Base(other), name_(other.name_), year_(other.year_),
      route_(other.route_), wagonsCount_(other.wagonsCount_),
      cargoVolume_(other.cargoVolume_) {
    std::cout << "Train: конструктор копирования (" << name_ << ")\n";
}

Train::~Train() {
    std::cout << "Train: деструктор (" << name_ << ")\n";
}

Train& Train::operator=(const Train& other) {
    if (this == &other) return *this;
    name_ = other.name_;
    year_ = other.year_;
    route_ = other.route_;
    wagonsCount_ = other.wagonsCount_;
    cargoVolume_ = other.cargoVolume_;
    std::cout << "Train: оператор присваивания\n";
    return *this;
}

void Train::setName(const std::string& n) { name_ = n; }

void Train::setYear(int y) {
    if (y < 1800 || y > 2100)
        throw std::invalid_argument("Год выпуска должен быть в диапазоне 1800-2100");
    year_ = y;
}

void Train::setRoute(const std::string& r) { route_ = r; }

void Train::setWagonsCount(int c) {
    if (c < 0)
        throw std::invalid_argument("Количество вагонов не может быть отрицательным");
    wagonsCount_ = c;
}

void Train::setCargoVolume(double v) {
    if (v < 0)
        throw std::invalid_argument("Объём груза не может быть отрицательным");
    cargoVolume_ = v;
}

void Train::print() const {
    std::cout << "=== Поезд ===\n";
    std::cout << "  Наименование: " << name_ << "\n";
    std::cout << "  Год выпуска: " << year_ << "\n";
    std::cout << "  Маршрут: " << route_ << "\n";
    std::cout << "  Количество вагонов: " << wagonsCount_ << "\n";
    std::cout << "  Объём груза: " << cargoVolume_ << " т\n";
}

std::ostream& operator<<(std::ostream& os, const Train& t) {
    os << "[Поезд] " << t.name_ << " (" << t.year_ << "), "
       << t.wagonsCount_ << " вагонов, груз " << t.cargoVolume_ << " т";
    return os;
}

void Train::save(std::ofstream& out) const {
    out << name_ << "\n" << year_ << "\n" << route_ << "\n"
        << wagonsCount_ << "\n" << cargoVolume_ << "\n";
}

void Train::load(std::ifstream& in) {
    std::getline(in, name_);
    in >> year_;
    in.ignore();
    std::getline(in, route_);
    in >> wagonsCount_ >> cargoVolume_;
    in.ignore();
}