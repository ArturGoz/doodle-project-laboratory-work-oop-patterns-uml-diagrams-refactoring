#include <iostream>
#include <string>

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
