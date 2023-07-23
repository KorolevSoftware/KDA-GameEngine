#pragma once
#include <cstdint>
#include <span>
#include <array>

namespace kdaGraphics {

	enum class AdapterType {
		NONE,
		OPENGL,
		OPENGLES,
		VULKAN,
		DIRECTX9,
		DIRECTX11,
		DIRECTX12,
		METAL,
		COUNT
	};

	enum class AttribType {
		FLOAT,
		BYTE,
		INT
	};

	enum class Clear {
		COLOR,
		DEPTH,
		STENCIL
	};

	enum class Attrib {
		POSITION,
		NORMAL,
		TANGENT,
		BITANGENT,
		COLOR0,
		Color1,
		Color2,
		Color3,
		INDEXES,
		WEIGHT,
		TEXCOORD0
	};

	struct VertexLayout {
		Attrib attrib;
		uint16_t count;
		AttribType type;
		bool _normalized = false;
	};

	struct BufferLayoutDeclaration {
		std::array<VertexLayout, 5> declaration;
	};

	// Main Function
	int initialize(void* nwt, uint16_t width, uint16_t height);
	void renderFrame();
	int finalize();

	// Graphics functions
	void setViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void setClearColor(std::initializer_list<Clear> flags, uint32_t rgba, float depth, uint8_t stencil);
	void drawArray();
	void drawElements();
	void createBuffer(const BufferLayoutDeclaration & declaration, std::span<const std::byte> data);
	void createIndexBuffer(std::span<const std::byte> data);
	void setViewProjection(std::span<const float> view, std::span<const float> projection);
	void setTransform(std::span<const float> transform);
}