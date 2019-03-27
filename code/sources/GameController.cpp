#include "GameController.hpp"
namespace prz
{
	void GameController::handle_contact(b2Contact* contact, const ContactState& state)
	{
		std::cout << "Handling ";

		if (state == ContactState::BEGIN)
		{
			std::cout << "start of contact..." << std::endl;
		}
		else if (state == END)
		{
			std::cout << "end of contact..." << std::endl;
		}

		ContactState contactState = state;
	}
}