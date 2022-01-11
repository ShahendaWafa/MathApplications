#include <SFML/Graphics.hpp>

float lerp(float start, float end, float t) {
    return t * (end - start) + start;
}

float inverseLerp(float start, float end, float pos) {
    return (pos - start) / (end - start);
}

sf::Vector2f lerpPosition(sf::Vector2f start, sf::Vector2f end, float t)
{
    sf::Vector2f position;
    position.x = lerp(start.x, end.x, t);
    position.y = lerp(start.y, end.y, t);

    return position;
}

sf::Color lerpColor(sf::Color start, sf::Color end, float t) {
    sf::Color color;
    color.r = lerp(start.r, end.r, t);
    color.g = lerp(start.g, end.g, t);
    color.b = lerp(start.b, end.b, t);

    return color;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::RectangleShape box(sf::Vector2f(100, 60));
    sf::VertexArray triangle(sf::Triangles, 3);

    sf::Vector2f pos0(0, 400);
    sf::Vector2f pos1(400, 400);
    sf::Vector2f pos2(200, 0);

    triangle[0].position = pos0;
    triangle[1].position = pos1;
    triangle[2].position = pos2;

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f mousePos;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == event.MouseButtonPressed) {
                mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
                float t = inverseLerp(0, 400, mousePos.y);
                sf::Vector2f leftPos = lerpPosition(pos2, pos0, t);
                sf::Vector2f rightPos = lerpPosition(pos2, pos1, t);

                sf::Color leftCol = lerpColor(triangle[2].color, triangle[0].color, t);
                sf::Color rightCol = lerpColor(triangle[2].color, triangle[1].color, t);

                t = inverseLerp(leftPos.x, rightPos.x, mousePos.x);
                sf::Color boxColor = lerpColor(leftCol, rightCol, t);
                if (t <= 1 && t >= 0)
                    box.setFillColor(boxColor);
            }
        }

        window.clear();
        window.draw(triangle);
        window.draw(box);
        window.display();
    }

    return 0;
}