#include "Simulation.h"
#include <iostream>
#include <chrono>

Simulation::Simulation(sf::Vector2u windowSize) : window(sf::VideoMode(windowSize.x,windowSize.y),"Simulation",sf::Style::Fullscreen)
{
	// Framerate limit
	//window.setFramerateLimit(60);
	this->panning = false;
	// Default zoom equal 1.0 scale
	this->zoomLevel = 1.0f;
	// Movement controlls
	simulationView.setSize(float(windowSize.x), float(windowSize.y));
	simulationView.move(-float(windowSize.x / 2), -float(windowSize.y) / 2);
	simulationView.zoom(zoomLevel);	
	// Create new image with size equal to screen resolution
	image.create(windowSize.x, windowSize.y,sf::Color::White);
	clearImage.create(windowSize.x, windowSize.y, sf::Color::White);
	texture.create(windowSize.x, windowSize.y);
	sprite.setTexture(texture);
	// Spawn new cells
	this->spawning = false;
	this->cellType = CellTypes::SAND;
}

void Simulation::run()
{
	while (window.isOpen())
	{
		auto t_start = std::chrono::high_resolution_clock::now();
		image = clearImage;
		window.clear(sf::Color::White);
		update();
		auto t_end = std::chrono::high_resolution_clock::now();
		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
		std::cout << "Elapsed time: " << elapsed_time_ms << std::endl;
		draw();
		window.display();
		pollEvent();

	}
}

void Simulation::pollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::MouseMoved)
		{
			if (panning)
			{
				// Get mouse offset and move simulation view according to it and zoom level
				sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(window) - this->panningAnchor);
				simulationView.move(-1.0f * pos * this->zoomLevel);
				panningAnchor = sf::Mouse::getPosition(window);
			}
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == sf::Mouse::Middle)
			{
				if (!panning)
				{
					// Set panning flag and panning starting location
					panning = true;
					panningAnchor = sf::Mouse::getPosition(window);
				}
			}
			else if (e.mouseButton.button == sf::Mouse::Left)
			{
				spawning = true;
			}
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			else if (e.key.code == sf::Keyboard::Num0)
			{
				cellType = CellTypes::EMPTY;
			}
			else if (e.key.code == sf::Keyboard::Num1)
			{
				cellType = CellTypes::SAND;
			}
			else if (e.key.code == sf::Keyboard::Num2)
			{
				cellType = CellTypes::STONE;
			}
			else if (e.key.code == sf::Keyboard::Num3)
			{
				cellType = CellTypes::WATER;
			}
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			if (e.mouseButton.button == sf::Mouse::Middle)
			{
				// Release panning
				panning = false;
			}
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				spawning = false;
			}
		}
		// Zooming
		if (e.type == sf::Event::MouseWheelMoved)
		{
			if (e.mouseWheel.delta < 0)
			{
				simulationView.zoom(2.0f);
				zoomLevel *= 2.0f;
			}
			else
			{
				simulationView.zoom(0.5f);
				zoomLevel *= 0.5f;
			}
		}
	}
	if (spawning)
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		for (int i = 0; i < 50; i++)
		{
			manager.spawnCell(cellType, mousePos);
			mousePos.x++;
		}
	}
}

void Simulation::update()
{
	// Update current view position on window
	window.setView(simulationView);
	// Update cells
	manager.update(image,window.mapPixelToCoords(sf::Vector2i(0, 0)), sf::Vector2f(window.getSize()));
}

void Simulation::draw()
{
	// Update texture with new pixel values
	texture.update(image);
	// Set Sprite relative to view location
	sprite.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
	// Draw pixel image on screen
	window.draw(sprite);
	// Draw active Chunks
	manager.draw(window);
}