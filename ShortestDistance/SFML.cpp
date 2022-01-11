#include <SFML/Graphics.hpp>

class Point {
public:
    bool isDragging = false;

    sf::CircleShape circle;
    Point() {
        circle.setRadius(10);
        circle.setOrigin(10, 10);
    }
    void setPosition(sf::Vector2f postion) {
        circle.setPosition(postion);
    }
    bool isMouseOver(sf::Vector2f mousePosition) {
        return circle.getGlobalBounds().contains(mousePosition);
    }
    void Begindrag(sf::Vector2f mousePosition) {
        isDragging = isMouseOver(mousePosition);
    }
    void drag(sf::Vector2f mousePosition) {
        if (isDragging)
            circle.setPosition(mousePosition);
    }
    void stopDragging() {
        isDragging = false;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::VertexArray lines(sf::LinesStrip, 2), completeLine(sf::LinesStrip, 2);
    sf::Vector2f p0(50, 300), p1(550, 300), circPos;

    sf::CircleShape circ(10, 10);
    circ.setOrigin(10, 10);
    circ.setFillColor(sf::Color::Magenta);

    lines[0] = p0;
    lines[1] = p1;

    Point c0, c1;
    c0.setPosition(p0);
    c1.setPosition(p1);

    sf::Vector2f cl0, cl1;

    float m, b;
    bool mouseOver = false;

    while (window.isOpen())
    {
        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                mouseOver = true;
                c0.Begindrag(mousePosition);
                c1.Begindrag(mousePosition);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseOver = false;
                c0.stopDragging();
                c1.stopDragging();
            }
        }

        if (mouseOver) {
            c0.drag(mousePosition);
            c1.drag(mousePosition);

            p0 = c0.circle.getPosition();
            p1 = c1.circle.getPosition();

            lines[0].position = p0;
            lines[1].position = p1;
        }

        b = p0.y - (p0.x * ((p1.y - p0.y) / (p1.x - p0.x)));
        m = (p0.y - p1.y) / (p0.x - p1.x);

        circPos.x = (mousePosition.x + (m * (mousePosition.y - b))) / ((m * m) + 1);
        circPos.y = ((m * (mousePosition.x + (m * mousePosition.y))) + b) / ((m * m) + 1);
        circ.setPosition(circPos);

        sf::Vector2f slope((p0.x - p1.x), (p0.y - p1.y));
        cl0.x = p0.x + (100 * slope.x);
        cl0.y = p0.y + (100 * slope.y);

        cl1.x = p0.x + (-100 * slope.x);
        cl1.y = p0.y + (-100 * slope.y);

        completeLine[0] = cl0;
        completeLine[1] = cl1;
        completeLine[0].color = sf::Color::Green;
        completeLine[1].color = sf::Color::Green;

        window.draw(completeLine);
        window.draw(circ);
        window.draw(lines);
        window.draw(c0.circle);
        window.draw(c1.circle);
        window.display();
        window.clear();
    }

    return 0;
}