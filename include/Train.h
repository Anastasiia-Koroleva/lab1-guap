#pragma once
#include "Base.h"

class Train : public Base {
private:
    std::string name_;
    int year_;
    std::string route_;
    int wagonsCount_;
    double cargoVolume_;

public:
    Train();
    Train(const std::string& name, int year, const std::string& route,
          int wagonsCount, double cargoVolume);
    Train(const Train& other);
    ~Train() override;

    Train& operator=(const Train& other);
    friend std::ostream& operator<<(std::ostream& os, const Train& t);

    void setName(const std::string& n);
    void setYear(int y);
    void setRoute(const std::string& r);
    void setWagonsCount(int c);
    void setCargoVolume(double v);

    std::string getName() const { return name_; }
    int getYear() const { return year_; }
    std::string getRoute() const { return route_; }
    int getWagonsCount() const { return wagonsCount_; }
    double getCargoVolume() const { return cargoVolume_; }

    void print() const override;
    void save(std::ofstream& out) const override;
    void load(std::ifstream& in) override;
    std::string type() const override { return "Train"; }
};