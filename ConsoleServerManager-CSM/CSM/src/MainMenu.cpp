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

#include "MainMenu.hpp"
namespace IExtreme::Application::CSM
{
	MainMenu::MainMenu(ugr::ConsoleWindow* cw) : State(cw)
	{
		this->panel = std::make_unique<ugr::Panel>();
	}
	MainMenu::~MainMenu()
	{

	}
	ugr::BOOL MainMenu::OnCreate()
	{
		this->panSize = { 230, 70 };
		this->panel->CreatePanel(panSize);
		this->obj.tris = {
			{0, 0, 0,     1, 0, 0,     1, 0, 0}
		};

		float Near = 0.1f;
		float Far = 1000.0f;
		float AspectRatio = (float)panSize.y / (float)panSize.x;
		float Fov = 90.0f;
		float FovRad = 1.0f / tanf(Fov / 2.0f / 180.0f * 3.14f);

		this->PP.m[0][0] = AspectRatio * FovRad;
		this->PP.m[1][1] = FovRad;
		this->PP.m[2][2] = Far / (Far - Near);
		this->PP.m[3][2] = (-Far * Near) / (Far - Near);
		this->PP.m[2][3] = 1.0f;
		return TRUE;
	}
	ugr::BOOL MainMenu::OnUpdate()
	{

		return TRUE;
	}
	ugr::BOOL MainMenu::OnRender()
	{
		this->panel->ClearScreen();



		this->panel->Display();



		this->CGE->RenderPanel(this->panel.get());

		return TRUE;
	}
	void MainMenu::RenderMesh(Mesh& m)
	{
		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++)
		{
			
		}
	}
	Vertex MainMenu::MulMatrixVertex(Vertex& i, Matrix& m)
	{
		Vertex o;
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
		return o;
	}
}
