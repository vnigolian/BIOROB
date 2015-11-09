#pragma once
#pragma once

#include "Scene\HalfModule.hh"
#include "Scene\RoomBot.hh"

class Structure
{
	glm::vec3 _centerOffset;//The difference between the Structure's position and its center
	std::vector<RoomBot> roomBots; //The RoomBot modules of the Structure
	void SetCenterOffset();

public:
	Structure(std::string sourceFilename);
	//void Init(std::string sourceFilename);
	/*Draws the Structure*/
	void Draw(const glm::mat4& VP) const;

	/*Returns the Structure's center position which is an average of the roombots' positions*/
	glm::vec3 Structure::CenterOffset() const;

	/*Cleans up the RoomBots*/
	void CleanUp();
};