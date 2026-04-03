#ifndef DATABASE_H
#define DATABASE_H

#include "BoardGame.h"
#include <string>

class Database {
private:
    BoardGame* items;   // динамический массив
    int count;          // текущее количество
    int capacity;       // выделенная ёмкость

    void resize(int newCapacity);  // расширение массива

public:
    Database();
    ~Database();

    // Запрещаем копирование (для упрощения)
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Основные операции
    void add(const BoardGame& bg);
    bool remove(int index);          // удалить по индексу
    bool edit(int index, const BoardGame& bg);
    void print() const;              // вывод в консоль

    // Поиск по имени и жанру (пустая строка = любой)
    int* search(const std::string& name, const std::string& genre, int& resultCount) const;

    // Работа с бинарным файлом
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    // Доступ по индексу
    BoardGame& operator[](int index);
    const BoardGame& operator[](int index) const;

    int size() const;
};

#endif
