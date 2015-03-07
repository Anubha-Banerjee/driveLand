#include "variables.h" 

// vertex arrays read from obj file (containing only distinct vertices)
component *v,*vn,*vt;

// the final vertics given to openGL
M3DVector3f *Ver;
M3DVector3f *Normals;
M3DVector2f *vTexCoords; 

object objects[maxobjects];
object carParts[maxobjects];


bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte *pBits;
	int nWidth, nHeight, nComponents;
	GLenum eFormat;
	
	// Read the texture bits
	pBits = gltReadTGABits(szFileName, &nWidth, &nHeight, &nComponents, &eFormat);
	if(pBits == NULL) 
		return false;
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, nComponents, nWidth, nHeight, 0,
				 eFormat, GL_UNSIGNED_BYTE, pBits);
	
    free(pBits);
    
    if(minFilter == GL_LINEAR_MIPMAP_LINEAR || 
       minFilter == GL_LINEAR_MIPMAP_NEAREST ||
       minFilter == GL_NEAREST_MIPMAP_LINEAR ||
       minFilter == GL_NEAREST_MIPMAP_NEAREST)
       glGenerateMipmap(GL_TEXTURE_2D);    
	return true;
}


void freePointers()
{
	free(v);
	free(vn);
	free(vt);
	free(Ver);
	free(Normals);
	free(vTexCoords);
}

void fillBuffer(char fname[40],GLBatch *batch)
{
	FILE *fp;
	fp=fopen(fname,"r+");
	int total_ver=loadMesh(fp);	
	fclose(fp);

	batch->Begin(GL_TRIANGLES,total_ver,1);
	batch->CopyVertexData3f(Ver);
	batch->CopyTexCoordData2f(vTexCoords,0);
	batch->CopyNormalDataf(Normals);	
	batch->End();
	freePointers();
}

void initialiseObjects()
{
	//for(int i = 0; i < 1; i++)
	//{
		fillBuffer("land2.obj",&objects[0].batch);
		objects[0].type = land;
		objects[0].ambient[0] = 1;
		objects[0].ambient[1] = 1;
		objects[0].ambient[2] = 1;

		objects[0].diffuse[0] = 0.5;
		objects[0].diffuse[1] = 0.5;
		objects[0].diffuse[2] = 0.5;

		objects[0].specular[0] = 0;
		objects[0].specular[1] = 0;
		objects[0].specular[2] = 0;

		objects[0].shininess = 200;	
		
	
		glGenTextures(1,&objects[0].texture);	
		glBindTexture(GL_TEXTURE_2D,objects[0].texture);	
		LoadTGATexture("r2.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
		
		
		fillBuffer("carExt.obj",&carParts[0].batch);
		carParts[0].type = car;
		carParts[0].ambient[0] = 1;
		carParts[0].ambient[1] = 1;
		carParts[0].ambient[2] = 1;

		carParts[0].diffuse[0] = 0.5;
		carParts[0].diffuse[1] = 0.5;
		carParts[0].diffuse[2] = 0.5;

		carParts[0].specular[0] = 1;
		carParts[0].specular[1] = 1;
		carParts[0].specular[2] = 1;

		carParts[0].shininess = 120;
		carParts[0].position = vec4(0, 0, 0, 1);

		glGenTextures(1, &carParts[0].texture);	
		glBindTexture(GL_TEXTURE_2D,carParts[0].texture);	
		LoadTGATexture("rose.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

				
		fillBuffer("wheel.obj",&carParts[1].batch);
		carParts[1].type = frontWheels;
		carParts[1].ambient[0] = 0.5;
		carParts[1].ambient[1] = 0.5;
		carParts[1].ambient[2] = 0.5;

		carParts[1].diffuse[0] = 0.5;
		carParts[1].diffuse[1] = 0.5;
		carParts[1].diffuse[2] = 0.5;

		carParts[1].specular[0] = 1;
		carParts[1].specular[1] = 1;
		carParts[1].specular[2] = 1;

		carParts[1].shininess = 200;

		carParts[1].translate = Transform::translate(4, 2 , -6.3);


		glGenTextures(1, &carParts[1].texture);	
		glBindTexture(GL_TEXTURE_2D, carParts[1].texture);	
		LoadTGATexture("t1.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

	

		fillBuffer("wheel.obj",&carParts[2].batch);

		carParts[2].ambient[0] = 0.5;
		carParts[2].ambient[1] = 0.5;
		carParts[2].ambient[2] = 0.5;

		carParts[2].diffuse[0] = 0.5;
		carParts[2].diffuse[1] = 0.5;
		carParts[2].diffuse[2] = 0.5;

		carParts[2].specular[0] = 1;
		carParts[2].specular[1] = 1;
		carParts[2].specular[2] = 1;

		carParts[2].shininess = 200;
		
		carParts[2].translate = Transform::translate(-4, 2 , -6.3);
		glBindTexture(GL_TEXTURE_2D, carParts[2].texture);	
		LoadTGATexture("t1.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);


		fillBuffer("wheel.obj",&carParts[3].batch);
		carParts[1].type = frontWheels;
		carParts[3].ambient[0] = 0.5;
		carParts[3].ambient[1] = 0.5;
		carParts[3].ambient[2] = 0.5;

		carParts[3].diffuse[0] = 0.5;
		carParts[3].diffuse[1] = 0.5;
		carParts[3].diffuse[2] = 0.5;

		carParts[3].specular[0] = 1;
		carParts[3].specular[1] = 1;
		carParts[3].specular[2] = 1;

		carParts[3].shininess = 200;
		carParts[3].translate = Transform::translate(4, 2 , 7);
		glGenTextures(1, &carParts[3].texture);	
		glBindTexture(GL_TEXTURE_2D, carParts[3].texture);	
		LoadTGATexture("t1.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

		fillBuffer("wheel.obj",&carParts[4].batch);
		carParts[1].type = frontWheels;
		carParts[4].ambient[0] = 0.5;
		carParts[4].ambient[1] = 0.5;
		carParts[4].ambient[2] = 0.5;


		carParts[4].diffuse[0] = 0.5;
		carParts[4].diffuse[1] = 0.5;
		carParts[4].diffuse[2] = 0.5;

		carParts[4].specular[0] = 1;
		carParts[4].specular[1] = 1;
		carParts[4].specular[2] = 1;

		carParts[4].shininess = 200;
		carParts[4].translate = Transform::translate(-4, 2 , 7);	
		glGenTextures(1, &carParts[4].texture);	
		glBindTexture(GL_TEXTURE_2D, carParts[4].texture);	
		LoadTGATexture("t1.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);

		fillBuffer("carInt.obj",&carParts[5].batch);
		carParts[5].type = car;
		carParts[5].ambient[0] = 0.3;
		carParts[5].ambient[1] = 0.1;
		carParts[5].ambient[2] = 0.2;

		carParts[5].diffuse[0] = 0.5;
		carParts[5].diffuse[1] = 0.5;
		carParts[5].diffuse[2] = 0.5;

		carParts[5].specular[0] = 1;
		carParts[5].specular[1] = 1;
		carParts[5].specular[2] = 1;

		carParts[5].shininess = 120;
		carParts[5].position = vec4(0, 0, 0, 1);

		glGenTextures(1, &carParts[5].texture);	
		glBindTexture(GL_TEXTURE_2D,carParts[5].texture);	
		LoadTGATexture("sofa.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
		
}
  
