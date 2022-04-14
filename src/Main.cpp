#include "Platform/Platform.hpp"
#include <string>

bool colision(sf::CircleShape c1, sf::CircleShape c2)
{
	if (c1.getPosition().x < c2.getPosition().x + 60 && c2.getPosition().x < c1.getPosition().x + 60 && c1.getPosition().y < c2.getPosition().y + 60 && c2.getPosition().y < c1.getPosition().y + 60)
		return true;

	return false;
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "My first window");
	srand(time(NULL));

	sf::Texture duck;
	if( !duck.loadFromFile("duck.jpeg") ) {
		std::cout << "Eroare la rata.\n";
	}
	duck.setSmooth(true);
	duck.setRepeated(false);
	int duckScore = 0;

	sf::Texture hog;
	if( !hog.loadFromFile("hog.jpeg") ) {
		std::cout << "Eroare la arici.\n";
	}
	hog.setSmooth(true);
	hog.setRepeated(false);
	int hogScore = 0;


	sf::CircleShape circle(30.f);
	circle.setPosition(rand() % 740, rand() % 540);
	circle.setTexture(&duck);

	sf::CircleShape food(30.f);
	food.setPosition(rand() % 740, rand() % 540);
	food.setTexture(&hog);

	bool finish = false;

	sf::Font font;
	sf::Font fontCifre;
	sf::Text text;
	sf::Text restart;
	sf::Text secondsText;
	sf::Text DuckText;
	sf::Text HogText;
	sf::Text HogScoreText;
	sf::Text DuckScoreText;

	if (!font.loadFromFile("retro.ttf"))
	{
		std::cout << "Eroare la font\n";
	}

	if (!fontCifre.loadFromFile("cifre.ttf"))
	{
		std::cout << "Eroare la font\n";
	}

	text.setFont(font);
	text.setString("GAME OVER");
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setPosition(130, 100);

	restart.setFont(font);
	restart.setString("press ENTER to play again");
	restart.setCharacterSize(20);
	restart.setFillColor(sf::Color::White);
	restart.setPosition(250, 400);

	secondsText.setFont(fontCifre);
	secondsText.setString("10");
	secondsText.setCharacterSize(100);
	secondsText.setFillColor(sf::Color::White);
	secondsText.setPosition(10, 10);


	DuckText.setFont(fontCifre);
	DuckText.setString("Duck: ");
	DuckText.setCharacterSize(50);
	DuckText.setFillColor(sf::Color::White);
	DuckText.setPosition(250, 0);

	DuckScoreText.setFont(fontCifre);
	DuckScoreText.setString(std::to_string(duckScore));
	DuckScoreText.setCharacterSize(50);
	DuckScoreText.setFillColor(sf::Color::White);
	DuckScoreText.setPosition(370, 0);


	HogText.setFont(fontCifre);
	HogText.setString("Hog: ");
	HogText.setCharacterSize(50);
	HogText.setFillColor(sf::Color::White);
	HogText.setPosition(450, 0);

	HogScoreText.setFont(fontCifre);
	HogScoreText.setString(std::to_string(hogScore));
	HogScoreText.setCharacterSize(50);
	HogScoreText.setFillColor(sf::Color::White);
	HogScoreText.setPosition(550, 0);

	sf::Clock clock;
	int seconds = 10;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color::Black);

		if( seconds < 0 ) {
			finish = true;
			seconds = 10;
			hogScore++;
			HogScoreText.setString(std::to_string(hogScore));
			text.setString("Hog win!");
		}

		if (finish)
		{
			window.draw(text);
			window.draw(restart);
			seconds = 11;
			secondsText.setString( std::to_string(seconds) );

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				finish = false;
				circle.setPosition(rand() % 740, rand() % 540);
				food.setPosition(rand() % 740, rand() % 540);
			}
		}

		//circle moving
		if (!finish)
		{
			sf::Time elapsed1 = clock.getElapsedTime();
			// std::cout << elapsed1.asSeconds() << '\n';
			if( elapsed1.asSeconds() >= 1.0000 ) {
				seconds--;
				secondsText.setString( std::to_string(seconds) );
				clock.restart();
			}


			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && circle.getPosition().x > 0)
			{
				circle.setPosition(circle.getPosition().x - 1, circle.getPosition().y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && circle.getPosition().x < 740)
			{
				circle.setPosition(circle.getPosition().x + 1, circle.getPosition().y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && circle.getPosition().y < 540)
			{
				circle.setPosition(circle.getPosition().x, circle.getPosition().y + 1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && circle.getPosition().y > 0)
			{
				circle.setPosition(circle.getPosition().x, circle.getPosition().y - 1);
			}

			//food moving
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && food.getPosition().x > 0)
			{
				food.setPosition(food.getPosition().x - 1, food.getPosition().y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && food.getPosition().x < 740)
			{
				food.setPosition(food.getPosition().x + 1, food.getPosition().y);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && food.getPosition().y < 540)
			{
				food.setPosition(food.getPosition().x, food.getPosition().y + 1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && food.getPosition().y > 0)
			{
				food.setPosition(food.getPosition().x, food.getPosition().y - 1);
			}

			window.draw(circle);
			window.draw(food);
			window.draw(secondsText);
			window.draw(DuckText);
			window.draw(HogText);
			window.draw(HogScoreText);
			window.draw(DuckScoreText);

			if (colision(circle, food)) {
				duckScore++;
				DuckScoreText.setString(std::to_string(duckScore));
				text.setString("Duck win!");
				finish = true;
			}
		}

		window.display();
	}

	return 0;
}
