#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <iostream>
#include <string>

// Класс, описывающий одну настольную игру
class BoardGame {
private:
    std::string name;
    std::string genre;
    int players;
    int age;
    double price;
    int stock;

public:
    // Конструкторы
    BoardGame();
    BoardGame(const std::string& n, const std::string& g, int p, int a, double pr, int s);

    // Геттеры
    std::string getName() const;
    std::string getGenre() const;
    int getPlayers() const;
    int getAge() const;
    double getPrice() const;
    int getStock() const;

    // Сеттеры
    void setName(const std::string& n);
    void setGenre(const std::string& g);
    void setPlayers(int p);
    void setAge(int a);
    void setPrice(double pr);
    void setStock(int s);

    // Перегрузка операторов ввода/вывода для консоли (текстовый режим)
    friend std::ostream& operator<<(std::ostream& os, const BoardGame& bg);
    friend std::istream& operator>>(std::istream& is, BoardGame& bg);

    // Бинарная сериализация (для файла)
    void writeBinary(std::ostream& os) const;
    void readBinary(std::istream& is);
};

// Класс базы данных (динамический массив объектов BoardGame)
class Database {
private:
    BoardGame* items;   // указатель на динамический массив
    int count;          // текущее количество элементов
    int capacity;       // выделенная ёмкость

    void resize(int newCapacity);  // внутренний метод для расширения массива

public:
    Database();
    ~Database();

    // Запрещаем копирование (для простоты, можно реализовать позже)
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Основные методы (аналог функций из C)
    void print() const;                    // аналог all_vivod
    void add(const BoardGame& bg);         // аналог add
    bool remove(int index);                // аналог delite (по индексу)
    bool edit(int index, const BoardGame& bg);  // аналог redact
    int* search(const std::string& name, const std::string& genre, int& resultCount) const;

    // Сохранение / загрузка в бинарный файл
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Перегрузка оператора [] для доступа к элементам
    BoardGame& operator[](int index);
    const BoardGame& operator[](int index) const;

    // Получение количества элементов
    int size() const;
};

#endif
