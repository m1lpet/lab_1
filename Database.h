#ifndef DATABASE_H
#define DATABASE_H

#include "BoardGame.h"
#include <string>

class Database {
private:
    BoardGame* items;  
    int count;          
    int capacity;      

    void resize(int newCapacity);  

public:
    Database();
    ~Database();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    void add(const BoardGame& bg);
    bool remove(int index);        
    bool edit(int index, const BoardGame& bg);
    void print() const;             

    int* search(const std::string& name, const std::string& genre, int& resultCount) const;

    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    BoardGame& operator[](int index);
    const BoardGame& operator[](int index) const;

    int size() const;
};

#endif
