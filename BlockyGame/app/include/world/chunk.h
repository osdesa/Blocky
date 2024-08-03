#pragma once

#include <vector>
#include "camera.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/shader.h"
#include <graphics/renderer.h>
#include "graphics/Texture.h"

#include <map>
#include "world/block_types.hpp"

#include <vector>
#include <array>
#include "external/FastNoiseLite.h"

#include <cstdint>

namespace Blocky {
	class Chunk : Renderer
	{
	public:

		Chunk() {};
		~Chunk();

		Chunk(const Chunk&) = delete;
		Chunk& operator=(const Chunk&) = delete;
		Chunk (Chunk&& rhs) noexcept
		{
			Logger::output(WARNING, "should not happen Chunk non implement function");
		}

		Chunk& operator=(Chunk&& rhs) noexcept {
			va = std::move(rhs.va);
			waterVao = std::move(rhs.waterVao);

			ib = std::move(rhs.ib);
			waterIb = std::move(rhs.waterIb);

			vb = std::move(rhs.vb);
			waterVb = std::move(rhs.waterVb);

			chunkShader = std::move(rhs.chunkShader);
			waterShader = std::move(rhs.waterShader);

			texture = std::move(rhs.texture);

			vertexData = std::move(rhs.vertexData);
			indicesData = std::move(rhs.indicesData);
			waterVertexData = std::move(rhs.waterVertexData);
			waterIndicesData = std::move(rhs.waterIndicesData);

			blockMeshData = std::move(rhs.blockMeshData);
			centx = std::move(rhs.centx);
			centz = std::move(rhs.centz);
			center = std::move(rhs.center);
			pythaDis = std::move(rhs.pythaDis);
			seed = std::move(rhs.seed);

			return *this;
		}

		void Shape(VertexArray& vao, VertexArray& waterVa, Shader& shader, Shader& WaterShader, int centerX, int centerZ,
			FastNoiseLite noise, std::map<Vec2, int>& hightMap, int hash);

		void GenerateMesh(std::unordered_map<uint32_t, BlockData>& texLoc, std::map<Vec2, int>& hightMap, FastNoiseLite noise);
		std::map<Vec3, uint32_t>& GenerateDetails(std::unordered_map<uint32_t, BlockData>& texLoc, std::map<Vec2, int>& hightMap, FastNoiseLite noise, std::map<Vec3, uint32_t>& blocksToPlace);
		std::map<Vec3, uint32_t>& PlaceTree(int x, int z, int y, std::map<Vec3, uint32_t>& blocksToPlace, BlockTypes type);
		void SetBlock(int x, int y, int z, uint32_t blockType);

		std::vector<float> GetVertexData() { return vertexData; }
		std::vector<uint32_t> GetIndices() { return indicesData; }

		void Draw(Camera& camera, bool underWater, float lightValue);

		// pythagoren distance
		float distance() { return (centx * centx) + (centz * centz); }
		const float GetDistance() { return pythaDis; }
		void SetDistance(Vec3& playerPos);
		inline Vec2 GetCenter() { return center; }
		inline uint8_t GetBlock(int x, int y, int z) { return blockMeshData[x][z][y]; }
		inline auto GetMeshData() { return blockMeshData;}
		inline void ForceSetDist(float dist) { pythaDis = dist; }

	private:
		std::vector<float> vertexData;
		std::vector<uint32_t> indicesData;

		std::vector<float> waterVertexData;
		std::vector<uint32_t> waterIndicesData;

		std::vector<std::vector<std::vector<uint8_t>>> blockMeshData;

		VertexArray va;
		VertexBuffer vb;
		IndexBuffer ib;
		Texture texture;
		Shader chunkShader;

		VertexArray waterVao;
		VertexBuffer waterVb;
		IndexBuffer waterIb;
		Shader waterShader;

		static const int CHUNK_WIDTH  = 16;
		static const int CHUNK_DEPTH  = 16;
		static const int CHUNK_HEIGHT = 128;

		int centx;
		int centz;
		Vec2 center;
		float pythaDis;
		int seed;

	};
}
