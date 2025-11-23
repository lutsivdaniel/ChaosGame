// Chaos Game - Sierpinski Triangle
// Partner 1: Brandon Tautuan
// Partner 2: Daniel Lutsiv

// Include important C++ libraries here
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <optional>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

enum GameMode
{
	MODE_MENU,
	MODE_TRIANGLE,
	MODE_SQUARE,
	MODE_PENTAGON,
	MODE_HEXAGON
};

float getRatio(int vertexCount)
{
	if (vertexCount == 3) return 0.5f;
	if (vertexCount == 4) return 0.5f;
	if (vertexCount == 5)
	{
		const float phi = 1.6180339887f;
		return 1.0f / phi;
	}
	if (vertexCount == 6) return 2.0f / 3.0f;
	if (vertexCount == 7) return 0.692f;
	if (vertexCount == 8) return 0.707f;
	if (vertexCount == 9) return 0.742f;
	if (vertexCount == 10) return 0.764f;
	return 0.5f;
}

int main()
{
	// Create a video mode object
	VideoMode vm(Vector2u(1920, 1080));
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	GameMode mode = MODE_MENU;
	int vertexCount = 0;
	int lastVertex = -1;

	Font font;
	if (!font.openFromFile("arial.ttf"))
	{
		cout << "Error loading font" << endl;
	}

	Text instructions(font);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::White);
	instructions.setPosition(Vector2f(10.f, 10.f));
	instructions.setString("T: triangle, S: square, P: pentagon, H: hexagon\nPress R to reset, ESC to quit");

	srand(static_cast<unsigned>(time(nullptr)));

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		while (auto event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (auto* keyPressed = event->getIf<Event::KeyPressed>())
			{
				if (keyPressed->code == Keyboard::Key::Escape)
				{
					window.close();
				}

				if (keyPressed->code == Keyboard::Key::R)
				{
					mode = MODE_MENU;
					vertexCount = 0;
					vertices.clear();
					points.clear();
					lastVertex = -1;
				}

				if (mode == MODE_MENU)
				{
					if (keyPressed->code == Keyboard::Key::T)
					{
						mode = MODE_TRIANGLE;
						vertexCount = 3;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
					else if (keyPressed->code == Keyboard::Key::S)
					{
						mode = MODE_SQUARE;
						vertexCount = 4;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
					else if (keyPressed->code == Keyboard::Key::P)
					{
						mode = MODE_PENTAGON;
						vertexCount = 5;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
					else if (keyPressed->code == Keyboard::Key::H)
					{
						mode = MODE_HEXAGON;
						vertexCount = 6;
						vertices.clear();
						points.clear();
						lastVertex = -1;
					}
				}
			}
			if (auto* mousePressed = event->getIf<Event::MouseButtonPressed>())
			{
				if (mousePressed->button == Mouse::Button::Left)
				{
					Vector2i mousePos = mousePressed->position;
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << mousePos.x << std::endl;
					std::cout << "mouse y: " << mousePos.y << std::endl;

					if (mode == MODE_TRIANGLE || mode == MODE_SQUARE || mode == MODE_PENTAGON || mode == MODE_HEXAGON)
					{
						float mx = static_cast<float>(mousePos.x);
						float my = static_cast<float>(mousePos.y);

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



		if (points.size() > 0 && static_cast<int>(vertices.size()) == vertexCount && vertexCount > 0)
		{
			float r = getRatio(vertexCount);

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
					current.x + r * (v.x - current.x),
					current.y + r * (v.y - current.y)
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
			instructions.setString("T: triangle, S: square, P: pentagon, H: hexagon\nPress R to reset, ESC to quit");
		}
		else
		{
			if (static_cast<int>(vertices.size()) < vertexCount)
			{
				if (mode == MODE_TRIANGLE)
					instructions.setString("Triangle mode\nClick 3 vertices\nPress R to reset, ESC to quit");
				else if (mode == MODE_SQUARE)
					instructions.setString("Square mode\nClick 4 vertices\nPress R to reset, ESC to quit");
				else if (mode == MODE_PENTAGON)
					instructions.setString("Pentagon mode\nClick 5 vertices\nPress R to reset, ESC to quit");
				else if (mode == MODE_HEXAGON)
					instructions.setString("Hexagon mode\nClick 6 vertices\nPress R to reset, ESC to quit");
			}
			else if (static_cast<int>(vertices.size()) == vertexCount && points.size() == 0)
			{
				instructions.setString("Click a final point to start the chaos game\nPress R to reset, ESC to quit");
			}
			else
			{
				instructions.setString("Chaos game running... Press R to reset, ESC to quit");
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
			pointShape.setPosition(Vector2f(points[i].x, points[i].y));
			pointShape.setFillColor(Color::Green);
			window.draw(pointShape);
		}

		window.draw(instructions);

		window.display();
	}
}
