#pragma once
#include "Base.h"

struct Delivery {
    std::string city;
    int hours;
    double cargoVolume;
};

class Car : public Base {
private:
    int year_;
    std::string brand_;
    std::string model_;
    Delivery* deliveries_;   
    int deliveriesCount_;

public:
    Car();
    Car(int year, const std::string& brand, const std::string& model);
    Car(const Car& other);
    ~Car() override;

    Car& operator=(const Car& other);
    friend std::ostream& operator<<(std::ostream& os, const Car& c);

    void setYear(int y);
    void setBrand(const std::string& b);
    void setModel(const std::string& m);
    void addDelivery(const std::string& city, int hours, double cargoVolume);
    void clearDeliveries();
    void removeDelivery(int index);

    int getYear() const { return year_; }
    std::string getBrand() const { return brand_; }
    std::string getModel() const { return model_; }
    int getDeliveriesCount() const { return deliveriesCount_; }
    Delivery getDelivery(int index) const;

    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string type() const override { return "Car"; }
};