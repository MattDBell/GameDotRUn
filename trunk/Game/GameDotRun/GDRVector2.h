#include <Box2D/Common/b2Math.h>
#include <SFML\System\Vector2.hpp>

#ifndef GDR_VECTOR2
#define GDR_VECTOR2
//Needs to be expanded to handle operators from both types... Yay
class GDR_Vector2
{
	b2Vec2 b2v;
	sf::Vector2<float> sfmlv;
	float x;
	float y;
public:
	float GetX() {return x;}
	float GetY() {return y;}
	void SetX(float to) { x = to; b2v.x = to; sfmlv.x = to;}
	void SetY(float to) {y = to; b2v.y = to; sfmlv.y = to;}
	const b2Vec2& AsBox() {return b2v;}
	const sf::Vector2<float>& AsSFML() {return sfmlv;}

};
#endif//GDR_VECTOR2