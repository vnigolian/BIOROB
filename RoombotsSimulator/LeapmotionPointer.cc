#include "LeapmotionPointer.hh"


void LeapmotionPointer::update()
{
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
}

void LeapmotionPointer::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_pointerModel.Draw(VP);
	_shadow.Draw(VP);
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
}


bool LeapmotionPointer::Pinching() const
{
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			if (_controller.frame().hands().rightmost().pinchStrength() > 0.9)
			{
				return true;
			}
			else if (_controller.frame().hands().rightmost().pinchStrength() > 0.5)
			{
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}


glm::vec3 LeapmotionPointer::Position() const
{
	return _position;
}