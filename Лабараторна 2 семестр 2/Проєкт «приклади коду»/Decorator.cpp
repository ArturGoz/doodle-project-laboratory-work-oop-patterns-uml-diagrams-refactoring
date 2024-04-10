#include <iostream>
#include <string>

//патерн “Декоратор” реалізований наступним чином:
//Базовий інтерфейс Компонент(Component) : Це інтерфейс, який визначає поведінку, яка буде декорована.Він має метод Operation().
// 
//Конкретний Компонент(ConcreteComponent) : Це клас, який реалізує базовий інтерфейс.Він визначає поведінку, яку ми будемо декорувати.
// 
//Базовий Декоратор(Decorator) : Це абстрактний клас, який також реалізує інтерфейс Component і має посилання на об’єкт Component.
// Він переопределяє метод Operation() так, щоб викликати цей метод у об’єкта Component.
// 
//Конкретні Декоратори(ConcreteDecoratorA і ConcreteDecoratorB) : Це класи, які реалізують Decorator.
//Вони додають нову поведінку до методу Operation().

//Переваги використання патерну Декоратор :
//
//Ви можете додавати або видаляти обов’язки об’єкта під час виконання, не змінюючи його клас.
//Ви можете використовувати різні варіації об’єкта, змінюючи лише обгортку.
//Ви можете вкладати декоратори один в одного, отримуючи тим самим багато комбінацій поведінки.
//Недоліки використання патерну Декоратор :
//
//Важко налаштувати об’єкти, які були обгорнуті декораторами.
//Багато малих об’єктів в коді можуть ускладнити розуміння програми.


// Базовий інтерфейс Компонент
class Component {
public:
    virtual ~Component() {}
    virtual std::string Operation() const = 0;
};

// Конкретний Компонент
class ConcreteComponent : public Component {
public:
    std::string Operation() const override {
        return "ConcreteComponent";
    }
};

// Базовий Декоратор
class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* c) : component(c) {}
    std::string Operation() const override {
        return this->component->Operation();
    }
};

// Конкретний Декоратор A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* c) : Decorator(c) {}
    std::string Operation() const override {
        return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
    }
};

// Конкретний Декоратор B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* c) : Decorator(c) {}
    std::string Operation() const override {
        return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
    }
};

void ClientCode(Component* component) {
    std::cout << "RESULT: " << component->Operation();
}

int main() {
    Component* simple = new ConcreteComponent;
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    ClientCode(decorator2);
    delete simple;
    delete decorator1;
    delete decorator2;
    return 0;
}
