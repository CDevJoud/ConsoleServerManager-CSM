// O------------------------------------LICENSE--------------------------------------O
// |  MIT License																	 |
// |  																				 |
// |  Copyright(c) 2023 Joud Kandeel												 |
// |  																				 |
// |  Permission is hereby granted, free of charge, to any person obtaining a copy	 |
// |  of this software and associated documentation files(the "Software"), to deal	 |
// |  in the Software without restriction, including without limitation the rights	 |
// |  to use, copy, modify, merge, publish, distribute, sublicense, and /or sell	 |
// |  copies of the Software, and to permit persons to whom the Software is			 |
// |  furnished to do so, subject to the following conditions :						 |
// |  																				 |
// |  The above copyright noticeand this permission notice shall be included in all	 |
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
#include <vector>
#include <State.hpp>
#include <memory>
using namespace ugr;

namespace IExtreme::Application::CSM
{
	struct Vertex
	{
		float x, y, z;
	};
	struct Triangle
	{
		Vertex p[3]{};
	};
	struct Mesh
	{
		std::vector<Triangle> tris;
	};
	struct Matrix
	{
		float m[4][4]{};
	};
	class MainMenu : public State
	{
	public:
		MainMenu(ugr::ConsoleWindow* cw);
		~MainMenu();
		
		//Overided virtual functions
	public:
		virtual ugr::BOOL OnCreate() override;
		virtual ugr::BOOL OnUpdate() override;
		virtual ugr::BOOL OnRender() override;

	private:
		void RenderMesh(Mesh& m);
		Vertex MulMatrixVertex(Vertex& i, Matrix& m);

		Mesh obj;
		Matrix PP;
		std::unique_ptr<Panel> panel;
		Vector2i panSize;
	};
}


