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
			_pointerModel.SetModelMatrix(glm::scale(mat4(1.0f), vec3(LEAP_POINTER_SIZE))
				*glm::translate(mat4(1.0f), vec3(rm_hand_pos.x, rm_hand_pos.y, rm_hand_pos.z)));
		}
	}
	bool useless = this->Pinching();
}

void LeapmotionPointer::Draw(const glm::mat4& VP)
{
	_pointerModel.Draw(VP);
}

void LeapmotionPointer::Init()
{
	std::cout << "LeapMotion connected !" << std::endl;
	_pointerModel.Init("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "");
	_pointerModel.SetModelMatrix(glm::scale(mat4(1.0f), vec3(0.05f))*glm::translate(mat4(1.0f), glm::vec3(0.5f, 0.5f, -1.0f)));
	this->_offset = Leap::Vector(0.5f, -4.0f, -5.0f);
}

bool LeapmotionPointer::Pinching()
{
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			if (_controller.frame().hands().rightmost().pinchStrength() > 0.9)
			{
				std::cout << "					PINCHING !!!" << std::endl;
				return true;
			}
			else if (_controller.frame().hands().rightmost().pinchStrength() > 0.5)
			{
				std::cout << "cloooooooooose" << std::endl;
				return false;
			}
			else
			{
				return false;
			}
		}
	}
}