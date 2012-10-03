#include "data/HeightmapInfo.h"
#include "core/Debug.h"

#include <gli/gli.hpp>
#include <gli/gtx/loader.hpp>

#include <cstdint>

#include "jsmn/jsmn.h"


using namespace de;
using namespace de::data;


HeightmapInfo::HeightmapInfo()
{
	height = 0;
	width = 0;
	depth = 0;

	hmWidth = 0;
	hmHeight = 0;

	heightInfo = nullptr;
}

//----------------------------------------------

HeightmapInfo::~HeightmapInfo()
{

}

//-----------------------------------------------
void HeightmapInfo::fromJSON(const std::string& pData)
{
	jsmn_parser parser;
	jsmn_init(&parser);

	jsmntok_t tokens[256];
	jsmnerr_t r = jsmn_parse(&parser, pData.c_str(), tokens, 256);

	if(r != JSMN_SUCCESS )
	{
		Debug::Log(std::string("Erreur parson JSON for HeightmapRender : ")+pData+" \n");
		return;
	}


	//------------------

	std::string heightmapFile = "";

	int i = 1; 
	while(tokens[i].start != -1)
	{

		if(tokens[i].type == JSMN_STRING)
		{
			std::string name = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

			if(name == "width" && tokens[i+1].type == JSMN_PRIMITIVE)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				width = atof(data.c_str());
			}
			else if(name == "height" && tokens[i+1].type == JSMN_PRIMITIVE)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				height = atof(data.c_str());
			}
			else if(name == "depth" && tokens[i+1].type == JSMN_PRIMITIVE)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				depth = atof(data.c_str());
			}
			else if(name == "heightmapWidth" && tokens[i+1].type == JSMN_PRIMITIVE)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				hmWidth = atoi(data.c_str());
			}
			else if(name == "heightmapHeight" && tokens[i+1].type == JSMN_PRIMITIVE)
			{
				i++;
				std::string data = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);

				hmHeight = atoi(data.c_str());
			}
			else if(name == "heightmap" && tokens[i+1].type == JSMN_STRING)
			{
				i++;
				heightmapFile = std::string(pData, tokens[i].start, tokens[i].end - tokens[i].start);
			}
			else
			{
				Debug::Log("Unreconignezed token : " + name + " in heightmap info");
			}
		}

		i++;
	}

	if(heightmapFile != "")
	{
		std::fstream inHeight;

		inHeight.open(heightmapFile, std::ios::in|std::ios::binary);

		if(inHeight.is_open())
		{
			if(hmWidth <= 0 || hmHeight <= 0)
			{
				Debug::Log("heightmapWidth or heightmapHeight = 0 or less. Please specify stricly positive size");
			}

			heightInfo = new float[hmWidth * hmHeight];

			for(int i = 0; i < hmWidth * hmHeight; i++)
			{
				uint16_t readHeight = 0;

				inHeight.read((char*)&readHeight, sizeof(uint16_t));

				heightInfo[i] = ((float)readHeight / (float)0xFFFF);
			}

			int debug = 0;

			inHeight.close();
		}
		else
		{
			Debug::Log("Error opening heightmap : " + heightmapFile);
		}
	}
}