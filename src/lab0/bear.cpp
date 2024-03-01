#include "wolf.hpp"
#include "bear.hpp"
#include "robber.hpp"

// Конструктор с параметрами для медведя
Bear::Bear(int x, int y) : NPC(BearType, x, y) {}

// Конструктор для чтения данных из потока для медведя
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

// Вывод информации о медведе
void Bear::print()
{
    std::cout << *this;
}

// Вывод информации о медведе в указанный поток
void Bear::print(std::ostream &outfs) {
    outfs << *this;
}

// Метод для взаимодействия с посетителями
bool Bear::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Bear>(this,[](Bear*){}));
}

// Сохранение данных о медведе в поток
void Bear::save(std::ostream &os) 
{
    os << BearType << std::endl;
    NPC::save(os);
}

// Метод для сражения с другим медведем
bool Bear::fight(std::shared_ptr<Bear> other) 
{
    fight_notify(other, false);
    return false;
}

// Метод для сражения с грабителем
bool Bear::fight(std::shared_ptr<Robber> other) 
{
    fight_notify(other, false);
    return false;
}

// Метод для сражения с волком
bool Bear::fight(std::shared_ptr<Wolf> other) 
{
    fight_notify(other, true);
    return true;
}

// Перегрузка оператора вывода для вывода информации о медведе
std::ostream &operator<<(std::ostream &os, Bear &bear)
{
    os << "Bear 🐻: " << *static_cast<NPC *>(&bear) << std::endl;
    return os;
}
