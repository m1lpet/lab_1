#include "BoardGame.h"
#include <iomanip>

BoardGame::BoardGame() : players(0), age(0), price(0.0), stock(0) {}

BoardGame::BoardGame(const std::string& n, const std::string& g, int p, int a, double pr, int s)
    : name(n), genre(g), players(p), age(a), price(pr), stock(s) {}

std::string BoardGame::getName() const { return name; }
std::string BoardGame::getGenre() const { return genre; }
int BoardGame::getPlayers() const { return players; }
int BoardGame::getAge() const { return age; }
double BoardGame::getPrice() const { return price; }
int BoardGame::getStock() const { return stock; }

void BoardGame::setName(const std::string& n) { name = n; }
void BoardGame::setGenre(const std::string& g) { genre = g; }
void BoardGame::setPlayers(int p) { players = p; }
void BoardGame::setAge(int a) { age = a; }
void BoardGame::setPrice(double pr) { price = pr; }
void BoardGame::setStock(int s) { stock = s; }

std::ostream& operator<<(std::ostream& os, const BoardGame& bg) {
    os << std::left << std::setw(20) << bg.name
       << std::setw(15) << bg.genre
       << std::setw(8) << bg.players
       << std::setw(5) << bg.age
       << std::setw(10) << bg.price
       << std::setw(5) << bg.stock;
    return os;
}

std::istream& operator>>(std::istream& is, BoardGame& bg) {
    std::cout << "Название: ";   is >> bg.name;
    std::cout << "Жанр: ";       is >> bg.genre;
    std::cout << "Кол-во игроков: "; is >> bg.players;
    std::cout << "Мин. возраст: ";   is >> bg.age;
    std::cout << "Цена: ";           is >> bg.price;
    std::cout << "На складе (шт): "; is >> bg.stock;
    return is;
}

void BoardGame::writeBinary(std::ostream& os) const {
    size_t len = name.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(name.c_str(), len);

    len = genre.size();
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(genre.c_str(), len);

    os.write(reinterpret_cast<const char*>(&players), sizeof(players));
    os.write(reinterpret_cast<const char*>(&age), sizeof(age));
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
    os.write(reinterpret_cast<const char*>(&stock), sizeof(stock));
}

void BoardGame::readBinary(std::istream& is) {
    size_t len;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    name.resize(len);
    is.read(&name[0], len);

    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    genre.resize(len);
    is.read(&genre[0], len);

    is.read(reinterpret_cast<char*>(&players), sizeof(players));
    is.read(reinterpret_cast<char*>(&age), sizeof(age));
    is.read(reinterpret_cast<char*>(&price), sizeof(price));
    is.read(reinterpret_cast<char*>(&stock), sizeof(stock));
}
