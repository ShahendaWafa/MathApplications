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

float lerp(float start, float end, float t) {
    return t * (end - start) + start;
}

sf::Vector2f lerpPosition(sf::Vector2f start, sf::Vector2f end, float t)
{
    sf::Vector2f position;
    position.x = lerp(start.x, end.x, t);
    position.y = lerp(start.y, end.y, t);

    return position;
}

sf::Color lerpColor(sf::Color start, sf::Color end, float t)
{
    sf::Color color;
    color.r = lerp(start.r, end.r, t);
    color.g = lerp(start.g, end.g, t);
    color.b = lerp(start.b, end.b, t);

    return color;
}

sf::VertexArray bezierCurve(sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
    int pointsCount = 30;
    float delta = 1.f / (pointsCount - 1);
    float t = 0;

    sf::VertexArray curve(sf::LineStrip, pointsCount);
    for (int i = 0; i < pointsCount; i++) {
        sf::Vector2f p01 = lerpPosition(p0, p1, t);
        sf::Vector2f p12 = lerpPosition(p1, p2, t);
        sf::Vector2f p23 = lerpPosition(p2, p3, t);

        sf::Vector2f p012 = lerpPosition(p01, p12, t);
        sf::Vector2f p123 = lerpPosition(p12, p23, t);

        curve[i] = lerpPosition(p012, p123, t);
        curve[i].color = lerpColor(sf::Color::Magenta, sf::Color::Cyan, t);

        t += delta;
    }
    return curve;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    sf::VertexArray lines(sf::LinesStrip, 4);
    sf::Vector2f p0(50, 550);
    sf::Vector2f p1(50, 50);
    sf::Vector2f p2(550, 50);
    sf::Vector2f p3(550, 550);

    lines[0] = p0;
    lines[1] = p1;
    lines[2] = p2;
    lines[3] = p3;

    Point c0, c1, c2, c3;
    c0.setPosition(p0);
    c1.setPosition(p1);
    c2.setPosition(p2);
    c3.setPosition(p3);

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
                c2.Begindrag(mousePosition);
                c3.Begindrag(mousePosition);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseOver = false;
                c0.stopDragging();
                c1.stopDragging();
                c2.stopDragging();
                c3.stopDragging();
            }
        }

        if (mouseOver) {
            c0.drag(mousePosition);
            c1.drag(mousePosition);
            c2.drag(mousePosition);
            c3.drag(mousePosition);

            p0 = c0.circle.getPosition();
            p1 = c1.circle.getPosition();
            p2 = c2.circle.getPosition();
            p3 = c3.circle.getPosition();

            lines[0].position = p0;
            lines[1].position = p1;
            lines[2].position = p2;
            lines[3].position = p3;

        }

        window.draw(lines);
        window.draw(bezierCurve(p0, p1, p2, p3));
        window.draw(c0.circle);
        window.draw(c1.circle);
        window.draw(c2.circle);
        window.draw(c3.circle);
        window.display();
        window.clear();
    }

    return 0;
}