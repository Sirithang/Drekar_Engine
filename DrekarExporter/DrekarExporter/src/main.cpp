#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <fstream>


Assimp::Importer	gImp;
std::string			gOutputName = "";

enum VertexData
{
	VERTEX	= 0x1,
	NORMAL	= 0X2,
	UV		= 0x4,
	TANGENT = 0X8
};


void loadModel(std::string pPath)
{
	const aiScene* scene = gImp.ReadFile( pPath,	aiProcess_CalcTangentSpace|         
													aiProcess_Triangulate|        
													aiProcess_JoinIdenticalVertices| 
													aiProcess_SortByPType | aiProcess_FlipWindingOrder);

	if(!scene)
	{
		std::cout<<"Error loading the scene : \n"<<gImp.GetErrorString()<<std::endl;
		exit(-1);
	}

	for(int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* lMesh = scene->mMeshes[i];

		aiMatrix4x4 lMat;
		//aiMatrix4x4::RotationX(-90.0f * 3.14f / 180.0f, lMat);

		int numberOfVertex = lMesh->mNumVertices;
		unsigned int data = VERTEX;

		if(lMesh->HasTextureCoords(0))
			data |= UV;
		if(lMesh->HasNormals())
			data |= NORMAL;
		if(lMesh->HasTangentsAndBitangents())
			data |= TANGENT;

		aiQuaternion lRotation(aiVector3D(1,0,0), 90.0f); // Y UP

		char num[10];
		itoa(i, num, 10);

		std::string outputPath;

		if(gOutputName == "")
			outputPath = pPath + "_" + std::string(num) + ".mesh";
		else
			outputPath = gOutputName + "_" + std::string(num) + ".mesh";

		std::fstream lStream(outputPath, std::ios::binary|std::ios::out);

	
		lStream.write((char*)&data, sizeof(unsigned int));
		lStream.write((char*)&lMesh->mNumVertices, sizeof(unsigned int));

		for(int i = 0; i < numberOfVertex; i++)
		{
			aiVector3D lPts = lMat* lMesh->mVertices[i];

			lStream.write((char*)&lPts.x, sizeof(float));
			lStream.write((char*)&lPts.y, sizeof(float));
			lStream.write((char*)&lPts.z, sizeof(float));
		
			if(data&UV)
			{
				lPts = lMesh->mTextureCoords[0][i];
				lStream.write((char*)&lPts.x, sizeof(float));
				lStream.write((char*)&lPts.y, sizeof(float));
				lStream.write((char*)&lPts.z, sizeof(float));
			}

			if(data&NORMAL)
			{
				lPts = lMat* lMesh->mNormals[i];

				lStream.write((char*)&lPts.x, sizeof(float));
				lStream.write((char*)&lPts.y, sizeof(float));
				lStream.write((char*)&lPts.z, sizeof(float));
			}
		}

		lStream.write((char*)&lMesh->mNumFaces, sizeof(unsigned int));
	
		for(int i = 0; i < lMesh->mNumFaces; i++)
		{
			if(lMesh->mFaces[i].mNumIndices != 3)
				continue;

			lStream.write((char*)&lMesh->mFaces[i].mIndices[0], sizeof(unsigned int));
			lStream.write((char*)&lMesh->mFaces[i].mIndices[1], sizeof(unsigned int));
			lStream.write((char*)&lMesh->mFaces[i].mIndices[2], sizeof(unsigned int));
		}

		lStream.close();
	}
}


//------------------------------------------------------

int main(int argc, char** argv)
{
	std::string file = "";

	for(int i = 0; i < argc; i++)
	{
		std::string arg(argv[i]);

		if(arg == "-f")
		{
			if(i + 1 >= argc)
			{
				std::cout<<"Error not enought argument after -f"<<std::endl;
				system("pause");
				exit(-1);
			}
			else
			{
				file  = argv[i+1];
			}
		}
		else if(arg == "-o")
		{
			if(i + 1 >= argc )
			{
				std::cout<<"Error, need a name argument after -o"<<std::endl;
				system("pause");
				exit(-1);
			}
			else
			{
				gOutputName = argv[i+1];
			}
		}
	}

	if(file != "")
		loadModel(file);

	system("pause");
}