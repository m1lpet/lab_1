#include "Database.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

Database::Database() : items(nullptr), count(0), capacity(0) {}

Database::~Database() {
    delete[] items;
}

void Database::resize(int newCapacity) {
    BoardGame* newItems = new BoardGame[newCapacity];
    int copyCount = (count < newCapacity) ? count : newCapacity;
    for (int i = 0; i < copyCount; ++i)
        newItems[i] = items[i];
    delete[] items;
    items = newItems;
    capacity = newCapacity;
    if (count > capacity) count = capacity;
}

void Database::add(const BoardGame& bg) {
    if (count == capacity) {
        int newCap = (capacity == 0) ? 2 : capacity * 2;
        resize(newCap);
    }
    items[count++] = bg;
}

bool Database::remove(int index) {
    if (index < 0 || index >= count) return false;
    for (int i = index; i < count - 1; ++i)
        items[i] = items[i + 1];
    count--;
    return true;
}

bool Database::edit(int index, const BoardGame& bg) {
    if (index < 0 || index >= count) return false;
    items[index] = bg;
    return true;
}

void Database::print() const {
    if (count == 0) {
        std::cout << "База данных пуста.\n";
        return;
    }
    std::cout << "\n========================================================================\n";
    std::cout << std::left << std::setw(20) << "Название"
              << std::setw(15) << "Жанр"
              << std::setw(8) << "Игроки"
              << std::setw(5) << "Возраст"
              << std::setw(10) << "Цена"
              << std::setw(5) << "Склад\n";
    std::cout << "========================================================================\n";
    for (int i = 0; i < count; ++i)
        std::cout << i+1 << ". " << items[i] << '\n';
}

int* Database::search(const std::string& name, const std::string& genre, int& resultCount) const {
    int* indices = new int[count];
    resultCount = 0;
    for (int i = 0; i < count; ++i) {
        bool matchName = name.empty() || items[i].getName() == name;
        bool matchGenre = genre.empty() || items[i].getGenre() == genre;
        if (matchName && matchGenre)
            indices[resultCount++] = i;
    }
    return indices; 
}

bool Database::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return false;
    ofs.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (int i = 0; i < count; ++i)
        items[i].writeBinary(ofs);
    return true;
}

bool Database::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return false;
    int newCount;
    ifs.read(reinterpret_cast<char*>(&newCount), sizeof(newCount));
    if (newCount < 0) return false;

    BoardGame* temp = new BoardGame[newCount];
    for (int i = 0; i < newCount; ++i)
        temp[i].readBinary(ifs);
    if (ifs.fail()) {
        delete[] temp;
        return false;
    }
    delete[] items;
    items = temp;
    count = newCount;
    capacity = newCount;
    return true;
}

BoardGame& Database::operator[](int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
    return items[index];
}

const BoardGame& Database::operator[](int index) const {
    if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
    return items[index];
}

int Database::size() const { return count; }
