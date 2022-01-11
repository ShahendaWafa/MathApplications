#include <SFML/Graphics.hpp>
#include <math.h>
#define Pi 22/7.0f

sf::ConvexShape getCircle(sf::Vector2f center, float radius, float dir)
{
    int pointsCount = 100;
    float deltaAngle = (2.0f * Pi) / pointsCount;

    float angle = 0;
    int pts = 1;
    sf::ConvexShape circle(pts);
    circle.setPointCount(pts);
    circle.setPoint(0, center);

    for (int i = 1; i < pointsCount; i++)
    {
        float x = radius * cos(angle + dir - Pi / 6) + center.x;
        float y = radius * sin(angle + dir - Pi / 6) + center.y;
        if (angle <= Pi / 3) {
            circle.setPointCount(++pts);
            circle.setPoint(pts - 1, sf::Vector2f(x, y));
        }
        angle += deltaAngle;
    }

    return circle;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::CircleShape circ(15, 30);
    sf::CircleShape otherCirc(15, 30);
    circ.setFillColor(sf::Color::Magenta);
    otherCirc.setFillColor(sf::Color::Yellow);

    sf::Vector2f circPos(300, 300), otherCircPos(500, 500);
    circ.setOrigin(15, 15);
    otherCirc.setPosition(otherCircPos);
    otherCirc.setOrigin(15, 15);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    circPos.x -= 10;
                    break;
                case sf::Keyboard::Right:
                    circPos.x += 10;
                    break;
                case sf::Keyboard::Up:
                    circPos.y -= 10;
                    break;
                case sf::Keyboard::Down:
                    circPos.y += 10;
                    break;
                }
            default:
                break;
            }
        }
        circ.setPosition(circPos);

        sf::Vector2f forward(mousePos.x - circPos.x, mousePos.y - circPos.y);
        sf::Vector2f yellowCirc(otherCircPos.x - circPos.x, otherCircPos.y - circPos.y);

        float f = sqrt((forward.x * forward.x) + (forward.y * forward.y));
        float y = sqrt((yellowCirc.x * yellowCirc.x) + (yellowCirc.y * yellowCirc.y));

        float angleRotation = atan2(forward.y, forward.x);
        sf::ConvexShape shape = getCircle(circPos, 100, angleRotation);

        float angleView = (yellowCirc.x * forward.x + yellowCirc.y * forward.y) / (f * y);

        float d = sqrt(pow((circPos.x - otherCircPos.x), 2) + pow((circPos.y - otherCircPos.y), 2));

        if (angleView >= cos(Pi / 6) && d < 100) {
            shape.setFillColor(sf::Color::Yellow);
        }
        else {
            shape.setFillColor(sf::Color::Cyan);
        }

        window.draw(shape);
        window.draw(circ);
        window.draw(otherCirc);

        window.display();
        window.clear();
    }

    return 0;
}