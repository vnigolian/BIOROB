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

			_pointerModel.SetModelMatrix(glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE))
				*glm::translate(mat4(1.0f), _position ));
		}
	}
	bool useless = this->Pinching();
}

void LeapmotionPointer::Draw(const glm::mat4& VP) const
{
	glEnable(GL_BLEND);
	_pointerModel.Draw(VP);
	glDisable(GL_BLEND);
}

void LeapmotionPointer::Init()
{
	std::cout << "LeapMotion connected !" << std::endl;
	_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_pointerModel.SetModelMatrix(glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE))*glm::translate(mat4(1.0f), glm::vec3(0.5f, 0.5f, -1.0f)));
	this->_offset = Leap::Vector(0.5f, -4.0f, -5.0f);
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