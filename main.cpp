#include <iostream>
#include <cstring>
#include <algorithm>

struct Item {
    char* name;
    char* type;
    int level;
};

// Функция для создания нового предмета
Item createItem(const char* name, const char* type, int level) {
    Item newItem;
    
    // Выделяем память для имени
    newItem.name = new char[strlen(name) + 1];
    strcpy(newItem.name, name);
    
    // Выделяем память для типа
    newItem.type = new char[strlen(type) + 1];
    strcpy(newItem.type, type);
    
    newItem.level = level;
    
    return newItem;
}

// Функция для освобождения памяти предмета
void freeItem(Item& item) {
    delete[] item.name;
    delete[] item.type;
}

// Освобождение памяти всего инвентаря
void freeInventory(Item* inv, int count) {
    if (inv != nullptr) {
        for (int i = 0; i < count; i++) {
            freeItem(inv[i]);
        }
        delete[] inv;
    }
}

int main() {
    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ИНВЕНТАРЕМ ===\n";
    std::cout << "Базовая структура создана.\n";
    
    // Тестируем создание и освобождение одного предмета
    Item testItem = createItem("Тестовый меч", "оружие", 5);
    std::cout << "Создан предмет: " << testItem.name << " | Тип: " << testItem.type << " | Уровень: " << testItem.level << "\n";
    freeItem(testItem);
    
    return 0;
}