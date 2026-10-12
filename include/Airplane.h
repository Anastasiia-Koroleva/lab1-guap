#pragma once
#include "Base.h"

class Airplane : public Base {
private:
    std::string type_;
    std::string name_;
    double cargoVolume_;
    double length_, width_, height_;
    std::string* cities_;
    int citiesCount_;

public:
    Airplane();
    Airplane(const std::string& type, const std::string& name,
             double cargoVolume, double length, double width, double height);
    Airplane(const Airplane& other);
    ~Airplane() override;

    Airplane& operator=(const Airplane& other);
    friend std::ostream& operator<<(std::ostream& os, const Airplane& a);

    void setType(const std::string& t);
    void setName(const std::string& n);
    void setCargoVolume(double v);
    void setDimensions(double l, double w, double h);
    void addCity(const std::string& city);
    void clearCities();

    std::string getType() const { return type_; }
    std::string getName() const { return name_; }
    double getCargoVolume() const { return cargoVolume_; }
    double getLength() const { return length_; }
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
    int getCitiesCount() const { return citiesCount_; }
    std::string getCity(int i) const;

    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string type() const override { return "Airplane"; }
};