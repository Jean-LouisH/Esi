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

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <application/scene/assets/image.hpp>
#include <application/scene/assets/mesh.hpp>
#include "vertex_array.hpp"
#include <memory>

namespace Omnific
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		VertexBuffer(std::shared_ptr<Mesh> mesh, std::shared_ptr<VertexArray> vertexArray);
		VertexBuffer(std::shared_ptr<Image> image, std::shared_ptr<VertexArray> vertexArray);
		~VertexBuffer();
		void bind();
		void deleteVertexBuffer();
		unsigned int getIndexCount();
	private:
		GLuint vertexBufferID = 0;
		GLuint elementBufferID = 0;
		GLsizei indexCount;
	};
}

