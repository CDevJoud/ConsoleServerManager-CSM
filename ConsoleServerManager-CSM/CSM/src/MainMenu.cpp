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

#include "MainMenu.hpp"
namespace IExtreme::Application::CSM
{
	Vertex MulMatrixVertex(Vertex& i, Matrix& m)
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
	Triangle ProjectTriangle(Triangle& i, Matrix& m)
	{
		Triangle o;
		o.p[0] = MulMatrixVertex(i.p[0], m);
		o.p[1] = MulMatrixVertex(i.p[1], m);
		o.p[2] = MulMatrixVertex(i.p[2], m);
		return o;
	}
	VOID ScaleToView(Vector2i viewsize, Triangle& i)
	{
		i.p[0].x += 1.0f;	i.p[0].y += 1.0f;
		i.p[1].x += 1.0f;	i.p[1].y += 1.0f;
		i.p[2].x += 1.0f;	i.p[2].y += 1.0f;

		i.p[0].x *= 0.5f * viewsize.x;
		i.p[0].y *= 0.5f * viewsize.y;
		i.p[1].x *= 0.5f * viewsize.x;
		i.p[1].y *= 0.5f * viewsize.y;
		i.p[2].x *= 0.5f * viewsize.x;
		i.p[2].y *= 0.5f * viewsize.y;
	}
	Triangle TranslateTriangle(Triangle& i, Vertex pos)
	{
		Triangle o;
		o.p[0].x = i.p[0].x + pos.x;
		o.p[1].x = i.p[1].x + pos.x;
		o.p[2].x = i.p[2].x + pos.x;
		o.p[0].y = i.p[0].y + pos.y;
		o.p[1].y = i.p[1].y + pos.y;
		o.p[2].y = i.p[2].y + pos.y;
		o.p[0].z = i.p[0].z + pos.z;
		o.p[1].z = i.p[1].z + pos.z;
		o.p[2].z = i.p[2].z + pos.z;
		return o;
	}
	void RotateX(Mesh& m, float rotation)
	{
		Matrix matRotX;
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(rotation);
		matRotX.m[1][2] = sinf(rotation);
		matRotX.m[2][1] = -sinf(rotation);
		matRotX.m[2][2] = cosf(rotation);

		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++)
		{
			*it._Ptr = ProjectTriangle(*it._Ptr, matRotX);
		}
	}
	void RotateY(Mesh& m, float rotation)
	{
		Matrix matRotY;
		matRotY.m[0][0] = cosf(rotation);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[2][0] = sinf(rotation);
		matRotY.m[0][2] = -sinf(rotation);
		matRotY.m[2][2] = cosf(rotation);

		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++)
		{
			*it._Ptr = ProjectTriangle(*it._Ptr, matRotY);
		}
	}

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
			// SOUTH
		{ 0, 0, 0,    0, 1, 0,    1, 1, 0},
		{ 0, 0, 0,    1, 1, 0,    1, 0, 0},                                                     
		{ 1, 0, 0,    1, 1, 0,    1, 1, 1},
		{ 1, 0, 0,    1, 1, 1,    1, 0, 1},                                                    
		{ 1, 0, 1,    1, 1, 1,    0, 1, 1},
		{ 1, 0, 1,    0, 1, 1,    0, 0, 1},                                                      
		{ 0, 0, 1,    0, 1, 1,    0, 1, 0},
		{ 0, 0, 1,    0, 1, 0,    0, 0, 0},                                                    
		{ 0, 1, 0,    0, 1, 1,    1, 1, 1},
		{ 0, 1, 0,    1, 1, 1,    1, 1, 0},                                                  
		{ 1, 0, 1,    0, 0, 1,    0, 0, 0},
		{ 1, 0, 1,    0, 0, 0,    1, 0, 0},
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
		RotateX(this->obj, 1.0f * this->CGE->dt);
		RotateY(this->obj, 1.0f * this->CGE->dt);
		if (this->CGE->Keyboard(0x1B).bStrokeReleased)
		{
			this->m_bQuit = TRUE;
			this->es = State::ExitState::Exit;
		}
		return TRUE;
	}
	ugr::BOOL MainMenu::OnRender()
	{
		this->panel->ClearScreen();

		this->RenderMesh(this->obj);

		this->panel->Display();

		this->CGE->RenderPanel(this->panel.get());

		return TRUE;
	}
	State::ExitState MainMenu::ExitVal()
	{
		return es;
	}
	void MainMenu::RenderMesh(Mesh& m)
	{
		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++)
		{
			Triangle triProjected, triTranslated;
			triTranslated = TranslateTriangle(*it._Ptr, { 0, 0, 1.5f });
			triProjected = ProjectTriangle(triTranslated, PP);
			ScaleToView(this->panSize, triProjected);

			VAO tris[] = {
				triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y
			};
			this->panel->RenderTriangle(tris);
		}
	}
	
}
