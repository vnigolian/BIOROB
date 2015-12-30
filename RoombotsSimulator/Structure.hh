#pragma once

#include "Scene\RoomBot.hh"

class Structure
{
	const std::string _filename = "";
	glm::vec3 _centerOffset;//The difference between the Structure's position and its center
	std::vector<RoomBot> roomBots; //The RoomBot modules of the Structure
	void SetCenterOffset();

public:
	Structure(std::string sourceFilename, OBJModel* p_h1, OBJModel* p_h2);

	//Structure(Structure* other);

	/*Draws the Structure*/
	void Draw(const glm::mat4& VP) const;

	/*Returns the Structure's center position which is an average of the roombots' positions*/
	glm::vec3 CenterOffset() const;

	//RE-WRITE THIS !!!
	/*Returns a vector of all the RoomBots' half-module's positions as pairs A-B*/
	std::vector<Position> RoombotsPositions() const;

	/*Cleans up the RoomBots*/
	void CleanUp();
};