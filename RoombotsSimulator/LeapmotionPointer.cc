#include "LeapmotionPointer.hh"
#include "GUI.hh"

void LeapmotionPointer::Init(GUI* p_gui)
{
	if (!_init)
	{
		std::cout << "LeapMotion connected !" << std::endl;
		_pointerModel = new Cube("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "",glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		_pointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, -1.0f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));

		_referencePointerModel = new Cube("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		_referencePointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, -1.0f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));


		_shadow = new Quad("Shaders/pointer_vshader.glsl", "Shaders/pointer_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));


		_p_structure = NULL;

		_init = true;
		_p_gui = p_gui;
	}
}


Leap::Vector LeapmotionPointer::adaptToMode(Leap::Vector right_hand_pos, bool mode)
{
	//all values used in this method come from a longs fine-tuning sessions to figure out 
	//what were the best parameters for a good use of the program
	Leap::Vector adapted = right_hand_pos;
	if (mode)
	{
		adapted *= BOX_COORDINATE_SYSTEM_SCALE_CONVERSION;
		adapted += Leap::Vector(0.0f, -EYES_POSITION - 2.5f, -3.0f);
	}
	else
	{
		adapted *= COORDINATE_SYSTEM_SCALE_CONVERSION;
		adapted += Leap::Vector(0.0f, -EYES_POSITION - 0.6f, -2.0f);
	}
	return adapted;
}

void LeapmotionPointer::update(bool mode)
{
	//updating the controller's position
	if (_init )
	{
		if (_controller.isConnected())
		{
			if (!_controller.frame().hands().isEmpty())
			{
				//the right-most hand's position is gotten from the Leapmotion device.
				//For more details about how the device work, see its SDK's documentation
				Leap::Vector rm_hand_pos = _controller.frame().hands().rightmost().palmPosition();
				rm_hand_pos = adaptToMode(rm_hand_pos, mode);

				//here we convert the Leap::Vector from the Leapmotion's SDK into a glm::vec3 from the GLM library
				_position = glm::vec3(rm_hand_pos.x, rm_hand_pos.y, rm_hand_pos.z);

				//The _position is adapted according to the translations from the Scene's WorldMatrix
				_position = glm::vec3(_invertedWorldMatrix*glm::vec4(_position, 1.0f));

				//pinching value goes from 1.0 to 0.5 and allows to visually represent the pinching strength
				//by scaling the LeapmotionPointer's Model depending on this value.
				//This means 1.0 for an open hand and 0.5 for a fully pinching hand
				float pinchingValue(1.0f - 0.5f*_controller.frame().hands().rightmost().pinchStrength());

				//all models' position are then updated 
				_pointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), _position)
					*glm::scale(glm::mat4(1.0f), glm::vec3(pinchingValue*LEAP_POINTER_SIZE)));
				
				_referencePointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), _position)
					*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));

				_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, -EYES_POSITION + 0.01f, _position.z))
					*glm::scale(glm::mat4(1.0f), glm::vec3(pinchingValue*LEAP_POINTER_SIZE)));
			}
		}

		//handling the assignedStructure
		if (_p_structure != NULL)
		{
			//If the Leapmotion Pointer is linked to a Structure and the user's hand is still pinching, we move this Structure
			if (Pinching())
			{
				_p_structure->Drag(_position);
			}
			else//Otherwise it means that the user's hand is open again and we can drop the Structure
			{
				std::cout << "pinching strength :" << _controller.frame().hands().rightmost().pinchStrength() << std::endl;
				unsigned int buttonID = _p_structure->LinkedButtonID();
				
				_p_structure->Drop();

				//the GUI is notified that a structure has been dropped so it can pop a new one
				_p_gui->DroppedStructure(buttonID);
				_p_structure = NULL;
			}
		}
	}
}

void LeapmotionPointer::UpdateWorldMatrix(const glm::mat4& worldMatrix)
{
	_invertedWorldMatrix = glm::inverse(worldMatrix);
}

void LeapmotionPointer::Draw(const glm::mat4& VP) const
{
	if (_init)
	{
		glEnable(GL_BLEND);
		_pointerModel->Draw(VP);
		_referencePointerModel->Draw(VP);
		_shadow->Draw(VP);
		glDisable(GL_BLEND);
	}
}




bool LeapmotionPointer::Pinching() const
{

	bool pinching = false;
	if (_controller.isConnected())
	{
		if (!_controller.frame().hands().isEmpty())
		{
			//The pinching value goes from 0.0 for a fully open hand 
			//to 1.0 for a hand where the thumb is in direct contact with another finger
			//0.8 has been chosen for a minimum pinching value because the Leapmotion device
			//return values smaller than 1.0 for an actually pinching hand
			if (_controller.frame().hands().rightmost().pinchStrength() > PINCHING_LIMIT)
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

void LeapmotionPointer::AssignStructure(MovableStructure* p_structure)
{
	_p_structure = p_structure;
}

MovableStructure* LeapmotionPointer::AssignedStructure() const
{
	return _p_structure;
}

void LeapmotionPointer::CleanUp()
{
	_referencePointerModel->CleanUp();
	_pointerModel->CleanUp();
	_shadow->CleanUp();
}