#pragma once
#include <cstdint>
#include <span>
#include <array>
#include <vector>
#include <list>
namespace kdaGraphics {

	enum class AdapterType {
		None,
		OpenGL,
		OpenGLES,
		Vulkan,
		DirectX9,
		DirectX11,
		DirectX12,
		Metal,
		Count
	};

	enum class AttribType {
		Float,
		Byte,
		Int
	};

	enum class Clear {
		COLOR,
		DEPTH,
		STENCIL
	};

	enum class Attrib {
		Position,  //!< a_position
		Normal,    //!< a_normal
		Tangent,   //!< a_tangent
		Bitangent, //!< a_bitangent
		Color0,    //!< a_color0
		Color1,    //!< a_color1
		Color2,    //!< a_color2
		Color3,    //!< a_color3
		Indices,   //!< a_indices
		Weight,    //!< a_weight
		TexCoord0, //!< a_texcoord0
		TexCoord1, //!< a_texcoord1
		TexCoord2, //!< a_texcoord2
		TexCoord3, //!< a_texcoord3
		TexCoord4, //!< a_texcoord4
		TexCoord5, //!< a_texcoord5
		TexCoord6, //!< a_texcoord6
		TexCoord7, //!< a_texcoord7

		Count
	};

	using Shader = uint32_t;
	using BufferVertex = uint32_t;
	using BufferIndex = uint32_t;
	using Program = uint32_t;
	using Texture = uint32_t;

	enum class TextureFormat {
		BGRA8,
		RGB8
	};

	enum class ShaderType {
		Vertex,
		Pixel,
		Compute
	};

	struct VertexLayout {
		Attrib attrib;
		uint16_t count;
		AttribType type;
		bool _normalized = false;
	};

	struct BufferLayoutDeclaration {
		std::list<VertexLayout> declaration;
	};

	// Main Function
	int initialize(void* nwt, uint16_t width, uint16_t height);
	void renderFrame();
	int finalize();

	// Graphics functions
	void setViewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height);
	void setClearColor(std::span<Clear> flags, uint32_t rgba, float depth, uint8_t stencil);
	void setVertexBuffer(BufferVertex buffer);
	void setIndexBuffer(BufferIndex buffer);
	void setProgram(Program program);
	void drawArray();
	void drawElements();
	Program createProgramGraphic(Shader vertex, Shader pixel);
	Program createProgramCompute(Shader compute);
	const Shader createShader(ShaderType type, std::span<const std::byte> shaderBin);
	BufferVertex createVertexBuffer(const BufferLayoutDeclaration & declaration, std::span<float> data);
	BufferIndex createIndexBuffer(std::span<uint32_t> data);
	Texture createTexture(int32_t width, int32_t height, TextureFormat format, std::span<const std::byte> data);
	void setViewProjection(std::span<const float> view, std::span<const float> projection);
	void setTransform(std::span<const float> transform);
}