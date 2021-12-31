// MIT License
// 
// Copyright (c) 2020 Jean-Louis Haywood
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "window.hpp"

Esi::Window::Window(const char* title, uint16_t width, uint16_t height, bool isFullscreen)
{
	this->isFullscreen = isFullscreen;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->sdlWindow = std::shared_ptr<SDL_Window>(SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_FULLSCREEN_DESKTOP & isFullscreen | SDL_WINDOW_OPENGL));

	SDL_DisableScreenSaver();
	SDL_GetCurrentDisplayMode(0, this->sdlDisplayMode.get());
}


void Esi::Window::setToWindowed(uint16_t width_px, uint16_t height_px)
{
	SDL_SetWindowFullscreen(this->sdlWindow.get(), 0);
	SDL_SetWindowSize(this->sdlWindow.get(), width_px, height_px);

}

void Esi::Window::setToFullscreen()
{
	SDL_SetWindowDisplayMode(this->sdlWindow.get(), this->sdlDisplayMode.get());
	SDL_SetWindowFullscreen(this->sdlWindow.get(), SDL_WINDOW_FULLSCREEN);
}

void Esi::Window::toggleWindowedFullscreen()
{
	this->isFullscreen = !isFullscreen;

	if (this->isFullscreen)
	{
		SDL_SetWindowFullscreen(this->sdlWindow.get(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(this->sdlWindow.get(), 0);
		SDL_SetWindowPosition(
			this->sdlWindow.get(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED);
	}

	SDL_ShowCursor(!this->isFullscreen);
}

void Esi::Window::resize(uint16_t width_px, uint16_t height_px)
{
	SDL_SetWindowSize(this->sdlWindow.get(), width_px, height_px);
	SDL_SetWindowPosition(this->sdlWindow.get(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Esi::Window::changeTitle(const char* title)
{
	SDL_SetWindowTitle(this->sdlWindow.get(), title);
}

void Esi::Window::changeIcon(Image image)
{
	SDL_SetWindowIcon(this->sdlWindow.get(), image.getSDLSurface());
}

void Esi::Window::maximize()
{
	SDL_MaximizeWindow(this->sdlWindow.get());
}

void Esi::Window::minimize()
{
	SDL_MinimizeWindow(this->sdlWindow.get());
}

void Esi::Window::raise()
{
	SDL_RaiseWindow(this->sdlWindow.get());
}

void Esi::Window::restore()
{
	SDL_RestoreWindow(this->sdlWindow.get());
}

void Esi::Window::hide()
{
	SDL_HideWindow(this->sdlWindow.get());
}

void Esi::Window::show()
{
	SDL_ShowWindow(this->sdlWindow.get());
}

void Esi::Window::sleep(int time_ms)
{
	if (time_ms > 0)
		SDL_Delay(time_ms);
}

void Esi::Window::swapBuffers()
{
	SDL_GL_SwapWindow(this->sdlWindow.get());
}

Esi::Rectangle Esi::Window::getWindowSize()
{
	Rectangle rectangle;
	int width = 0;
	int height = 0;
	
	SDL_GetWindowSize(this->sdlWindow.get(), &width, &height);
	rectangle.width = width;
	rectangle.height = height;

	return rectangle;
}

SDL_Window* Esi::Window::getSDLWindow()
{
	return this->sdlWindow.get();
}