#include "LeapmotionPointer.hh"


void LeapmotionPointer::update()
{
	//updating the controller's position
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			Leap::Vector rm_hand_pos = _controller.frame().hands().rightmost().palmPosition();
			rm_hand_pos *= COORDINATE_SYSTEM_SCALE_CONVERSION;
			rm_hand_pos += this->_offset;

			_position = glm::vec3(rm_hand_pos.x, rm_hand_pos.y, rm_hand_pos.z);

			float pinchingValue(1.0f-0.5f*_controller.frame().hands().rightmost().pinchStrength());

			_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), _position)*glm::scale(mat4(1.0f), vec3(pinchingValue*LEAP_POINTER_SIZE)));

			_shadow.SetModelMatrix(glm::translate(mat4(1.0f), glm::vec3(_position.x, -1.199f, _position.z))*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));
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
	//_shadow.Draw(VP);
	glDisable(GL_BLEND);
}

void LeapmotionPointer::Init()
{
	std::cout << "LeapMotion connected !" << std::endl;
	_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_pointerModel.SetModelMatrix(glm::translate(mat4(1.0f), glm::vec3(0.5f, 0.0f, -1.0f))*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));
	
	this->_offset = Leap::Vector(0.0f, -2.0f, -2.0f);

	this->_shadow.Init("Shaders/shadow_vshader.glsl", "Shaders/shadow_fshader.glsl", "");
	this->_shadow.SetModelMatrix(glm::translate(mat4(1.0f), glm::vec3(_position.x, -1.199f, _position.z))*glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE)));

	_p_structure = NULL;
}


bool LeapmotionPointer::Pinching() const
{
	bool pinching = false;
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			if (_controller.frame().hands().rightmost().pinchStrength() > 0.80)
			{
				pinching = true;
			}
			else
			{
				pinching = false;
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
