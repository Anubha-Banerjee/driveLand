#define FREEGLUT_STATIC

#include <GLTools.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::mat3 mat3 ;
typedef glm::mat4 mat4 ; 
typedef glm::vec3 vec3 ; 
typedef glm::vec4 vec4 ; 


extern GLint shader;

struct camera
{
	vec3 eye;
	vec3 up;
	vec3 goal;
};

enum shape {land, car, frontWheels} ;

// For multiple objects, read from a file.  
const int maxobjects = 10 ; 
extern int numobjects ; 


struct object {
	GLBatch batch;
	shape type ; 
	float size ;
	GLfloat ambient[4]; 
	GLfloat diffuse[4]; 
	GLfloat specular[4]; 
	GLfloat shininess;
    mat4 transform ; 
	mat4 translate;
	mat4 rotate;
	vec4 position;
	mat4 dist_from_origin;
	GLuint texture;
} ;

extern object objects[maxobjects];
extern object carParts[maxobjects];

struct component
{
	float x;
	float y;
	float z;
};

int loadMesh(FILE *fp);

extern component *v,*vn,*vt;
extern M3DVector3f *Ver;
extern M3DVector3f *Normals;
extern M3DVector2f *vTexCoords; 	

extern void initialiseObjects();


extern GLuint lightposn; 
extern GLuint lightcolor;

struct uniform
{
	GLuint ambientcol ; 
	GLuint diffusecol ; 
	GLuint specularcol ; 
	GLuint shininesscol ; 
	GLint shader;
};

extern uniform colorUniform;
extern camera myCamera;


class Transform  
{
public:
	Transform();
	virtual ~Transform();
	static void left(float degrees,vec3& eye, vec3& center, vec3& up, vec3& carCentre);
	static void up(float degrees, vec3& eye, vec3& up);
	static mat4 lookAt(vec3  eye,  vec3 up);
	static mat4 perspective(float fovy, float aspect, float zNear, float zFar);
    static mat3 rotate(const float degrees, const vec3& axis) ;
    static mat4 scale(const float &sx, const float &sy, const float &sz) ; 
    static mat4 translate(const float &tx, const float &ty, const float &tz);
    static vec3 upvector(const vec3 &up, const vec3 &zvec) ; 
};

extern bool arrowKeys[4];