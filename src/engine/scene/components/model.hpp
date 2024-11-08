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

#include "scene/components/component.hpp"
#include <foundations/resources/image.hpp>
#include <foundations/resources/shader.hpp>
#include <memory>
#include <glm.hpp>
#include <engine_api.hpp>
#include "foundations/resources/mesh.hpp"
#include "foundations/resources/material.hpp"
#include "foundations/resources/skeletal_animation.hpp"
#include "foundations/resources/rig.hpp"

namespace Omnific
{
	class OMNIFIC_ENGINE_API ShaderParameters
	{
	public:
		void set_int_uniform(std::string uniform_name, int value);
		void set_bool_uniform(std::string uniform_name, bool value);
		void set_float_uniform(std::string uniform_name, float value);
		void set_vec2_uniform(std::string uniform_name, glm::vec2 value);
		void set_vec3_uniform(std::string uniform_name, glm::vec3 value);
		void set_vec4_uniform(std::string uniform_name, glm::vec4 value);
		void set_mat4_uniform(std::string uniform_name, glm::mat4 value);

		std::unordered_map<std::string, int> int_uniforms;
		std::unordered_map<std::string, bool> bool_uniforms;
		std::unordered_map<std::string, float> float_uniforms;
		std::unordered_map<std::string, glm::vec2> vec2_uniforms;
		std::unordered_map<std::string, glm::vec3> vec3_uniforms;
		std::unordered_map<std::string, glm::vec4> vec4_uniforms;
		std::unordered_map<std::string, glm::mat4> mat4_uniforms;
	private:

	};

	class OMNIFIC_ENGINE_API Model : public Component
	{
	public:
		enum class FaceCullMode
		{
			NONE,
			BACK,
			FRONT,
			FRONT_AND_BACK
		};

		Model()
		{
			this->type = TYPE_STRING;
			this->shader_parameters = std::shared_ptr<ShaderParameters>(new ShaderParameters());
		};
		static constexpr const char* TYPE_STRING = "Model";

		virtual Registerable* instance() override
		{
			Model* clone = new Model(*this);
			clone->id = UIDGenerator::get_new_uid();
			return clone;
		}

		virtual void deserialize(YAML::Node yaml_node);
		void set_to_cube();
		void set_to_textured_cube(std::shared_ptr<Material> material);
		void set_to_image(std::shared_ptr<Image> image);
		void set_dimensions(float width, float height);
		void set_dimensions(float width, float height, float depth);
		void set_shader(std::shared_ptr<Shader> shader);
		void set_overriding_shader(std::shared_ptr<Shader> overriding_shader);
		void set_alpha(uint8_t value);
		void set_face_culling_to_none();
		void set_face_culling_to_front();
		void set_face_culling_to_back();
		void set_face_culling_to_front_and_back();
		uint8_t get_alpha();
		float get_alpha_in_percentage();
		bool is_no_face_culling();
		bool is_front_face_culling();
		bool is_back_face_culling();
		bool is_front_and_back_face_culling();
		void hide();
		void show();
		FaceCullMode get_face_cull_mode();
		std::shared_ptr<Image> get_image();
		std::shared_ptr<Shader> get_shader();
		std::shared_ptr<Shader> get_overriding_shader();
		bool is_renderable() override;
		glm::vec3 get_dimensions();

		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Material> material;
		std::shared_ptr<Rig> rig;
		std::vector<std::shared_ptr<SkeletalAnimation>> skeletal_animations;
		std::shared_ptr<ShaderParameters> shader_parameters;
	protected:
		glm::vec3 dimensions;
		uint8_t alpha = 255;
		FaceCullMode face_cull_mode = FaceCullMode::NONE;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Shader> overriding_shader;
	private:
		void build_uniform_references_from_shader(std::shared_ptr<Shader> shader);
	};
}