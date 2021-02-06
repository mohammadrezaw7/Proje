#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <string>
using namespace std;
class Ship
{
public:
    Ship(const int id,float speed)
{
    //load kardan ship va upload o andze ddn
    alive=true;
    
    if(!texture.loadFromFile("/home/mohammad/Desktop/Spaceinvader/medium_ship.png"))
       throw invalid_argument("Ship not loaded!");
    
    
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.4,0.4));
}

void setLocation(float xpos, float ypos) //makane ship
{
    sprite.setPosition(xpos,ypos);
}

sf::Sprite & getSprite() 
{
    return sprite;
}

void kill()  
{
    alive = false;
}

bool isAlive()
{
    return alive;
}

void draw(sf::RenderWindow &win) //keshidan ship
{
    
    sprite.setTexture(texture);
    win.draw(sprite);
}

void respawn()
{
    alive=true;
}
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;
};

class Tir
{
public:
    Tir(const int id,float speed)
{
    
    alive = false;
    
    //bargozari tir o andze ddn
    if(!texture.loadFromFile("/home/mohammad/Desktop/Spaceinvader/bullet.png"))
        throw invalid_argument("Bullet not loaded!");
    
    sprite.scale(sf::Vector2f(0.3,0.3));
}

sf::Sprite & getSprite()
{
    return sprite;
}

void setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos,ypos);
}

void kill()
{
    alive = false;
}

bool isAlive()
{
    return alive;
}

void spawn(bool bul)
{
    alive=bul;
}

void draw(sf::RenderWindow &win)
{
    //kshidan
    sprite.setTexture(texture);
    win.draw(sprite);
}

private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;

};

class Enemy
{
public:
   Enemy();
   Enemy(const int id,float sp)   //aliens
{
    
    alive = true;

    speed = sp;
    
    // load o andze ddn
    if(!texture.loadFromFile("/home/mohammad/Desktop/Spaceinvader/alien_100.png"))
        throw invalid_argument("Enemy not loaded!");
    
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.8,0.8));
}

sf::Sprite & getSprite()
{
    return sprite;
}

void setLocation(float xpos, float ypos)
{
    sprite.setPosition(xpos,ypos);
}

void kill()
{
    alive = false;
}

bool isAlive()
{
    return alive;
}

void draw(sf::RenderWindow &win)
{
    //keshidan
    sprite.setTexture(texture);
    
    win.draw(sprite);
}

float getSpeed() const
{
    return speed;
}
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;
    float speed;
};

class CollisionManager
{
public:
bool collidesWith(Ship &obj1, Enemy &obj2)
{
    //gereftan andazeye ship b surate y mostatil
    sf::FloatRect ship;
    //gereftan noghteye bala chap
    ship.left = obj1.getSprite().getPosition().x+10;
    ship.top = obj1.getSprite().getPosition().y+10;
    //gereftane noghte pain rast
    ship.width = obj1.getSprite().getGlobalBounds().width-10;
    ship.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //gereftan andazeye alien b surate y mostatil
    sf::FloatRect alien;
    //bala chap
    alien.left = obj2.getSprite().getPosition().x;
    alien.top = obj2.getSprite().getPosition().y;
    //pain rast
    alien.width = obj2.getSprite().getGlobalBounds().width;
    alien.height =obj2.getSprite().getGlobalBounds().height;
        
    return ship.intersects(alien);
    
}

bool collidesWith2(Tir &obj1, Enemy &obj2)
{
    //gereftan andazeye tir b surate y mostatil
    sf::FloatRect Tir;
    //gereftan noghteye bala chap
    Tir.left = obj1.getSprite().getPosition().x+10;
    Tir.top = obj1.getSprite().getPosition().y+10;
    //gereftane noghte pain rast
    Tir.width = obj1.getSprite().getGlobalBounds().width-10;
    Tir.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //gereftan andazeye alien b surate y mostatil
    sf::FloatRect alien;
    //gereftan noghteye bala chap
    alien.left = obj2.getSprite().getPosition().x;
    alien.top = obj2.getSprite().getPosition().y;
   //gereftane noghte pain rast
    alien.width = obj2.getSprite().getGlobalBounds().width;
    alien.height =obj2.getSprite().getGlobalBounds().height;
    
    return Tir.intersects(alien);
  }  
};


class LoseScreen
{
public:
    LoseScreen()
{
    //loade screen gameove
    if(!texture.loadFromFile("/home/mohammad/Desktop/Spaceinvader/you_lose.png"))
        throw invalid_argument("Game over screen not loaded!");
    
    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(1,1));
    sprite.setPosition(100,100);
}

sf::Sprite & getSprite()
{
    return sprite;
}

void setLocation(float xpos,float ypos)
{
    sprite.setPosition(xpos,ypos);
}

void draw(sf::RenderWindow &win)
{
    sprite.setTexture(texture);
    win.draw(sprite);
}


private:
    sf::Sprite sprite;
    sf::Texture texture;
};


class WinScreen
{
public:
   WinScreen()
{
    // loade safe win
    if(!texture.loadFromFile("/home/mohammad/Desktop/Spaceinvader/you_win.png"))
        throw invalid_argument("Game over screen not loaded!");
    
    sprite.scale(sf::Vector2f(1,1));
    sprite.setPosition(100,100);
}

sf::Sprite & getSprite()
{
    return sprite;
}

void setLocation(float xpos,float ypos)
{
    sprite.setPosition(xpos,ypos);
}

void draw(sf::RenderWindow &win)
{
    sprite.setTexture(texture);
    win.draw(sprite);
}
private:
    sf::Sprite sprite;
    sf::Texture texture;
};


class SoundManager
{
public:
   SoundManager()
{
    //loade  lazer
    if (!lazerBuffer.loadFromFile("/home/mohammad/Desktop/Spaceinvader/space_gun.wav"))
        throw invalid_argument("Lazer sound not loaded!");

    //loade explosion
    if (!explosionBuffer.loadFromFile("/home/mohammad/Desktop/Spaceinvader/ship_explode.wav"))
        throw invalid_argument("Explosion sound not loaded!");

    //loade reward
    if (!rewardBuffer.loadFromFile("/home/mohammad/Desktop/Spaceinvader/reward.wav"))
        throw invalid_argument("Reward sound not loaded!");
    

    if (!music.openFromFile("/home/mohammad/Desktop/Spaceinvader/background.wav"))
        throw invalid_argument("Explosion sound not loaded!");
}

void playBackgroundMusic()
{
    music.setLoop(true);
    music.play();
}

void pauseBackgroundMusic()
{
    music.pause();
}

void playLazer()
{
    lazerSound.setBuffer(lazerBuffer);
    lazerSound.play();
}

void playExplosion()
{
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.play();
}

void playReward()
{
    rewardSound.setBuffer(rewardBuffer);
    rewardSound.play();
}
private:
    sf::SoundBuffer lazerBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::SoundBuffer rewardBuffer;
    sf::Music music;
    sf::Sound lazerSound;
    sf::Sound explosionSound;
    sf::Sound rewardSound;
};


#define WIDTH 800
#define HEIGHT 600
#define NUMBER_OF_ALIENS 7

int main(int, char *argv[])
{
    const float shipSpeed = 400.f;
    const int alienMaxSpeed = 1200;
    const int alienMinSpeed = 500;
    const float tirSpeed = 500.f;
    bool gameOver=false;
    bool winner = false;

    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
    window.setVerticalSyncEnabled(true);

    SoundManager music;
    music.playBackgroundMusic();
    
    //sakhte background
    sf::Sprite back;
    sf::Texture star;
    
    // Loade background
    if(!star.loadFromFile("/home/mohammad/Desktop/Spaceinvader/stars.png"))
        throw invalid_argument("Background not loaded!");
    back.setTexture(star);
    
    //sakhte screen bordo bakht
    WinScreen win;
    LoseScreen lose;
    
    
    Tir tir(0,tirSpeed);
    CollisionManager collision;
    //sakhte ship
    Ship myShip(0,shipSpeed);
    myShip.setLocation(WIDTH/2,HEIGHT-myShip.getSprite().getGlobalBounds().height);

    //sakhte 7 ta doshman
    Enemy alienArray[NUMBER_OF_ALIENS];
    for(int i=0; i<NUMBER_OF_ALIENS; i++)
    {
        
        Enemy alien(i, alienMinSpeed + (rand()%alienMaxSpeed) );
        alien.setLocation(i*100+50, alien.getSprite().getGlobalBounds().height/2);
        alienArray[i] = alien;
    }

    //Zamane asli
    sf::Clock clock;
    
    //zaman vase harekate aliena
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

   //zaman vase tir
    sf::Clock tirClock;
    tirClock.restart().asSeconds();
    
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (gameOver)
                {
                    // etmam bazi
                    gameOver = false;
                    winner=false;
                    clock.restart();
                    
                    //reset aliens
                    for(int i=0; i<NUMBER_OF_ALIENS; i++)
                    {
                        Enemy alien(i, alienMinSpeed + (rand()%alienMaxSpeed) );
                        alien.setLocation(i*100+50, alien.getSprite().getGlobalBounds().height/2);
                        alienArray[i] = alien;
                    }
                    
                    //reset ship location
                    myShip.setLocation(WIDTH/2,HEIGHT-myShip.getSprite().getGlobalBounds().height);
                    myShip.respawn();
                    
                    //restart music
                    music.playBackgroundMusic();
                }
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                if(!tir.isAlive() && !gameOver)
                {
                    tir.spawn(true);
                    tir.setLocation(myShip.getSprite().getPosition().x+31,myShip.getSprite().getPosition().y-15);
                    music.playLazer();
                }
            }
            //escape
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        window.clear(sf::Color(0,0,0,255));
        window.draw(back);
        
        
        //harekat ship
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
        {
            if (myShip.getSprite().getPosition().x + myShip.getSprite().getGlobalBounds().width < WIDTH)
            {
                
                myShip.getSprite().move(shipSpeed * deltaTime, 0.f);
            }
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
        {
            if(myShip.getSprite().getPosition().x > 0.f)
            {
                myShip.getSprite().move(-shipSpeed * deltaTime, 0.f);
            }
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
        {
            if(myShip.getSprite().getPosition().y > 0.f)
            {
                myShip.getSprite().move( 0.f,-shipSpeed * deltaTime);
            }
        }
        
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
        {
            if(myShip.getSprite().getPosition().y + myShip.getSprite().getGlobalBounds().height < HEIGHT)
            {
                myShip.getSprite().move(0.f, shipSpeed * deltaTime);
            }
        }
                 //zaman tey shde       
        sf::Time t = alienClock.getElapsedTime();
        if(t.asSeconds() > 0.5)
        {
            for(size_t i=0; i<7; i++)
            {
                alienArray[i].getSprite().move(0.f,alienArray[i].getSpeed()*deltaTime);
            }
            alienClock.restart();
        }

        sf::Time bc = tirClock.getElapsedTime();
        if(bc.asSeconds() > 1.0)
        {
            if(tir.isAlive() && !gameOver)
            {
                
                tir.draw(window);
                tir.getSprite().move(0.f,-20);
            }
        }

        //test barkhord beyn alien va ship
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(collision.collidesWith(myShip, alienArray[i]) && alienArray[i].isAlive())
            {
                if(!gameOver)
                    music.playExplosion();
                myShip.kill();
                winner=false;
                gameOver=true;
            }
        }
        
        //test barkhord beyn aliens va tahe safhe
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(alienArray[i].getSprite().getPosition().y+alienArray[i].getSprite().getGlobalBounds().height>HEIGHT && alienArray[i].isAlive())
            {
                if(!gameOver)
                    music.playExplosion();
                winner=false;
                gameOver=true;
            }
        }
        
        //test barkhord beyn tir o alien
        for(int i=0; i<NUMBER_OF_ALIENS;i++)
        {
            if(collision.collidesWith2(tir, alienArray[i]) && alienArray[i].isAlive())
            {
                music.playExplosion();
                alienArray[i].kill();
                tir.kill();
            }
        }
        
        int deadAliens=0;
        //bordan
        for(int i=0; i<NUMBER_OF_ALIENS; i++)
        {
            if(!alienArray[i].isAlive())
                deadAliens++;
            
            if(deadAliens==NUMBER_OF_ALIENS)
            {
                if(!gameOver)
                winner=true;
                gameOver=true;
            }
        }
                
        //test barkhord tir ba saghf
        if(tir.getSprite().getPosition().y < 0)
            tir.kill();
        
        
        //keshidan
        if(!gameOver)
        {
            for(size_t i=0;i<NUMBER_OF_ALIENS;i++)
            {
                if(alienArray[i].isAlive())
                {
                    alienArray[i].draw(window);
                }
            }

            if(myShip.isAlive())
            {
                myShip.draw(window);
            }
        
            // Update
            window.display();
        }
        else
        {
            music.pauseBackgroundMusic();
            
            if(winner)
                win.draw(window);
            else
                lose.draw(window);
                
            // Update
            window.display();
        }
        
    }
    
    return EXIT_SUCCESS;
}
