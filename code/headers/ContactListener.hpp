/**
 * @file ContactListener.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief
 * @version 0.1
 * @date 2019-03-18
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef BOX2D_ANIMATED_SCENE_CONTACT_LISTENER_H_
#define BOX2D_ANIMATED_SCENE_CONTACT_LISTENER_H_

#include "Internal/Declarations/Declarations.hpp"

#include <Box2D/Box2D.h>

#include <functional>

namespace prz
{
	template<class ContactHandler>
	class ContactListener : public b2ContactListener
	{
		using ContactHandlerFn = void(ContactHandler::*) (b2Contact* contact, const ContactState& state);

	public:

		static ContactListener<ContactHandler>& instance()
		{
			static ContactListener<ContactHandler> instance;
			return instance;
		}

	public:

		void BeginContact(b2Contact* contact) override
		{
			if (fnContactHandler_ && contactHandler_)
			{
				std::cout << "Contact began \n" << std::endl;

				/*std::function<void()> handlerCall = std::bind(fnContactHandler_, contactHandler_, contact, ContactState::Begin);
				handlerCall();*/ // Another way to call a generic function from generic object

				(contactHandler_->*fnContactHandler_)(contact, ContactState::BEGIN);
			}
		}

		void EndContact(b2Contact* contact) override
		{
			if (fnContactHandler_ && contactHandler_)
			{
				std::cout << "Contact finished \n" << std::endl;
				
				(contactHandler_->*fnContactHandler_)(contact, ContactState::END);
			}
		}

	public:

		void set(ContactHandlerFn contactHandler, ContactHandler* handlerObj)
		{
			set_contact_handler_fn(contactHandler);
			set_contact_handler_obj(handlerObj);
		}

		void set_contact_handler_fn(ContactHandlerFn fnContactHandler)
		{
			fnContactHandler_ = fnContactHandler;
		}

		void set_contact_handler_obj(ContactHandler* handlerObj)
		{
			contactHandler_ = handlerObj;
		}

	private:

		ContactListener()
			:
			fnContactHandler_(nullptr),
			contactHandler_(nullptr)
		{}

	private:
		
		ContactHandlerFn fnContactHandler_;
		ContactHandler* contactHandler_;
	};
}
#endif // !BOX2D_ANIMATED_SCENE_CONTACT_LISTENER_H_