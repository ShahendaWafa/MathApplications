#include <SFML/Graphics.hpp>
#include <iostream>

#define PI 22/7.0f

sf::ConvexShape getCircle(sf::Vector2f center, float radius, float angle, float dir)
{
    int pointsCount = 300;
    float deltaAngle = (2.0f * PI) / pointsCount;

    float angle2 = angle;
    int pts = 1;
    sf::ConvexShape circle(pts);
    circle.setPointCount(pts);
    circle.setPoint(0, center);

    for (int i = 1; i < pointsCount; i++)
    {
        float x = radius * cos(angle + dir) + center.x;
        float y = radius * sin(angle + dir) + center.y;
        //std:: cout << x << " " << y << std:: endl;
        circle.setPointCount(++pts);
        circle.setPoint(i, sf::Vector2f(x, y));

        //std::cout << angle << std::endl;
        angle += deltaAngle;
        if (angle > ((2 * PI) - angle2))
            break;
    }

    return circle;
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::ConvexShape shape;
    window.setFramerateLimit(10);
    float angle = 0;
    float dir = 0;
    sf::Clock clock;
    float t;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = PI;
                    break;
                case sf::Keyboard::Right:
                    dir = 0;
                    break;
                case sf::Keyboard::Up:
                    dir = 3 * (PI / 2);
                    break;
                case sf::Keyboard::Down:
                    dir = PI / 2;
                    break;
                }
            default:
                break;
            }
        }

        t = clock.getElapsedTime().asMilliseconds();
        //sf::sleep(sf::milliseconds(100));
        angle = (PI / 6) * abs(sin(t));

        shape = getCircle(sf::Vector2f(125.f, 125.f), 100, angle, dir);

        shape.setOrigin(25, 25);
        shape.setPosition(100, 100);
        shape.setFillColor(sf::Color::Yellow);
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}