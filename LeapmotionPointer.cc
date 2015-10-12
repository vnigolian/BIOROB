#include "LeapmotionPointer.hh"

/*LeapmotionPointer::LeapmotionPointer(bool left_or_right) //:_controller((new Leap::Controller))
{
	//std::cout << "LeapMotion connected !" << std::endl;
	//Leap::Controller newController;
	//_controller = newController;

	if (_controller.isConnected() )
	{
		std::cout << " LeapMotion connected !" << std::endl;
	}

	this->_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	
	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	this->_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), this->_position)*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));

	this->_offset = Leap::Vector(0.0f, -2.0f, -2.0f);

	this->_p_structure = NULL;

	this->_right = left_or_right;

	std::cout << "added pointer" << std::endl;
}*/

void LeapmotionPointer::update()
{
	//updating the controller's position
	if (_controller.isConnected())
	{
		std::cout << "controller connected, are there hands ? " << std::endl;
		std::cout << _controller.frame().hands().isEmpty() << std::endl;
		if (!_controller.frame().hands().isEmpty())
		{
			Leap::Vector hand_pos;
			float pinchingValue;

			if (_right)
			{
				std::cout << "updating " << _right << " pointer" << std::endl;
				hand_pos = _controller.frame().hands().rightmost().palmPosition();
				pinchingValue = (1.0f - 0.5f*_controller.frame().hands().rightmost().pinchStrength());
				std::cout << hand_pos << std::endl;
			}
			else
			{
				hand_pos = _controller.frame().hands().leftmost().palmPosition();
				pinchingValue = (1.0f - 0.5f*_controller.frame().hands().leftmost().pinchStrength());
			}

			hand_pos *= COORDINATE_SYSTEM_SCALE_CONVERSION;
			hand_pos += this->_offset;

			_position = glm::vec3(hand_pos.x, hand_pos.y, hand_pos.z);

			_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), _position)*glm::scale(mat4(1.0f), vec3(pinchingValue*LEAP_POINTER_SIZE)));
		}
	}

	//handling the assignedStructure
	if (_p_structure != NULL)
	{
		if (Pinching())
		{
			_p_structure->Drag(_position);
		}
		else
		{
			std::cout << "pinching strength :" << _controller.frame().hands().rightmost().pinchStrength() << std::endl;
			_p_structure->Drop();
			_p_structure = NULL;
		}
	}
}

void LeapmotionPointer::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_pointerModel.Draw(VP);
	glDisable(GL_BLEND);
}

void LeapmotionPointer::Init(bool left_or_right)
{
	if (_controller.isConnected())
	{
		std::cout << " LeapMotion connected !" << std::endl;
	}

	this->_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");

	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);

	this->_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), this->_position)*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));

	this->_offset = Leap::Vector(0.0f, -2.0f, -2.0f);

	this->_p_structure = NULL;

	this->_right = left_or_right;

	std::cout << "added pointer" << std::endl;

	/*std::cout << "LeapMotion connected !" << std::endl;
	_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");

	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), _position)*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));
	
	this->_offset = Leap::Vector(0.0f, -2.0f, -2.0f);
	_p_structure = NULL;*/
}


bool LeapmotionPointer::Pinching() const
{
	bool pinching = false;
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			if (_right)
			{
				if (_controller.frame().hands().rightmost().pinchStrength() > 0.80)
				{
					pinching = true;
				}
			}
			else
			{
				if (_controller.frame().hands().leftmost().pinchStrength() > 0.80)
				{
					pinching = true;
				}
			}
		}
	}
	return pinching;
}


glm::vec3 LeapmotionPointer::Position() const
{
	return _position;
}

void LeapmotionPointer::AssignStructure(Structure* p_structure)
{
	_p_structure = p_structure;
}

Structure* LeapmotionPointer::AssignedStructure() const
{
	return _p_structure;
}
