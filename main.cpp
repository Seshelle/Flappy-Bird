#include <SFML/Graphics.hpp>
#include <stdlib.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(385, 600), "Flappy Birb");

	srand(1);

	double pipePos = 0;
	double pipe1H = 350;
	double pipe2H = 250;
	double birdPos = 300;
	double birdVel = 0;
	bool released = true;
	sf::FloatRect pipeBox1;
	sf::FloatRect pipeBox2;
	sf::FloatRect birdBox;

	sf::Texture screens;
	screens.loadFromFile("flappy-bird-game-screens.jpg");
	sf::Sprite title;
	title.setTexture(screens);
	title.setTextureRect(sf::IntRect(0, 0, 385, 684));


	//pipe1 points up, pipe2 points down
	sf::Texture pipes;
	pipes.loadFromFile("pipes.jpg");
	sf::Sprite pipe1;
	pipe1.setTexture(pipes);
	pipe1.setTextureRect(sf::IntRect(0, 449, 80, 278));

	sf::Sprite pipe2;
	pipe2.setTexture(pipes);
	pipe2.setTextureRect(sf::IntRect(0, 449, 80, 278));
	pipe2.setRotation(180);

	sf::Texture birbs;
	birbs.loadFromFile("Flappy_Birb.png");
	sf::Sprite birb;
	birb.setTexture(birbs);
	birb.setScale(0.5, 0.5);
	birb.setPosition(192, 300);



	sf::Vector2i pos;
	char gameMode = 't'; //title, instructions, playing

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			pos = sf::Mouse::getPosition(window);
			if (gameMode == 'i' && released == true){
				gameMode = 'p';
				title.setTextureRect(sf::IntRect(810, 0, 385, 684));
			}
			if (pos.x >= 61 && pos.x <= 165 && pos.y >= 475 && pos.y <= 510 && gameMode == 't'){
				gameMode = 'i';
				title.setTextureRect(sf::IntRect(405, 0, 385, 684));
				released = false;
			}
		}

		if (gameMode == 't'){
			title.setTextureRect(sf::IntRect(0, 0, 385, 684));
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			released = true;
		}

		window.clear();
		window.draw(title);

		if (gameMode == 'p'){

			birdVel -= 0.0001;
			birdPos -= birdVel;
			birb.setPosition(180, birdPos);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && released == true){
				birdVel = 0.1;
			}

			pipePos -= 0.02;
			if (pipePos <= -90){
				pipe1H = rand() % 163 + 322;
				pipe2H = rand() % 128 + 50;
				pipePos = 385;
			}

			pipeBox1 = pipe1.getGlobalBounds();
			pipeBox2 = pipe2.getGlobalBounds();
			birdBox = birb.getGlobalBounds();

			if (pipeBox1.intersects(birdBox) || pipeBox2.intersects(birdBox) || birdPos >= 500){
				gameMode = 't';
				birdPos = 300;
				birdVel = 0;
				pipe1H = 350;
				pipe2H = 250;
				pipePos = 0;
			}

			/*
			// get the bounding box of the entity
			sf::FloatRect boundingBox = entity.getGlobalBounds();

			// check collision with another box (like the bounding box of another entity)
			sf::FloatRect otherBox = ...;
			if (boundingBox.intersects(otherBox))
			{
				// collision!
			}
			*/

			pipe1.setPosition(pipePos, pipe1H);
			pipe2.setPosition(pipePos + 80, pipe2H);
			window.draw(pipe1);
			window.draw(pipe2);
			window.draw(birb);
		}

		window.display();
	}

	return 0;
}