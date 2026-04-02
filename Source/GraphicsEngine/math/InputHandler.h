#pragma once
#include <windows.h>
#include <bitset>
#include "KeyCodes.h"

namespace CommonUtilities
{


	class InputHandler
	{

	public:
		InputHandler();
		~InputHandler();

		bool UpdateEvents(UINT aMessage, WPARAM wParam, LPARAM lParam);

		bool IsKeyDown(const KeyCode aKeyCode) const;
		bool IsKeyPressed(const KeyCode aKeyCode) const;
		bool IsKeyReleased(const KeyCode aKeyCode) const;

		void UpdateInput();

		POINT GetMousePosition() const;
		POINT GetMouseDelta() const;

		int GetMouseWheelDelta() const;

	private:
		std::bitset<256> myCurrentKeyState;
		std::bitset<256> myPreviousKeyState;
		std::bitset<256> myTentativeKeyState;

		POINT myCurrentMousePosistion;
		POINT myPreviousMousePosistion;
		POINT myTentativeMousePosistion;

		int myMouseWheelDelta;
		int myMouseTentativeWheelDelta;
	};

}
