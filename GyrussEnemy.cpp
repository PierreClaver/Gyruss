#include "GyrussEnemy.h"

GyrussEnemy::GyrussEnemy() 
{
		if(EnemyTexture.loadFromFile("textures/enemy.png") ){
			cout << "enemy sprite loaded" << endl;
		}
		EnemySprite.setTexture(EnemyTexture) ; 
		int ts = 1 ;
		_x= ((width-1)/2)*ts; 
		_y= ((length -1)/2)*ts ;
		
		_xRefPoint = _x ;
		_yRefPoint = _y ; 
		_dx = 4 - rand()%8 ; 
		_dy = 4 - rand()%8 ; 
	
	
	
}

void GyrussEnemy::move()
{
	srand(time(0)) ; 
	_dx =+ ((2 - rand()%2) +  _dx) ; _x +=  _dx ;
	_dy =+ ((2 - rand()%2)+ _dy ) ; _y +=      _dy ;
	 int changeinX = (_xRefPoint - _x)  ,changeinY = (_yRefPoint -  _y) ;
	
		
	 float r =  sqrt( pow(changeinX , 2)  + pow(changeinY , 2)   )   ; 
		
		if((  r >= 100)) { _dx =- _dx ; _x +=  _dx  ; } ;
	
		if((  r >= 100)) { _dy =- _dy ; _y += _dy  ; } ;
		EnemySprite.rotate(10) ;
}


float tempTime = 0;
GyrussEnemy::updateScreen( sf::RenderWindow &window)
{	
	float timeE = clockE.getElapsedTime().asSeconds ();
	move() ; 
	EnemySprite.setPosition(_x, _y ) ;
	tempTime += timeE;
	if(tempTime > 0.1){
		
		_enemyWeapon.enemyShoot(*this, "enemyBullet");
		tempTime = 0;
	}
	timeE = clockE.restart().asSeconds();
	_enemyWeapon.weaponUpdate(window,sf::Vector2<float> (250,250), 1.0f);
	_enemyCollider.update(EnemySprite.getGlobalBounds());
	auto i = 0;
	auto colliders = _enemyWeapon.getBulletCollider();
	if(_enemyCollider.collided(colliders,i)){
		cout << "Collided with " << colliders.at(i - 1).getTag() << endl;
	}
	//std::cout <<"x: " << _x << "y: " << _y << std::endl ; ,
	window.draw(EnemySprite) ;
}

GyrussEnemy::~GyrussEnemy()
{
}


void GyrussEnemy::enemySetup(sf::Texture texture,sf::Vector2f initialPosition, sf::Vector2f scale){
	EnemyTexture = texture;
	EnemySprite.setPosition(initialPosition);
	EnemySprite.setScale(scale);
}

GyrussEnemy::GyrussEnemy( sf::Vector2f initPos, EnemyType enemyType = EnemyType::ships){
	sf::Texture temp ;
	switch(enemyType){
		case EnemyType::ships:
			temp.loadFromFile("textures/enemy.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::satellites:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::laser:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::generator:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		case EnemyType::asteroids:
			temp.loadFromFile("textures/game_sprite.png");
			enemySetup(temp, initPos, sf::Vector2<float> (2,2));
			break;
		default:
			break;
	} 
}
