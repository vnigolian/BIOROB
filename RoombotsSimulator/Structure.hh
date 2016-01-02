#pragma once

#include "Scene\RoomBot.hh"

/**
   This class represents a set of Roombot Modules organized to form a particular structure.
   It is created from .rbs files, files that contain a list of positions for the Roombot modules.
   They take the form :
   
   0 0 0
   0 1 0
   0 0 1
   0 1 1
   ...

   Where every pair of triplet is interpreted as a Roombot module.

   All coordinates are relative to the Structure and the position (0,0,0) corresponds to the
   left-most, lowest, closest Roombot module.

   IMPORTANT NOTE : There is no verification of the validity of the .rbs file.
                    A wrongly-written file would create an impossible Structure.
*/
class Structure
{
	const std::string _filename = ""; //The .rbs file name from which the Structure is loaded
	glm::vec3 _centerOffset;//The difference between the Structure's position and its center
	std::vector<RoomBot> roomBots; //The RoomBot modules of the Structure
	void SetCenterOffset();

public:
	/*The constructor takes the .rbs file name to import it and create the corresponding 
	Structure and a pointer to both hemisphere.*/
	Structure(std::string sourceFilename, OBJModel* p_h1, OBJModel* p_h2);

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