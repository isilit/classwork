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

// Добавление предмета в инвентарь
Item* addItem(Item* inv, int& count, const char* name, const char* type, int level) {
    // Создаем новый массив с увеличенным размером
    Item* newInv = new Item[count + 1];
    
    // Копируем старые элементы
    for (int i = 0; i < count; i++) {
        newInv[i] = inv[i];
    }
    
    // Добавляем новый элемент
    newInv[count] = createItem(name, type, level);
    
    // Удаляем старый массив, если он существовал
    if (inv != nullptr) {
        delete[] inv;
    }
    
    count++;
    return newInv;
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
    Item* inventory = nullptr;
    int itemCount = 0;
    
    std::cout << "=== СИСТЕМА УПРАВЛЕНИЯ ИНВЕНТАРЕМ ===\n";
    
    // Тестируем добавление предметов
    inventory = addItem(inventory, itemCount, "Меч дракона", "оружие", 15);
    std::cout << "Добавлен предмет: Меч дракона\n";
    
    inventory = addItem(inventory, itemCount, "Кожаный доспех", "броня", 5);
    std::cout << "Добавлен предмет: Кожаный доспех\n";
    
    std::cout << "Всего предметов в инвентаре: " << itemCount << "\n";
    
    freeInventory(inventory, itemCount);
    
    return 0;
}