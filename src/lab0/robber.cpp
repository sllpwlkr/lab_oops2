#include "robber.hpp"
#include "wolf.hpp"
#include "bear.hpp"

// Конструктор с параметрами для грабителя
Robber::Robber(int x, int y) : NPC(RobberType, x, y) {}

// Конструктор для чтения данных из потока для грабителя
Robber::Robber(std::istream &is) : NPC(RobberType, is) {}

// Метод для взаимодействия с посетителями
bool Robber::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::shared_ptr<Robber>(this,[](Robber*){}));
}

// Вывод информации о грабителе
void Robber::print()
{
    std::cout << *this;
}

// Вывод информации о грабителе в указанный поток
void Robber::print(std::ostream &outfs) {
    outfs << *this;
}

// Сохранение данных о грабителе в поток
void Robber::save(std::ostream &os)
{
    os << RobberType << std::endl;
    NPC::save(os);
}

// Метод для сражения с медведем
bool Robber::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, true);
    return true;
}

// Метод для сражения с волком
bool Robber::fight(std::shared_ptr<Wolf> other)
{
    fight_notify(other, false);
    return false;
}

// Метод для сражения с другим грабителем
bool Robber::fight(std::shared_ptr<Robber> other)
{
    fight_notify(other, false);
    return false;
}

// Перегрузка оператора вывода для вывода информации о грабителе
std::ostream &operator<<(std::ostream &os, Robber &robber)
{
    os << "robber 🦹‍: " << *static_cast<NPC*>(&robber) << std::endl;
    return os;
}
