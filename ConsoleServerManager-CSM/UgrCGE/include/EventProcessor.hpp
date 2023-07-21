#pragma once
#include <Windows.h>
#include <Vector.hpp>
namespace ugr
{
	class EventProcessor
	{
	private:
		struct KeyStrokesCondition
		{
			BOOL bStrokePressed;
			BOOL bStrokeReleased;
			BOOL bStrokeIsHeld;
		} m_KeyboardCondition[256], m_MouseCondition[5];
		SHORT m_NewKeyboardCondition[256] = { 0 };
		SHORT m_OldKeyboardCondition[256] = { 0 };
		BOOL m_OldMouseCondition[5] = { 0 };
		BOOL m_NewMouseCondition[5] = { 0 };
	public:
		EventProcessor() = default;
		EventProcessor(HANDLE consoleInput);
		enum class MouseType
		{
			Left = 0, Right, Middle
		};
		

		KeyStrokesCondition Keyboard(INT ID) { return this->m_KeyboardCondition[ID]; }
		Vector2i GetMousePos() const { return this->m_mousePos; }
		KeyStrokesCondition Mouse(MouseType ID);
		VOID ProcessEvents();
	protected:
		VOID InitEventProcessor(HANDLE hConsoleInput);
	private:
		Vector2i m_mousePos;
		HANDLE m_handleConsoleInput = nullptr;
		
	};
}
