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

#include "ProMainMenu.hpp"
#include <algorithm>
namespace IExtreme::Application::CSM
{
	enum COLOUR
	{
		FG_BLACK = 0x0000,
		FG_DARK_BLUE = 0x0001,
		FG_DARK_GREEN = 0x0002,
		FG_DARK_CYAN = 0x0003,
		FG_DARK_RED = 0x0004,
		FG_DARK_MAGENTA = 0x0005,
		FG_DARK_YELLOW = 0x0006,
		FG_GREY = 0x0007, // Thanks MS :-/
		FG_DARK_GREY = 0x0008,
		FG_BLUE = 0x0009,
		FG_GREEN = 0x000A,
		FG_CYAN = 0x000B,
		FG_RED = 0x000C,
		FG_MAGENTA = 0x000D,
		FG_YELLOW = 0x000E,
		FG_WHITE = 0x000F,
		BG_BLACK = 0x0000,
		BG_DARK_BLUE = 0x0010,
		BG_DARK_GREEN = 0x0020,
		BG_DARK_CYAN = 0x0030,
		BG_DARK_RED = 0x0040,
		BG_DARK_MAGENTA = 0x0050,
		BG_DARK_YELLOW = 0x0060,
		BG_GREY = 0x0070,
		BG_DARK_GREY = 0x0080,
		BG_BLUE = 0x0090,
		BG_GREEN = 0x00A0,
		BG_CYAN = 0x00B0,
		BG_RED = 0x00C0,
		BG_MAGENTA = 0x00D0,
		BG_YELLOW = 0x00E0,
		BG_WHITE = 0x00F0,
	};

	enum PIXEL_TYPE
	{
		PIXEL_SOLID = 0x2588,
		PIXEL_THREEQUARTERS = 0x2593,
		PIXEL_HALF = 0x2592,
		PIXEL_QUARTER = 0x2591,
	};

	CharPixel GetColour(float lum)
	{
		short bg_col, fg_col;
		wchar_t sym;
		int pixel_bw = (int)(13.0f * lum);
		switch (pixel_bw)
		{
		case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

		case 1: bg_col = BG_DARK_GREY; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
		case 2: bg_col = BG_DARK_GREY; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
		case 3: bg_col = BG_DARK_GREY; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 4: bg_col = BG_DARK_GREY; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

		case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
		case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
		case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

		case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
		case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
		case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
		case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
		default:
			bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
		}

		CharPixel c;
		c.Color = bg_col | fg_col;
		c.Char.UnicodeChar = sym;
		return c;
	}
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

		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++) *it._Ptr = ProjectTriangle(*it._Ptr, matRotX);
	}
	void RotateY(Mesh& m, float rotation)
	{
		Matrix matRotY;
		matRotY.m[0][0] = cosf(rotation);
		matRotY.m[1][1] = 1.0f;
		matRotY.m[2][0] = sinf(rotation);
		matRotY.m[0][2] = -sinf(rotation);
		matRotY.m[2][2] = cosf(rotation);

		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++) *it._Ptr = ProjectTriangle(*it._Ptr, matRotY);
	}

	MainMenu::MainMenu(ugr::ConsoleWindow* cw) : State(cw)
	{
		this->panel = std::make_unique<ugr::Panel>();
	}
	MainMenu::~MainMenu()
	{
		for(int i = 0; i < this->btns.size(); i++)
			this->btns.pop_back();
	}
	ugr::BOOL MainMenu::OnCreate()
	{
		this->InitButtons();
		this->InitInputs();
		this->panSize = { 238, 73 };
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
		this->obj.tris.clear();
		this->obj.LoadFromObjectFile("CSM/obj/antenna.obj");

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
		RotateX(this->obj, 0.25f);
		return TRUE;
	}
	ugr::BOOL MainMenu::OnUpdate()
	{
		RotateX(this->obj, 0.05f * this->CGE->dt);
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

		for (auto& i : this->btns)
		{
			this->panel->RenderButton(i);
			i->ProcessEvents(this->CGE);
		}
		for (auto& i : this->m_mapInputs)
		{
			i.second->ProcessEvents(this->CGE);
			this->panel->RenderInputBox(i.second);
		}
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
		std::vector<Triangle> vecTrianglesToRaster;
		for (std::vector<Triangle>::iterator it = m.tris.begin(); it != m.tris.end(); it++)
		{
			Triangle triProjected, triTranslated;

			triTranslated = TranslateTriangle(*it._Ptr, { 1.75f, -0.5, 0.75f });

			Vertex normal, line1, line2;
			line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
			line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
			line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

			line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
			line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
			line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

			normal.x = line1.y * line2.z - line1.z * line2.y;
			normal.y = line1.z * line2.x - line1.x * line2.z;
			normal.z = line1.x * line2.y - line1.y * line2.x;

			float l = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
			normal.x /= l; normal.y /= l; normal.z /= l;

			if (normal.x * (triTranslated.p[0].x - vCamera.x) +
				normal.y * (triTranslated.p[0].y - vCamera.y) +
				normal.z * (triTranslated.p[0].z - vCamera.z) < 0.0f)
			{
				Vector3f light_direction = { -1.0f, -1.0f, 1.0f };
				float l = sqrtf(light_direction.x * light_direction.x + light_direction.y * light_direction.y + light_direction.z * light_direction.z);
				light_direction.x /= l; light_direction.y /= l; light_direction.z /= l;

				float dp = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;

				triProjected = ProjectTriangle(triTranslated, this->PP);
				ScaleToView(this->panSize, triProjected);

				CharPixel c = GetColour(dp);
				triProjected.cp.Color = c.Color;
				triProjected.cp.Char.UnicodeChar = c.Char.UnicodeChar;

				vecTrianglesToRaster.push_back(triProjected);
			}
		}
		sort(vecTrianglesToRaster.begin(), vecTrianglesToRaster.end(), [](Triangle& t1, Triangle& t2)
			{
				float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
				float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
				return z1 > z2;
			});
		for (std::vector<Triangle>::iterator it = vecTrianglesToRaster.begin(); it != vecTrianglesToRaster.end(); it++)
		{
			Triangle triProjected = (*it);
			this->panel->RasterizeTriangle(
				Vector2i(triProjected.p[0].x, triProjected.p[0].y),
				Vector2i(triProjected.p[1].x, triProjected.p[1].y),
				Vector2i(triProjected.p[2].x, triProjected.p[2].y), triProjected.cp.Char.UnicodeChar, triProjected.cp.Color
			);
		}
	}
	void MainMenu::InitButtons()
	{
		Button* btn = new Button();
		btn->SetPosition(Vector2i(50, 10));
		btn->SetTitle(L"IJUHJ", 0xC0);
		btn->SetColor(0x04);
		this->btns.push_back(btn);
	}
	void MainMenu::InitInputs()
	{
		InputBox* ib = new InputBox;
		ib->CreateBox(Vector2i(40, 1));
		ib->SetPosition(Vector2i(30, 25));
		ib->SetTitle(L"{Enter Host}", 0x8f);
		ib->SetStrInput(L"127.0.0.1");
		this->m_mapInputs.insert(std::pair<std::string, InputBox*>("Host", ib));
	}
}