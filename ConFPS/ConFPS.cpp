#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

#include "oldConsoleGameEngine.h"

class UltimateMaze : public oldConsoleGameEngine {
	
public: UltimateMaze() {
		m_sAppname = L"Ultimate Maze Shooter";
	}
private:	 

	  float fPlayerX = 8.0f;
	  float fPlayerY = 8.0f;
	  float fPlayerA = 0.0f;

	  int nMapHeight = 16;
	  int nMapWidth = 16;

	  wstring map;

	  float fFOV = 3.14159 / 4.0;
	  float fDepth = 16.0f;
	  float fSpeed = 5.0f;

	  protected:
		  virtual bool OnUserCreate() {



			  map += L"#########.......#########.......";
			  map += L"#...............#...............";
			  map += L"#.......#########.......########";
			  map += L"#..............##..............#";
			  map += L"#......##......##......##......#";
			  map += L"#......##..............##......#";
			  map += L"#..............##..............#";
			  map += L"###............####............#";
			  map += L"##.............###.............#";
			  map += L"#............####............###";
			  map += L"#..............................#";
			  map += L"#..............##..............#";
			  map += L"#..............##..............#";
			  map += L"#...........#####...........####";
			  map += L"#..............................#";
			  map += L"###..####....########....#######";
			  map += L"####.####.......######..........";
			  map += L"#...............#...............";
			  map += L"#.......#########.......##..####";
			  map += L"#..............##..............#";
			  map += L"#......##......##.......#......#";
			  map += L"#......##......##......##......#";
			  map += L"#..............##..............#";
			  map += L"###............####............#";
			  map += L"##.............###.............#";
			  map += L"#............####............###";
			  map += L"#..............................#";
			  map += L"#..............................#";
			  map += L"#..............##..............#";
			  map += L"#...........##..............####";
			  map += L"#..............##..............#";
			  map += L"################################";


			  return true;

		  }

		  class oldcSprite {
		  public: 
			  oldcSprite() {

			  }

			  oldcSprite(int w, int h) {
				  Create(w, h);
			  }

			  oldcSprite(wString sFile) {
				  if (!Load(sfile))
					  Create(8, 8);
			  }
		  };

		  private {
			  nWidth = w;
			  nHeight = h;
			  m_Glyphs = new wchar_t[w * h];
			  m_Colours = new short[w * h];
			  for (int i = 0; i < w * h; i++) {
				  m_Glyphs[i] = L' ';
				  m_Colours[i] = FG_BLACK;
			  }
		  }

	public:
		void SetGlyph(int x, int y, wchar_t c) {
			if (x < x || x > nWidth || y < 0 || y > nHeight)
				return;
			else
				m_Glyphs[y * nWidth + x] = c;
		}

		void SetColour(int x, int y, wchar_t c) {
			if (x < 0 || x > nWidth || y < 0 || y > nHeight)
				return;
			else
				m_Colours[y * nWidth + x] = c;

		}

		wchar_t SampleGlyph(float x, float y) {
			int sx = x * (float)nWidth;
			int sy = y * (float)nHeight - 1;
			if (sx < 0 || sx > nWidth || sy < 0 || sy > nHeight)
				return L' ';
			else
				return m_Glyphs[sy * nWidth + sx];
		}

		short SampleColour(float x, float y) {
			int sx = x * (float)nWidth;
			int sy = y * (float)nHeight - 1;
			if (sx < 0 || sx > nWidth || sy < 0 || sy > nHeight)
				return FG_BLACK;
			else
				return m_Colour[sy * nWidth + sx];
		}


		  protected:

			  virtual bool OnUserUpdate() {

				  sprite = new oldcSprite(32, 32);
				  sCurrentSpriteFile = L"fps_wall1.spr";

				  return true;
			  }

			  virtual bool OnUserCreate(float fElapsedTime) {

			  // Controls
		// Handle CCW Rotation
			  if (m_keys[L'A'].bHeld)
				  fPlayerA -= (fSpeed * 0.8f) * fElapsedTime;

			  if (m_keys[L'D'].bHeld)
				  fPlayerA += (fSpeed * 0.8f) * fElapsedTime;

			  if (m_keys[L'W'].bHeld) {

				  fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
				  fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;

				  if (map.c_str()[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
					  fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
					  fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
				  }
			  }

			  if (m_keys[L'S'].bHeld) {

				  fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
				  fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;

				  if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
					  fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
					  fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
				  }
			  }

			  // Handle strafe Right movement & collision
			  if (m_keys[L'E'].bHeld) {

				  fPlayerX += cosf(fPlayerA) * fSpeed * fElapsedTime;
				  fPlayerY -= sinf(fPlayerA) * fSpeed * fElapsedTime;

				  if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
					  fPlayerX += cosf(fPlayerA) * fSpeed * fElapsedTime;
					  fPlayerY += sinf(fPlayerA) * fSpeed * fElapsedTime;
				  }
			  }


			  // Handle strafe Left movement & collision
			  if (m_keys[L'Q'].bHeld) {

				  fPlayerX -= cosf(fPlayerA) * fSpeed * fElapsedTime;
				  fPlayerY += sinf(fPlayerA) * fSpeed * fElapsedTime;

				  if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
					  fPlayerX += cosf(fPlayerA) * fSpeed * fElapsedTime;
					  fPlayerY += sinf(fPlayerA) * fSpeed * fElapsedTime;
				  }
			  }



			  for (int x = 0; x < ScreenWidth(); x++) {
				  // For each column, calculate the projected ray angle into world space
				  float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fFOV;

				  float fDistanceToWall = 0;
				  float fStepSize = 0.1f;
				  bool bHitWall = false;
				  bool bBoundary = false;

				  float fEyeX = sinf(fRayAngle);
				  float fEyeY = cosf(fRayAngle);

				  while (!bHitWall && fDistanceToWall < fDepth) {

					  fDistanceToWall += 0.1f;

					  int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
					  int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

					  // Test if ray is out of bounds
					  if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
						  bHitWall = true;		// Just set distance to maximum depth
						  fDistanceToWall = fDepth;
					  }
					  else {
						  // Ray is inbounds to test to see if the ray cell is a wall block
						  if (map.c_str()[nTestY * nMapWidth + nTestX] == '#') {
							  bHitWall = true;

							  vector<pair<float, float>> p; // distance, dot

							  for (int tx = 0; tx < 2; tx++)
								  for (int ty = 0; ty < 2; ty++) {
									  float vy = (float)nTestY + ty - fPlayerY;
									  float vx = (float)nTestX + tx - fPlayerX;
									  float d = sqrt(vx * vx + vy * vy);
									  float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									  p.push_back(make_pair(d, dot));
								  }

							  // Sort Pairs from closest to farthest
							  sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right)
								  {return left.first < right.first; });

							  float fBound = 0.01;
							  if (acos(p.at(0).second) < fBound) bBoundary = true;
							  if (acos(p.at(1).second) < fBound) bBoundary = true;
							  if (acos(p.at(2).second) < fBound) bBoundary = true;

						  }
					  }
				  }

				  // Calculate distance to ceiling and floor

				  int nCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)fDistanceToWall);
				  int nFloor = ScreenHeight() - nCeiling;

				  short nShade = ' ';

				  if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588;
				  else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
				  else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
				  else if (fDistanceToWall < fDepth)				nShade = 0x2591;
				  else											nShade = ' ';

				  if (bBoundary) nShade = ' ';


				  for (int y = 0; y < ScreenHeight(); y++) {
					  if (y <= nCeiling)
						  Draw(x, y, L' ');
					  else if (y > nCeiling && y <= nFloor)
						  screen[y * ScreenWidth() + x] = nShade;
					  else {
						  float b = 1.0f - (((float)y - ScreenHeight() / 2.0f) / ((float)ScreenHeight() / 2.0f));

						  if (b < 0.25)			nShade = '#';
						  else if (b < 0.5)		nShade = 'x';
						  else if (b < 0.75)		nShade = '.';
						  else if (b < 0.9)		nShade = '_';
						  else					nShade = ' ';
						  screen[y * ScreenWidth() + x] = nShade;



					  }
				  }


			  }

			  // Map
			  for (int nx = 0; nx < nMapWidth; nx++)
				  for (int ny = 0; ny < nMapWidth; ny++) {
					  Draw(nx + 1, ny + 1, map[ny * nMapWidth + nx]);
				  }
			  Draw(1 + (int)fPlayerY, 1 + (int)fPlayerX, L'P']);

			  screen[ScreenWidth() * ScreenHeight() - 1] = '\0';


			  swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);



			  WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth* nScreenHeight, { 0,0 }, & dwBytesWritten);


			  return true;



		  }


};

#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace std;




int main() {

	UltimateMaze game;
	game.ConstructConsole(340, 80, 4, 4);
	game.Start();
		

	return 0;
};