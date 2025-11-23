// Chaos Game - Sierpinski Triangle
// Partner 1: Brandon Tautuan
// Partner 2: Daniel Lutsiv

// Include important C++ libraries here
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

enum GameMode
{
	MODE_MENU,
	MODE_TRIANGLE,
	MODE_SQUARE
};

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	GameMode mode = MODE_MENU;
	int vertexCount = 0;
	int lastVertex = -1;

	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cout << "Error loading font" << endl;
	}

	Text instructions;
	instructions.setFont(font);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::White);
	instructions.setPosition(10.f, 10.f);
	instructions.setString("Click T for triangle, S for square");

	srand(static_cast<unsigned>(time(nullptr)));

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}

				if (mode == MODE_MENU)
				{
					if (event.key.code == Keyboard::T)
					{
						mode = MODE_TRIANGLE;
						vertexCount = 3;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
					else if (event.key.code == Keyboard::S)
					{
						mode = MODE_SQUARE;
						vertexCount = 4;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (mode == MODE_TRIANGLE || mode == MODE_SQUARE)
					{
						float mx = static_cast<float>(event.mouseButton.x);
						float my = static_cast<float>(event.mouseButton.y);

						if (static_cast<int>(vertices.size()) < vertexCount)
						{
							vertices.push_back(Vector2f(mx, my));
						}
						else if (static_cast<int>(vertices.size()) == vertexCount && points.size() == 0)
						{
							points.push_back(Vector2f(mx, my));
						}
					}
				}
			}
		}



		if (points.size() > 0 && static_cast<int>(vertices.size()) == vertexCount)
		{
			for (int i = 0 ; i < 200; ++i)
			{
				Vector2f current = points.back();
				int index = rand() % vertexCount;
				if (vertexCount >= 4)
				{
					while (index == lastVertex)
					{
						index = rand() % vertexCount;
					}
				}

				lastVertex = index;

				Vector2f v = vertices[index];

				Vector2f newPoint(
					(current.x + v.x) / 2.f,
					(current.y + v.y) / 2.f
				);

				points.push_back(newPoint);
			}
		}
		/*
		****************************************
		Update
		****************************************
		*/



		if (mode == MODE_MENU)
		{
			instructions.setString("Click T for triangle, S for square\nClick ESC to quit");
		}
		else
		{
			if (static_cast<int>(vertices.size()) < vertexCount)
			{
				if (mode == MODE_TRIANGLE)
					instructions.setString("Triangle mode\nClick 3 vertices");
				else
					instructions.setString("Square mode\nClick 4 vertices");
			}
			else if (static_cast<int>(vertices.size()) == vertexCount && points.size() == 0)
			{
				instructions.setString("Click a final point to start the chaos game");
			}
			else
			{
				instructions.setString("Chaos game running... Press ESC to quit");
			}
		}


		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();

		for (int i = 0; i < static_cast<int>(vertices.size()); i++)
		{
			RectangleShape rect(Vector2f(10.f, 10.f));
			rect.setPosition(Vector2f(vertices[i].x - 5.f, vertices[i].y - 5.f));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}

		for (int i = 0; i < static_cast<int>(points.size()); i++)
		{
			RectangleShape pointShape(Vector2f(2.f, 2.f));
			pointShape.setPosition(points[i].x, points[i].y);
			pointShape.setFillColor(Color::Green);
			window.draw(pointShape);
		}

		window.draw(instructions);

		window.display();
	}
}
