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
#include <vector>
#include <State.hpp>
#include <memory>
#include <string>
#include <fstream>
#include <strstream>
#include <map>
#pragma warning(disable:4996)
using namespace ugr;

namespace IExtreme::Application::CSM
{
	typedef struct Vertex
	{
		float x, y, z;
	}Vector3f;
	struct Triangle
	{
		Vertex p[3]{};
		CharPixel cp;
	};
	struct Mesh
	{
		std::vector<Triangle> tris;

		bool LoadFromObjectFile(std::string sFilename)
		{
			std::ifstream f(sFilename);
			if (!f.is_open())
				return false;

			// Local cache of verts
			std::vector<Vector3f> verts;

			while (!f.eof())
			{
				char line[128];
				f.getline(line, 128);

				std::strstream s;
				s << line;

				char junk;

				if (line[0] == 'v')
				{
					Vector3f v;
					s >> junk >> v.x >> v.y >> v.z;
					verts.push_back(v);
				}

				if (line[0] == 'f')
				{
					int f[3];
					s >> junk >> f[0] >> f[1] >> f[2];
					tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
				}
			}

			return true;
		}
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
		ugr::BOOL OnCreate() override;
		ugr::BOOL OnUpdate() override;
		ugr::BOOL OnRender() override;
		ExitState ExitVal() override;
	private:
		ExitState es;
		void RenderMesh(Mesh& m);
		void InitButtons();
		void InitInputs();

		Mesh obj;
		Matrix PP;
		std::unique_ptr<Panel> panel;
		std::map<std::string, ugr::InputBox*> m_mapInputs;
		std::vector<Button*> btns;
		Vector2i panSize;
		Vector3f vCamera;
	};
}


