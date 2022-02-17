#include <iostream>
#include <ctime>
#include "Rectangle.h"
#include "Circle.h"
#include "SDL.h"

float aiming(float px, float py, float mx, float my)
{
	if (mx <= px && my <= py)
		return atan(float(py - my) / float(px - mx)) - M_PI;
	else if (mx <= px && my >= py)
		return atan(float(py - my) / float(px - mx)) - M_PI;
	else if (mx >= px && my >= py)
		return atan(float(my - py) / float(mx - px));
	else if (mx >= px && my <= py)
		return atan(float(py - my) / float(px - mx));
}

float fromDegtoRad(float degrees)
{
	return degrees * M_PI / 180.f;
}

int main(int argc, char* argv[])
{
	bool isInMenu = true;
	srand((unsigned)time(0));
	const char title[18] = "Enter the Gungeon";

	bool quit = false;
	int windowWidth = 1000, windowHeight = 800;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	std::cout << "----" << title << "----" << std::endl;
	std::cout << "Resolution: " << windowWidth << "x" << windowHeight << std::endl;
	std::cout << "WASD to move\nleft_click to shoot\nSPACE to jump";
	SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	int frameDelay = 17;

	int mx = 0;
	int my = 0;
	int px = windowWidth / 2;
	int py = windowHeight / 2;
	int v = 5;
	int s = 30;

	bool up = false, down = false, left = false, right = false;

	int vv = 0;
	int a = 3;

	float aim = 0;
	int floorCount = 1;
	bool jumping = false;
	bool floating = false;
	int temp = py;
	int deltaTime;

	Rectangle* head = new Rectangle();

	Rectangle *torso = new Rectangle();

	Rectangle *leftLeg = new Rectangle();
	Rectangle *rightLeg = new Rectangle();

	Rectangle *leftArm = new Rectangle();
	Circle *leftGlove = new Circle();
	Rectangle *rightArm = new Rectangle();

	Rectangle *rifle = new Rectangle();

	while (!quit)
	{
		deltaTime = SDL_GetTicks();

		//Read trough remaing events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_UP:
					break;

				case SDLK_s:
				case SDLK_DOWN:
					break;

				case SDLK_a:
				case SDLK_LEFT:
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					break;

				case SDLK_r:
					break;

				case SDLK_SPACE:
					if (vv == 0 && !jumping)
					{
						vv = -18;
						temp = py;
					}
					floating = true;
					break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_UP:
					up = false;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					down = false;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					left = false;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					right = false;
					break;

				case SDLK_SPACE:
					floating = false;
					break;
				}
				break;
			}
		}

		//TODO meassure collision detection
		if (jumping)
		{
			py += vv;
			vv += a;
		}



		//movement
		if (up && py >= 0) py -= v;
		if (down && py < windowHeight - s * 3) py += v;
		if (left && px >= 0) px -= v;
		if (right && px < windowWidth - s) px += v;



		//checks cursor pos
		if (0 < event.motion.x &&
			windowWidth > event.motion.x &&
			0 < event.motion.y &&
			windowHeight > event.motion.y &&
			event.motion.y != 1024)
		{
			mx = event.motion.x;
			my = event.motion.y;
		}
		aim = aiming(px + s + s / 2, py + s, mx, my);

		head->SetRectangle(Point2D(px + 2, py - s + 2), s - 4, s - 4);

		torso->SetRectangle(Point2D(px, py), s, s * 2);

		leftLeg->SetRectangle(Point2D(px, py + s * 2), s / 2 - 2, s * 2);
		rightLeg->SetRectangle(Point2D(px + s / 2 + 2, py + s * 2), s / 2 - 2, s * 2);

		leftArm->SetRectangle(Point2D(px - s / 2, py + s / 5), s / 2, s + s / 2);
		leftGlove->SetCircle(Point2D(px - s * 3 / 4, py + s + s / 2), s / 2);
		rightArm->SetRectangle(Point2D(px + s, py + s / 5), s / 2, s + s / 2);

		rifle->SetRectangle(Point2D(px + s + s / 2, py + s + s / 2), s + 2 * s / 3, s / 3);
		rifle->SetRotation(aim, Point2D(0, -6));

		//Background
		SDL_SetRenderDrawColor(renderer, 195, 176, 145, 0);
		SDL_RenderClear(renderer); // clear with the render color


		//stuff that works

		SDL_Texture *Tile = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, s, s * 4);

		unsigned char *bytes = nullptr;

		int pitch = 0;

		SDL_LockTexture(Tile, nullptr, reinterpret_cast<void**>(&bytes), &pitch);
		unsigned char rgba[4] = { 120, 80, 39, 255 };
		for (size_t y = 0; y < s * 4; y++)
		{
			for (size_t x = 0; x < s; x++)
			{
				memcpy(&bytes[(y * s + x) * sizeof(rgba)], rgba, sizeof(rgba));
			}
		}
		SDL_UnlockTexture(Tile);
		SDL_Rect destination = { 320, 240, s, s * 4 }; // top-left corner
		int tempAngle = SDL_GetTicks() * 0.03;
		SDL_RenderCopyEx(renderer, Tile, NULL, &destination, tempAngle, NULL, SDL_FLIP_NONE);

		// top-left
		int tlX = -s * cos(fromDegtoRad(tempAngle)) + s * 4 * sin(fromDegtoRad(tempAngle)) + 320;
		int tlY = -s * sin(fromDegtoRad(tempAngle)) - s * 4 * cos(fromDegtoRad(tempAngle)) + 240;

		//bottom-left
		int blX = -s * cos(fromDegtoRad(tempAngle)) - s * 4 * sin(fromDegtoRad(tempAngle)) + 320;
		int blY = -s * sin(fromDegtoRad(tempAngle)) + s * 4 * cos(fromDegtoRad(tempAngle)) + 240 + s * 4;

		//top-right
		int trX = s * cos(fromDegtoRad(tempAngle)) + s * 4 * sin(fromDegtoRad(tempAngle)) + 320 + s;
		int trY = s * sin(fromDegtoRad(tempAngle)) - s * 4 * cos(fromDegtoRad(tempAngle)) + 240;

		//bottom-right
		int brX = s * cos(fromDegtoRad(tempAngle)) - s * 4 * sin(fromDegtoRad(tempAngle)) + 320 + s;
		int brY = s * sin(fromDegtoRad(tempAngle)) + s * 4 * cos(fromDegtoRad(tempAngle)) + 240 + s * 4;
		
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		//top-left to bottom-left
		SDL_RenderDrawLineF(renderer,
		blX, tlY,
		blX, brY);
		//top-right to bottom-right
		SDL_RenderDrawLineF(renderer,
		trX, tlY,
		trX, brY
		);
		//top-left to top-right
		SDL_RenderDrawLineF(renderer,
		blX, tlY,
		trX, tlY
		);
		//bottom-left to bottom-right
		SDL_RenderDrawLineF(renderer,
		blX, brY,
		trX, brY);
		


		//end of stuff that works

		//tables
		SDL_SetRenderDrawColor(renderer, 120, 80, 39, 0);
		SDL_RenderDrawLineF(renderer, 0, 240, 320, 240);

		//reloading
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

		//shadow
		SDL_SetRenderDrawColor(renderer, 99, 95, 44, 0);

		//head
		SDL_SetRenderDrawColor(renderer, 150, 50, 99, 0);
		// head->render(renderer);

		//torso
		SDL_SetRenderDrawColor(renderer, 195, 50, 99, 0);
		torso->render(renderer);

		//legs
		SDL_SetRenderDrawColor(renderer, 14, 100, 5, 0);
		leftLeg->render(renderer);
		rightLeg->render(renderer);

		//rifle
		SDL_SetRenderDrawColor(renderer, 255, 171, 171, 0);
		//rifle->render(renderer);

		//arms
		SDL_SetRenderDrawColor(renderer, 18, 120, 55, 0);
		leftArm->render(renderer);
		rightArm->render(renderer);
		
		//gloves
		SDL_SetRenderDrawColor(renderer, 200, 200, 93, 0);
		leftGlove->render(renderer);

		//hud
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);


		//push frame
		SDL_RenderPresent(renderer);


		SDL_Delay(100);
		// deltaTime = SDL_GetTicks() - deltaTime;
		// if (frameDelay > deltaTime)
		// 	SDL_Delay(frameDelay - deltaTime);
	} //end of game-loop

	//
	//	deallocating
	//

	delete head;

	delete torso;

	delete leftLeg;
	delete rightLeg;

	delete leftArm;
	delete rightArm;

	delete rifle;

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}