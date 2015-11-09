#include "Structure.hh"


Structure::Structure(std::string sourceFilename)
//void Structure::Init(std::string sourceFilename)
{
	RoomBot leg1;
	leg1.Init(0, 0, 0,
		0, 1, 0);
	RoomBot leg2;
	leg2.Init(2, 0, 0,
		2, 1, 0);
	RoomBot leg3;
	leg3.Init(0, 0, 2,
		0, 1, 2);
	RoomBot leg4;
	leg4.Init(2, 0, 2,
		2, 1, 2);

	RoomBot base1;
	base1.Init(0, 2, 0,
		0, 2, 1);
	RoomBot base2;
	base2.Init(2, 2, 0,
		1, 2, 0);
	RoomBot base3;
	base3.Init(0, 2, 2,
		1, 2, 2);
	RoomBot base4;
	base4.Init(2, 2, 2,
		2, 2, 1);

	roomBots.push_back(leg1);
	roomBots.push_back(leg2);
	roomBots.push_back(leg3);
	roomBots.push_back(leg4);

	roomBots.push_back(base1);
	roomBots.push_back(base2);
	roomBots.push_back(base3);
	roomBots.push_back(base4);

	SetCenterOffset();
}

void Structure::SetCenterOffset()
{
	glm::vec3 centerOffset;
	size_t size = roomBots.size();
	for (size_t i = 0; i < size; i++)
	{
		glm::vec3 roomBotPosition = roomBots[i].Position();
		centerOffset += (1 / (float)size) * glm::vec3(roomBotPosition.x, roomBotPosition.y, -roomBotPosition.z);
	}
	_centerOffset = MODULE_SIZE * centerOffset - glm::vec3(MODULE_SIZE / 2, MODULE_SIZE / 2, -MODULE_SIZE / 2);
}

void Structure::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);

	for (size_t i = 0; i < roomBots.size(); i++)
	{
		//we multiply the VP matrix by a translation to draw the modules at the right place
		roomBots[i].Draw(VP);
	}
	glDisable(GL_BLEND);
}


glm::vec3 Structure::CenterOffset() const
{
	return _centerOffset;
}

void Structure::CleanUp()
{

}