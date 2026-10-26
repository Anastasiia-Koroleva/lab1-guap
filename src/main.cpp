#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>

// Подключаем windows.h для настройки консоли
#ifdef _WIN32
#include <windows.h>
#endif

#include "Base.h"
#include "Airplane.h"
#include "Train.h"
#include "Car.h"
#include "Keerer.h"
#include "Exceptions.h"

using namespace std;

// --- Вспомогательные функции для ввода ---
void clearInput() {
    cin.clear();
    // Используем числовое значение вместо max(), чтобы VS Code не ругался
    cin.ignore(10000, '\n'); 
}

int readInt(const string& prompt) {
    int num;
    cout << prompt;
    while (!(cin >> num)) {
        cout << "Ошибка: введите целое число. Повторите: ";
        clearInput();
    }
    clearInput();
    return num;
}

double readDouble(const string& prompt) {
    double num;
    cout << prompt;
    while (!(cin >> num)) {
        cout << "Ошибка: введите число. Повторите: ";
        clearInput();
    }
    clearInput();
    return num;
}

string readString(const string& prompt) {
    string input_str;
    cout << prompt;
    getline(cin, input_str);
    while (input_str.empty()) {
        cout << "Пустая строка недопустима. Повторите: ";
        getline(cin, input_str);
    }
    return input_str;
}

// --- Функции ввода конкретных объектов ---

Base* createAirplane() {
    cout << "\n--- Создание Самолета ---\n";
    string type = readString("Тип: ");
    string name = readString("Наименование: ");
    double cargo = readDouble("Объём груза (т): ");
    double l = readDouble("Длина (м): ");
    double w = readDouble("Ширина (м): ");
    double h = readDouble("Высота (м): ");

    Airplane* a = new Airplane(type, name, cargo, l, w, h);

    int citiesCount = readInt("Сколько городов посещает? ");
    for (int i = 0; i < citiesCount; ++i) {
        string city = readString("Город " + to_string(i + 1) + ": ");
        a->addCity(city);
    }
    return a;
}

Base* createTrain() {
    cout << "\n--- Создание Поезда ---\n";
    string name = readString("Наименование: ");
    int year = readInt("Год выпуска: ");
    string route = readString("Маршрут: ");
    int wagons = readInt("Количество вагонов: ");
    double cargo = readDouble("Объём груза (т): ");

    return new Train(name, year, route, wagons, cargo);
}

Base* createCar() {
    cout << "\n--- Создание Автомобиля ---\n";
    int year = readInt("Год выпуска: ");
    string brand = readString("Марка: ");
    string model = readString("Модель: ");

    Car* c = new Car(year, brand, model);

    int delivCount = readInt("Сколько городов доставки? ");
    for (int i = 0; i < delivCount; ++i) {
        cout << "  Доставка " << (i + 1) << ":\n";
        string city = readString("  Город: ");
        int hours = readInt("  Часов в пути: ");
        double vol = readDouble("  Объём груза (т): ");
        c->addDelivery(city, hours, vol);
    }
    return c;
}

// --- Главное меню ---
void printMenu() {
    cout << "\n=== МЕНЮ ===\n";
    cout << "1. Добавить Самолёт\n";
    cout << "2. Добавить Поезд\n";
    cout << "3. Добавить Автомобиль\n";
    cout << "4. Показать все объекты\n";
    cout << "5. Удалить объект по индексу\n";
    cout << "6. Сохранить в файл\n";
    cout << "7. Загрузить из файла\n";
    cout << "8. Очистить контейнер\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    // ---- ИСПРАВЛЕННАЯ НАСТРОЙКА КОДИРОВКИ ----
    #ifdef _WIN32
    // 65001 — это код UTF-8
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif

    Keerer container;
    int choice;

    do {
        printMenu();
        while (!(cin >> choice)) {
            cout << "Ошибка: введите число. Повторите: ";
            clearInput();
        }
        clearInput();

        try {
            switch (choice) {
                case 1: {
                    Base* a = createAirplane();
                    container.add(a);
                    cout << "Самолёт добавлен.\n";
                    break;
                }
                case 2: {
                    Base* t = createTrain();
                    container.add(t);
                    cout << "Поезд добавлен.\n";
                    break;
                }
                case 3: {
                    Base* c = createCar();
                    container.add(c);
                    cout << "Автомобиль добавлен.\n";
                    break;
                }
                case 4: {
                    container.printAll();
                    break;
                }
                case 5: {
                    if (container.empty()) {
                        cout << "Контейнер пуст.\n";
                        break;
                    }
                    int idx = readInt("Введите индекс для удаления: ");
                    container.remove(idx);
                    cout << "Объект с индексом " << idx << " удалён.\n";
                    break;
                }
                case 6: {
                    string filename = readString("Введите имя файла для сохранения (например, data.txt): ");
                    container.saveToFile(filename);
                    break;
                }
                case 7: {
                    string filename = readString("Введите имя файла для загрузки (например, data.txt): ");
                    container.loadFromFile(filename);
                    break;
                }
                case 8: {
                    container.clear();
                    cout << "Контейнер очищен.\n";
                    break;
                }
                case 0: {
                    cout << "Выход из программы.\n";
                    break;
                }
                default: {
                    cout << "Неверный пункт меню. Попробуйте снова.\n";
                    break;
                }
            }
        }
        catch (const out_of_range& e) {
            cout << "\n[ОШИБКА] " << e.what() << "\n";
        }
        catch (const invalid_argument& e) {
            cout << "\n[ОШИБКА] " << e.what() << "\n";
        }
        catch (const runtime_error& e) {
            cout << "\n[ОШИБКА] " << e.what() << "\n";
        }
        catch (const exception& e) {
            cout << "\n[ОШИБКА] Неизвестная ошибка: " << e.what() << "\n";
        }
        catch (...) {
            cout << "\n[ОШИБКА] Неизвестная ошибка.\n";
        }

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.get(); // пауза

    } while (choice != 0);

    cout << "Программа завершена.\n";
    return 0;
}