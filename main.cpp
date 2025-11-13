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

// Удаление предмета по названию
Item* removeItem(Item* inv, int& count, const char* name) {
    if (inv == nullptr || count == 0) {
        std::cout << "Инвентарь пуст!\n";
        return inv;
    }
    
    // Ищем предмет для удаления
    int indexToRemove = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(inv[i].name, name) == 0) {
            indexToRemove = i;
            break;
        }
    }
    
    if (indexToRemove == -1) {
        std::cout << "Предмет '" << name << "' не найден!\n";
        return inv;
    }
    
    // Если остался один элемент
    if (count == 1) {
        freeItem(inv[0]);
        delete[] inv;
        count = 0;
        std::cout << "Предмет '" << name << "' удален. Инвентарь пуст.\n";
        return nullptr;
    }
    
    // Создаем новый массив без удаляемого элемента
    Item* newInv = new Item[count - 1];
    
    // Копируем элементы до удаляемого
    for (int i = 0; i < indexToRemove; i++) {
        newInv[i] = inv[i];
    }
    
    // Копируем элементы после удаляемого
    for (int i = indexToRemove + 1; i < count; i++) {
        newInv[i - 1] = inv[i];
    }
    
    // Освобождаем память удаляемого элемента
    freeItem(inv[indexToRemove]);
    
    // Удаляем старый массив
    delete[] inv;
    
    count--;
    std::cout << "Предмет '" << name << "' удален.\n";
    return newInv;
}

// Вывод инвентаря
void printInventory(Item* inv, int count) {
    if (inv == nullptr || count == 0) {
        std::cout << "Инвентарь пуст!\n";
        return;
    }
    
    std::cout << "\n=== ИНВЕНТАРЬ ===\n";
    std::cout << "Всего предметов: " << count << "\n";
    std::cout << "----------------------------------------\n";
    
    for (int i = 0; i < count; i++) {
        std::cout << (i + 1) << ". " << inv[i].name 
                  << " | Тип: " << inv[i].type 
                  << " | Уровень: " << inv[i].level << "\n";
    }
    std::cout << "----------------------------------------\n";
}

// Сортировка по уровню (пузырьковая сортировка)
void sortByLevel(Item* inv, int count) {
    if (inv == nullptr || count <= 1) {
        return;
    }
    
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (inv[j].level > inv[j + 1].level) {
                // Обмен местами
                Item temp = inv[j];
                inv[j] = inv[j + 1];
                inv[j + 1] = temp;
            }
        }
    }
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
    
    // Добавляем предметы в разном порядке уровней
    inventory = addItem(inventory, itemCount, "Меч дракона", "оружие", 15);
    inventory = addItem(inventory, itemCount, "Кожаный доспех", "броня", 5);
    inventory = addItem(inventory, itemCount, "Зелье здоровья", "зелье", 3);
    inventory = addItem(inventory, itemCount, "Лук охотника", "оружие", 8);
    inventory = addItem(inventory, itemCount, "Стальной щит", "броня", 12);
    
    std::cout << "Исходный инвентарь:\n";
    printInventory(inventory, itemCount);
    
    // Сортируем по уровню
    std::cout << "\nПосле сортировки по уровню:\n";
    sortByLevel(inventory, itemCount);
    printInventory(inventory, itemCount);
    
    freeInventory(inventory, itemCount);
    
    return 0;
}