#ifndef DE_MESH_H
#define DE_MESH_H

#include <glm/glm.hpp>
#include <string>

#include <gl/glew.h>

#include "export.h"
#include "core/CountedObject.h"

namespace de
{
	/**
	\namespace data

	\brief the namespace of all data that lives in memory.
	*/
	namespace data
	{
		/**
			\class Mesh

			\brief describe a Mesh in memory
		 */
		class DE_EXPORT Mesh : public CountedObject<Mesh>
		{
		protected:

			//used by binary importer to know which data are contained in the file
			enum VertexData
							{
								DATA_VERTEX	= 0x1,
								DATA_NORMAL	= 0X2,
								DATA_UV		= 0x4,
								DATA_TANGENT = 0X8
							};

			enum IDS{VERTICE, UV, NORMAL, TANGENT, TRIANGLE}; // for indexing in array like mOpenGLIDS

			unsigned int mNbVertex;
			unsigned int mNbTriangles;

			glm::vec3*		mVertex;
			glm::vec2*		mUvs;
			glm::vec3*		mNormals;
			glm::vec3*		mTangents;

			unsigned int*	mTriangles;

			GLuint		mOpenGLID[5]; // 5 for the moment (pos, uv, normal, tangent, triangles), this could change in the futur

		public:
			Mesh();
			Mesh(std::string pPath);

			void release();

			void loadFromFile(const std::string& pPath);
			
			void setVertex(glm::vec3*	pVertex, unsigned int pNb);
			void setUV(glm::vec2*		pUv);
			void setNormal(glm::vec3* pNormal);

			/**
			* \brief CAREFUL : pNb is actually three ime smalle than pTriangles size. there is 3 index by face, and pNB is the number OF FACES
			*/
			void setTriangles(int*	pTriangles, unsigned int pNb);

			void uploadToVRAM();
			void draw();
		};
	}
}

#endif