#include <glm/glm.hpp>

typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ;

class Car
{	
public:


	float wheelAngle;
	float position;
	float acceleration;
	float angle;
	float turnAngle;
	float wheelRotnSpeed;
	vec3 carCentre;
	vec3 wheelAxis;
	Car(float cAngle, float ta, float pos, float acc, float wAngle, vec3 axis, float wrs)
	{
		angle = cAngle;
		turnAngle = ta;
		position = pos;
		acceleration = acc;
		wheelAngle = wAngle;
		wheelAxis = axis;
		wheelRotnSpeed = wrs;

	}
};