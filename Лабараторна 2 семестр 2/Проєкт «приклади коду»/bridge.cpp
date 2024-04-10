#include <iostream>



//Приклад позичив у https://github.com/bubnicbf/phys_410/blob/8ffa08e5d9f3c0747249033caa041175981873f6/cpp/DesignPatterns/Structural/Bridge.cpp

//У наведеному  прикладі патерну Bridge на мові C++, ми використовуємо цей патерн для розділення абстракції(форми)
//  та її реалізації(API для малювання).
//
//Клас Shape є абстракцією, яка має методи draw() та resizeByPercentage().Ці методи визначають інтерфейс для малювання та зміни розміру форми.
//Клас CircleShape є уточненою абстракцією, яка реалізує методи draw() та resizeByPercentage() для круга.
//Клас DrawingAPI є реалізацією, яка має метод drawCircle().Цей метод визначає інтерфейс для малювання круга.
//Класи DrawingAPI1 та DrawingAPI2 є конкретними реалізаціями, які реалізують метод drawCircle() для двох різних API малювання.

//Переваги використання патерну Bridge :
//
//Він розділяє абстракцію та реалізацію на дві окремі ієрархії.
//Він поліпшує розширюваність.Можна незалежно розширювати абстракцію та реалізацію.
//Він додає динамічність, оскільки можна змінювати реалізацію в режимі реального часу.
//Недоліки використання патерну Bridge :
//
//Це може збільшити кількість системних класів.

// Implementor
class DrawingAPI {
public:
    virtual void drawCircle(double x, double y, double radius) = 0;
};

// ConcreteImplementor 1/2
class DrawingAPI1 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) {
        std::cout << "API1.circle at " << x << ':' << y << ' ' << radius << std::endl;
    }
};

// ConcreteImplementor 2/2
class DrawingAPI2 : public DrawingAPI {
public:
    void drawCircle(double x, double y, double radius) {
        std::cout << "API2.circle at " << x << ':' << y << ' ' << radius << std::endl;
    }
};

// Abstraction
class Shape {
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
    virtual void resizeByPercentage(double pct) = 0;
};

// Refined Abstraction
class CircleShape : public Shape {
public:
    CircleShape(double x, double y, double radius, DrawingAPI* drawingAPI) :
        m_x(x), m_y(y), m_radius(radius), m_drawingAPI(drawingAPI) {}
    void draw() {
        m_drawingAPI->drawCircle(m_x, m_y, m_radius);
    }
    void resizeByPercentage(double pct) {
        m_radius *= pct;
    }
private:
    double m_x, m_y, m_radius;
    DrawingAPI* m_drawingAPI;
};

int main(void) {
    CircleShape circle1(1, 2, 3, new DrawingAPI1());
    CircleShape circle2(5, 7, 11, new DrawingAPI2());
    circle1.resizeByPercentage(2.5);
    circle2.resizeByPercentage(2.5);
    circle1.draw();
    circle2.draw();
    return 0;
}
