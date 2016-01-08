#pragma once

#include "RoomBot.hh"
#include "Cube.hh"

/**
   This class represents a set of Roombot Modules organized to form a particular structure.
   It is created from .rbs files, files that contain a list of positions for the Roombot modules.
   They take the form :
   
   0 0 0 \n
   0 1 0 \n
   0 0 1 \n
   0 1 1 \n
   ...

   Where every pair of triplet is interpreted as a Roombot module.

   All coordinates are relative to the Structure and the position (0,0,0) corresponds to the
   left-most, lowest, closest Roombot module.

   IMPORTANT NOTE : There is no verification of the validity of the .rbs file.
                    A wrongly-written file would create a physicaly impossible Structure.
*/
class Structure
{
	const std::string    d_filename = ""; ///<The .rbs file name from which the Structure is loaded
	glm::vec3            d_centerOffset;  ///<The difference between the Structure's position and its center
	std::vector<RoomBot> d_roomBots;      ///<The RoomBot modules of the Structure
	Cube* centerCube;

public:
	/**Imports a new OBJModel from a .obj file
	\arg \c sourceFilename The name of the .bj file containing the model to import
	\arg \c \c p_h1,\c p_h2,\c p_circle Pointers to the OBJModels needed by the RoomBot of the Structure*/
	Structure(std::string sourceFilename, 
		      OBJModel* p_h1, 
			  OBJModel* p_h2, 
			  OBJModel* p_circle);

	/**Draws the Structure*/
	void Draw(const glm::mat4& VP) const;

	/**Returns the Structure's center position which is an average of the roombots' positions*/
	glm::vec3 CenterOffset() const;

	/**Returns a vector of all the RoomBots' half-module's positions as AB AB AB...*/
	std::vector<Position> RoombotsPositions() const;

private:
	/**Computes the offset between the lower, closer left corner and the center of the Structure.
	The center is calculated as the average of all of the Roombots' positions*/
	//void SetCenterOffset();
};