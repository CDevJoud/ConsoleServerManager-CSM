// O------------------------------------LICENSE--------------------------------------O
// |  MIT License																	 |
// |  																				 |
// |  Copyright(c) 2023-2024 Joud Kandeel											 |
// |  																				 |
// |  Permission is hereby granted, free of charge, to any person obtaining a copy	 |
// |  of this software and associated documentation files(the "Software"), to deal	 |
// |  in the Software without restriction, including without limitation the rights	 |
// |  to use, copy, modify, merge, publish, distribute, sublicense, and /or sell	 |
// |  copies of the Software, and to permit persons to whom the Software is			 |
// |  furnished to do so, subject to the following conditions :						 |
// |  																				 |
// |  The above copyright notice and this permission notice shall be included in all |
// |  copies or substantial portions of the Software.								 |
// |  																				 |
// |  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 |
// |  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 |
// |  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE	 |
// |  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER		 |
// |  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 |
// |  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	 |
// |  SOFTWARE.																		 |
// O---------------------------------------------------------------------------------O

#pragma once
#include <RemoteControl.hpp>
#include <MainMenu.hpp>
#include <stack>
#include <memory>

class Application : private ugr::ConsoleWindow
{
public:
	Application();
	~Application();
	INT Run();
	VOID ManageStates(IExtreme::Application::CSM::State::ExitState);
private:
	ugr::Panel MainMenu;
	BOOL m_bLoop = TRUE;
	//As we know stack is a dynamic container which mean everything will remain on the heap
	//but in this case we are storing the objects as a smart pointer to avoid getting object slicing.
	//The State class is 24 bytes and for ex RemoteControl class is 288, if we would to store it
	//we would lose data
	std::stack<std::unique_ptr<IExtreme::Application::CSM::State>> m_states;
};