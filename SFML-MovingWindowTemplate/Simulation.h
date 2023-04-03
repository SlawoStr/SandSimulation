#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "ChunkManager.h"


class Simulation
{
public:
	Simulation(sf::Vector2u windowSize);
	void run();
private:
	void pollEvent();
	void update();
	void draw();
private:
	sf::RenderWindow window;
	// Panning varibales
	float zoomLevel;
	bool panning;
	sf::Vector2i panningAnchor;
	sf::View simulationView;
	// Current window position in global coordinates
	sf::Vector2f windStart;
	sf::Vector2f windEnd;
	// Drawing
	sf::Image image;
	sf::Image clearImage;
	sf::Texture texture;
	sf::Sprite sprite;
	ChunkManager manager;
	bool spawning;
	CellTypes cellType;
};
