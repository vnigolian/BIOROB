/*
@author Valentin NIGOLIAN
valentin.nigolian@epfl.ch
Fall 2015
*/
#include "LeapmotionPointer.hh"
#include "GUI.hh"


void LeapmotionPointer::Init(GUI* p_gui)
{
	if (!d_init)
	{
		if (d_controller.isConnected())
		{
			std::cout << "LeapMotion connected !" << std::endl;
		}
		else
		{
			std::cout << "LeapMotion not connected..." << std::endl;
		}

		d_p_pointerModel = new Cube("Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 0.3f));
		d_p_pointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, -1.0f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));

		d_p_referencePointerModel = new Cube("Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 0.3f));
		d_p_referencePointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, -1.0f))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));


		d_p_shadow = new Quad("Shaders/simple_vshader.glsl", "Shaders/colorvec_fshader.glsl", "", glm::vec4(1.0f, 0.0f, 0.0f, 0.3f));
		d_p_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(d_position.x, -EYES_POSITION + 0.01f, d_position.z))
			*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));


		d_p_structure = NULL;

		d_init = true;
		d_p_gui = p_gui;
	}
}


Leap::Vector LeapmotionPointer::AdaptToMode(Leap::Vector right_hand_pos, bool mode)
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
	if (d_init )
	{
		if (d_controller.isConnected())
		{
			if (!d_controller.frame().hands().isEmpty())
			{
				//the right-most hand's position is gotten from the Leapmotion device.
				//For more details about how the device work, see its SDK's documentation
				Leap::Vector rm_hand_pos = d_controller.frame().hands().rightmost().palmPosition();
				rm_hand_pos = AdaptToMode(rm_hand_pos, mode);

				//here we convert the Leap::Vector from the Leapmotion's SDK into a glm::vec3 from the GLM library
				d_position = glm::vec3(rm_hand_pos.x, rm_hand_pos.y, rm_hand_pos.z);

				//The _position is adapted according to the translations from the Scene's WorldMatrix
				d_position = glm::vec3(d_invertedWorldMatrix*glm::vec4(d_position, 1.0f));

				//pinching value goes from 1.0 to 0.5 and allows to visually represent the pinching strength
				//by scaling the LeapmotionPointer's Model depending on this value.
				//This means 1.0 for an open hand and 0.5 for a fully pinching hand
				float pinchingValue(1.0f - 0.5f*d_controller.frame().hands().rightmost().pinchStrength());

				//all models' position are then updated 
				d_p_pointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), d_position)
					*glm::scale(glm::mat4(1.0f), glm::vec3(pinchingValue*LEAP_POINTER_SIZE)));
				
				d_p_referencePointerModel->SetModelMatrix(glm::translate(glm::mat4(1.0f), d_position)
					*glm::scale(glm::mat4(1.0f), glm::vec3(LEAP_POINTER_SIZE)));

				d_p_shadow->SetModelMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(d_position.x, -EYES_POSITION + 0.01f, d_position.z))
					*glm::scale(glm::mat4(1.0f), glm::vec3(pinchingValue*LEAP_POINTER_SIZE)));
			}
		}

		//handling the assignedStructure
		if (d_p_structure != NULL)
		{
			//If the Leapmotion Pointer is linked to a Structure and the user's hand is still pinching, we move this Structure
			if (Pinching())
			{
				d_p_structure->Drag(d_position);
			}
			else//Otherwise it means that the user's hand is open again and we can drop the Structure
			{
				std::cout << "pinching strength :" << d_controller.frame().hands().rightmost().pinchStrength() << std::endl;
				unsigned int buttonID = d_p_structure->LinkedButtonID();
				
				d_p_structure->Drop();

				//the GUI is notified that a structure has been dropped so it can pop a new one
				d_p_gui->DroppedStructure(buttonID);
				d_p_structure = NULL;
			}
		}
	}
}

void LeapmotionPointer::UpdateWorldMatrix(const glm::mat4& worldMatrix)
{
	d_invertedWorldMatrix = glm::inverse(worldMatrix);
}

void LeapmotionPointer::Draw(const glm::mat4& VP) const
{
	d_p_pointerModel->Draw(VP);
	d_p_referencePointerModel->Draw(VP);
	d_p_shadow->Draw(VP);
}




bool LeapmotionPointer::Pinching() const
{

	bool pinching = false;
	if (d_controller.isConnected())
	{
		if (!d_controller.frame().hands().isEmpty())
		{
			//The pinching value goes from 0.0 for a fully open hand 
			//to 1.0 for a hand where the thumb is in direct contact with another finger
			//0.8 has been chosen for a minimum pinching value because the Leapmotion device
			//return values smaller than 1.0 for an actually pinching hand
			if (d_controller.frame().hands().rightmost().pinchStrength() > PINCHING_LIMIT)
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
	return d_position;
}

void LeapmotionPointer::AssignStructure(MovableStructure* p_structure)
{
	d_p_structure = p_structure;
}

MovableStructure* LeapmotionPointer::AssignedStructure() const
{
	return d_p_structure;
}

void LeapmotionPointer::CleanUp()
{
	d_p_referencePointerModel->CleanUp();
	d_p_pointerModel->CleanUp();
	d_p_shadow->CleanUp();
}