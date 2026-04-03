#include "Database.h"
#include <iostream>
#include <limits>
#include <memory>

namespace Menu {
    void show() {
        std::cout << "\n=== Управление базой настольных игр ===\n"
                  << "1. Вывести все игры\n"
                  << "2. Добавить новую игру\n"
                  << "3. Удалить игру\n"
                  << "4. Редактировать игру\n"
                  << "5. Поиск (по названию и жанру)\n"
                  << "6. Сохранить в файл\n"
                  << "7. Загрузить из файла\n"
                  << "0. Выход\n"
                  << "Ваш выбор: ";
    }

    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int getInt(const std::string& prompt) {
        int val;
        std::cout << prompt;
        while (!(std::cin >> val)) {
            std::cerr << "Ошибка: введите целое число.\n";
            clearInput();
            std::cout << prompt;
        }
        clearInput();
        return val;
    }

    std::string getString(const std::string& prompt) {
        std::string s;
        std::cout << prompt;
        std::cin >> s;
        clearInput();
        return s;
    }
}

int main() {
    Database db;
    int choice;
    bool running = true;

    while (running) {
        Menu::show();
        std::cin >> choice;
        Menu::clearInput();

        switch (choice) {
            case 1:
                db.print();
                break;
            case 2: {
                BoardGame bg;
                std::cin >> bg;
                db.add(bg);
                std::cout << "Игра добавлена.\n";
                break;
            }
            case 3: {
                db.print();
                if (db.size() == 0) break;
                int idx = Menu::getInt("Номер игры для удаления: ") - 1;
                if (db.remove(idx))
                    std::cout << "Игра удалена.\n";
                else
                    std::cout << "Неверный номер.\n";
                break;
            }
            case 4: {
                db.print();
                if (db.size() == 0) break;
                int idx = Menu::getInt("Номер игры для редактирования: ") - 1;
                if (idx >= 0 && idx < db.size()) {
                    BoardGame bg;
                    std::cin >> bg;
                    if (db.edit(idx, bg))
                        std::cout << "Изменения сохранены.\n";
                    else
                        std::cout << "Ошибка редактирования.\n";
                } else {
                    std::cout << "Неверный номер.\n";
                }
                break;
            }
            case 5: {
                std::string name = Menu::getString("Название (оставьте пустым для любого): ");
                std::string genre = Menu::getString("Жанр (оставьте пустым для любого): ");
                int resCount;
                int* indices = db.search(name, genre, resCount);
                if (resCount == 0) {
                    std::cout << "Ничего не найдено.\n";
                } else {
                    std::cout << "Найдено игр: " << resCount << "\n";
                    for (int i = 0; i < resCount; ++i) {
                        std::cout << indices[i]+1 << ". " << db[indices[i]] << '\n';
                    }
                }
                delete[] indices;
                break;
            }
            case 6: {
                std::string fname = Menu::getString("Имя файла для сохранения: ");
                if (db.saveToFile(fname))
                    std::cout << "Сохранено в " << fname << "\n";
                else
                    std::cerr << "Ошибка сохранения.\n";
                break;
            }
            case 7: {
                std::string fname = Menu::getString("Имя файла для загрузки: ");
                if (db.loadFromFile(fname))
                    std::cout << "Загружено из " << fname << "\n";
                else
                    std::cerr << "Ошибка загрузки или файл не найден.\n";
                break;
            }
            case 0:
                running = false;
                std::cout << "До свидания!\n";
                break;
            default:
                std::cout << "Неверный пункт. Повторите.\n";
        }
    }
    return 0;
}
