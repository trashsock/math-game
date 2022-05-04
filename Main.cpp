//a ball bounces around from rectangle to rectangle in a circular path until window is closed
//i learned about push_back and ranged-based for loops from geeksforgeeks.org
//push_back()- https://www.geeksforgeeks.org/vectorpush_back-vectorpop_back-c-stl/
//ranged-based for loops- https://www.geeksforgeeks.org/range-based-loop-c/

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>

//window size
const int winx = 380;
const int winy = 380;

int main()
{
    sf::RenderWindow window({ winx, winy }, "challenge assignment week 5");

     //making board of rectangle pieces
    std::vector<sf::Vector2f> rectPieces;
    rectPieces.push_back({ 75, 75 });
    rectPieces.push_back({ 150, 50 });
    rectPieces.push_back({ 250, 50 });
    rectPieces.push_back({ 325, 75 });
    rectPieces.push_back({ 350, 150 });
    rectPieces.push_back({ 350, 250 });
    rectPieces.push_back({ 325, 325 });
    rectPieces.push_back({ 250, 350 });
    rectPieces.push_back({ 150, 350 });
    rectPieces.push_back({ 75, 325 });
    rectPieces.push_back({ 50, 250 });
    rectPieces.push_back({ 50, 150 });

    //rectangle
    sf::RectangleShape rect(sf::Vector2f(35.f, 14.f));
    rect.setFillColor(sf::Color(0,255,128));
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(2.f);
    rect.setOrigin(25.f, 25.f);

    //ball
    sf::CircleShape ball(15.f);
    ball.setFillColor(sf::Color(51,0,102));
    ball.setOutlineColor(sf::Color::Black);
    ball.setOutlineThickness(2.5f);
    ball.setOrigin(20.f, 20.f);

    float ballPos = 0.f;  //initiliasing ball's position to 0

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear({ 255,255,204 });  //setting bg colour

        //range-based for loop for setting initialised rectangles
        for (auto& pos : rectPieces)
        {
            rect.setPosition(pos);
            window.draw(rect);
        }

        //determining the point before and after the ball
        const sf::Vector2f prevPos = rectPieces[static_cast<std::size_t>(ballPos)];
        const sf::Vector2f nextPos = rectPieces[static_cast<std::size_t>(ballPos + 1) % rectPieces.size()];
        //determining the position between rectangles
        const float step = ballPos - static_cast<std::size_t>(ballPos);
        //parabolic jumping path of ball between rectangles
        const sf::Vector2f jump(0, 25.f * (2.f * (step - .5)) * (2.f * (step - .5)) - 25.f);
        ball.setPosition(prevPos + (nextPos - prevPos) * step + jump);
        window.draw(ball);
        window.display();  

        //ball velocity
        if ((ballPos = ballPos + .001f) > rectPieces.size())
        {
            ballPos = ballPos - rectPieces.size();
        }
    }
}