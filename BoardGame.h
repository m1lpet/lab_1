#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <iostream>
#include <string>

class BoardGame {
private:
    std::string name;
    std::string genre;
    int players;
    int age;
    double price;
    int stock;

public:
    BoardGame();
    BoardGame(const std::string& n, const std::string& g, int p, int a, double pr, int s);

    std::string getName() const;
    std::string getGenre() const;
    int getPlayers() const;
    int getAge() const;
    double getPrice() const;
    int getStock() const;

    void setName(const std::string& n);
    void setGenre(const std::string& g);
    void setPlayers(int p);
    void setAge(int a);
    void setPrice(double pr);
    void setStock(int s);

    friend std::ostream& operator<<(std::ostream& os, const BoardGame& bg);
    friend std::istream& operator>>(std::istream& is, BoardGame& bg);

    void writeBinary(std::ostream& os) const;
    void readBinary(std::istream& is);
};

#endif
