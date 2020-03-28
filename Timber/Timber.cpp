// HelloSFML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>



using namespace sf;
void updateBranch(int seed);
	const int NUM_BRANCHES = 6;
	Sprite branches[NUM_BRANCHES];
	enum class side { LEFT, RIGHT,NONE };
	side brancheside[NUM_BRANCHES];


int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
	Texture textureBackgrond;
	textureBackgrond.loadFromFile("graphics/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(textureBackgrond);
	spriteBackground.setPosition(0, 0);
	Texture treeText;
	treeText.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(treeText);
	spriteTree.setPosition(810, 0);
	Texture beeText;
	beeText.loadFromFile("graphics/bee.png");
	Sprite beeSprite;
	beeSprite.setTexture(beeText);
	beeSprite.setPosition(0, 800);
	bool beeMoving = false;
	float beeSpeed = 0.0f;
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	Clock clock;
	RectangleShape timebar;
	float timebraWidth = 400;
	float timebarHeight = 80;
	timebar.setSize(Vector2f(timebraWidth, timebarHeight));
	timebar.setFillColor(Color::Red);
	timebar.setPosition(1920 / 2, 980);
	Time gameTimeTotal;
	float timeReaining = 6.0f;
	float widthPerSeconds = timebraWidth / timeReaining;
	bool paused = true;
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter to start");
	scoreText.setString("Score =0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
	}
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite playerSprite;
	playerSprite.setTexture(texturePlayer);
	playerSprite.setPosition(580, 720);
	side playerSide = side::LEFT;
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);
	const float AXE_LEFT = 700;
	const float AXE_RIGHT = 1075;

	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	bool acceptInput = false;
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);
	SoundBuffer outoftimeBuffer;
	outoftimeBuffer.loadFromFile("sound/out_of_time.wav");
	Sound oot;
	oot.setBuffer(outoftimeBuffer);





	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::KeyReleased && !paused) {
				acceptInput = true;
				//hide axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

			}
			
			
			

		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)) {
			if (paused) {
				paused = false;
				score = 0;
				timeReaining = 5;

				for (int j = 1; j < NUM_BRANCHES; j++)
				{
					brancheside[j] = side::NONE;

				}

				//hidden the rip
				spriteRIP.setPosition(675, 2000);
				playerSprite.setPosition(580, 720);
				acceptInput = true;

			}
			else {
				paused = true;
			}
			
		}
		if (acceptInput) {
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				playerSide = side::RIGHT;
				score++;
				timeReaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_RIGHT, spriteAxe.getPosition().y);
				playerSprite.setPosition(1200, 720);
				updateBranch(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;
				chop.play();

			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				playerSide = side::LEFT;
				score++;
				timeReaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_LEFT, spriteAxe.getPosition().y);
				playerSprite.setPosition(580, 720);
				updateBranch(score);
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;
				acceptInput = false;
				chop.play();

			}

		}
		if (!paused) {

			if (brancheside[5] == playerSide) {
				paused = true;
				acceptInput = false;
				playerSprite.setPosition(2000, 660);
				spriteRIP.setPosition(525, 769);
				messageText.setString("DIED!!!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				death.play();

		}
		Time dt = clock.restart();
		timeReaining -= dt.asSeconds();
		timebar.setSize(Vector2f(widthPerSeconds*timeReaining, timebarHeight));
		if (timeReaining < 0.0f) {
			paused = true;
			messageText.setString("Out Of Time!!!");
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			oot.play();
		}
		if (logActive) {
			spriteLog.setPosition(
				spriteLog.getPosition().x + (logSpeedX* dt.asSeconds()),
				spriteLog.getPosition().y + (logSpeedY*dt.asSeconds()));
			if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x>2000) {
				logActive = false;
				spriteLog.setPosition(810, 720);

			}
					

		}
		if (!beeMoving) {
			//fast is?
			srand((int)time(0) * 10);
			beeSpeed = (rand() % 200) + 200;
			//beeHeight
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			beeSprite.setPosition(2000, height);
			beeMoving = true;

		}
		else {
			beeSprite.setPosition(beeSprite.getPosition().x-(beeSpeed*dt.asSeconds()), beeSprite.getPosition().y);
			if (beeSprite.getPosition().x < -100) {
				beeMoving = false;
			}

		}
		
		if (!cloud1Active) {
			//Select fast
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200) ;
			//cloudHeight
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;


		}
		else {
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed*dt.asSeconds()), spriteCloud1.getPosition().y);
			if (spriteCloud1.getPosition().x > 1920) {
				cloud1Active = false;
			}
		}
		if (!cloud2Active) {
			//Select fast
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200) ;
			//cloudHeight
			srand((int)time(0) * 20);
			float height = (rand() % 200)+200;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;


		}
		else {
			spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed*dt.asSeconds()), spriteCloud2.getPosition().y);
			if (spriteCloud2.getPosition().x > 1920) {
				cloud2Active = false;
			}
		}
		if (!cloud3Active) {
			//Select fast
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200) ;
			//cloudHeight
			srand((int)time(0) * 10);
			float height = (rand() % 450)-150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;


		}
		else {
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed*dt.asSeconds()), spriteCloud3.getPosition().y);
			if (spriteCloud3.getPosition().x > 1920) {
				cloud3Active = false;
			}
		}
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());
		for (int i = 0; i < NUM_BRANCHES; i++) {
			float height = i * 150;
			if (brancheside[i] == side::LEFT) {
				branches[i].setPosition(610, height);
				branches[i].setRotation(180);

			}
			else if (brancheside[i] == side::RIGHT) {
				branches[i].setPosition(1330, height); 
				branches[i].setRotation(0);
			}
			else {
				branches[i].setPosition(3000, height);
			}
		}

		}
		window.clear();
		window.draw(spriteBackground);

		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		window.draw(beeSprite);
		window.draw(spriteTree);
		window.draw(playerSprite);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRIP);
		window.draw(scoreText);
		window.draw(timebar);
		if (paused) {
			window.draw(messageText);
		}

		window.display();
		

	}
	
	return 0;
}
void updateBranch(int seed) {
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		brancheside[j] = brancheside[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		brancheside[0] = side::LEFT;
		break;

	case 1:
		brancheside[0] = side::RIGHT;
		break;

	default:
		brancheside[0] = side::NONE;
		break;
	}


}

