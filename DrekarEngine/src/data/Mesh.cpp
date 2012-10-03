#include "data/Mesh.h"
#include <fstream>

using namespace de::data;

Mesh::Mesh()
{
	mVertex = nullptr;
	mNormals = nullptr;
	mTangents = nullptr;
	mUvs = nullptr;
	mTriangles = nullptr;

	glGenBuffers(5, mOpenGLID);
}

//-------------------------------


//--------------------------------

Mesh::~Mesh()
{
	glDeleteBuffers(5, mOpenGLID);
}

//--------------------------------

void Mesh::setVertex(glm::vec3* pVertex, unsigned int pNb)
{
	if(mVertex != nullptr)
		delete[] mVertex;

	mNbVertex = pNb;

	mVertex = new glm::vec3[pNb];

	for(unsigned int i = 0; i < pNb; i++)
	{
		mVertex[i] = pVertex[i];
	}
}

//----------------------------------

void Mesh::setUV(glm::vec2* pUV)
{
	if(mUvs != nullptr)
		delete[] mUvs;

	mUvs = new glm::vec2[mNbVertex];

	for(int i = 0; i < mNbVertex; i++)
	{
		mUvs[i] = pUV[i];
	}
}

//----------------------------------

void Mesh::setNormal(glm::vec3* pNormal)
{
	if(mNormals != nullptr)
		delete[] mNormals;

	mNormals = new glm::vec3[mNbVertex];

	for(int i = 0; i < mNbVertex; i++)
	{
		mNormals[i] = pNormal[i];
	}
}

//----------------------------------

void Mesh::setTriangles(int* pTriangle, unsigned int pNumber)
{
	if(mTriangles != nullptr)
		delete[] mTriangles;

	mNbTriangles = pNumber;
	
	mTriangles = new unsigned int[mNbTriangles*3];
	for(int i = 0; i < mNbTriangles*3; i+=3)
	{
		mTriangles[i+0] = pTriangle[i+0];
		mTriangles[i+1] = pTriangle[i+1];
		mTriangles[i+2] = pTriangle[i+2];
	}
}

//-----------------------------------

void Mesh::uploadToVRAM()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mOpenGLID[TRIANGLE]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mNbTriangles*3*sizeof(unsigned int), mTriangles, GL_STATIC_DRAW); 

	glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[VERTICE]); 
	glBufferData(GL_ARRAY_BUFFER, mNbVertex*3*sizeof(float), mVertex, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 

	if(mNormals != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[NORMAL]); 
		glBufferData(GL_ARRAY_BUFFER, mNbVertex*3*sizeof(float), mNormals, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1); 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if(mUvs != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[UV]); 
		glBufferData(GL_ARRAY_BUFFER, mNbVertex*2*sizeof(float), mUvs, GL_STATIC_DRAW);
		glEnableVertexAttribArray(2); 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
}

//---------------------------------


void Mesh::draw()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mOpenGLID[TRIANGLE]);

	glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[VERTICE]); 
	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if(mNormals != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[NORMAL]); 
		glEnableVertexAttribArray(1); 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if(mUvs != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mOpenGLID[UV]); 
		glEnableVertexAttribArray(2); 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	glDrawElements(
     GL_TRIANGLES,      // mode
	 mNbTriangles*3,    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 ); 
}

//----------------------------------

void Mesh::fromFile(const std::string& pFile)
{
	std::fstream lFile;

	lFile.open(pFile, std::ios::in|std::ios::binary);

	if(lFile.is_open())
	{
		//retrieve which data the mesh contain
		unsigned int data;
		lFile.read((char*)&data, sizeof(unsigned int));

		//----------------------------- vertex loading

		lFile.read((char*)&mNbVertex, sizeof(unsigned int));

		mVertex = new glm::vec3[mNbVertex];

		if(data&DATA_NORMAL)
			mNormals = new glm::vec3[mNbVertex];

		if(data&DATA_UV)
			mUvs = new glm::vec2[mNbVertex];

		for(int i = 0; i < mNbVertex; i++)
		{
			lFile.read((char*)&mVertex[i].x,sizeof(float));
			lFile.read((char*)&mVertex[i].y,sizeof(float));
			lFile.read((char*)&mVertex[i].z,sizeof(float));

			if(data&DATA_UV)
			{
				float temp;
				lFile.read((char*)&mUvs[i].x,sizeof(float));
				lFile.read((char*)&mUvs[i].y,sizeof(float));
				lFile.read((char*)&temp,sizeof(float));

				int k = 0;
			}

			if(data&DATA_NORMAL)
			{
				lFile.read((char*)&mNormals[i].x,sizeof(float));
				lFile.read((char*)&mNormals[i].y,sizeof(float));
				lFile.read((char*)&mNormals[i].z,sizeof(float));
			}
		}


		//---------------------------- face loading

		lFile.read((char*)&mNbTriangles, sizeof(unsigned int));
		mTriangles = new unsigned int[mNbTriangles*3];
		for(int i = 0; i < mNbTriangles*3; i+=3)
		{
			lFile.read((char*)&mTriangles[i], sizeof(unsigned int));
			lFile.read((char*)&mTriangles[i+1], sizeof(unsigned int));
			lFile.read((char*)&mTriangles[i+2], sizeof(unsigned int));
		}

		lFile.close();

		uploadToVRAM();
	}
}