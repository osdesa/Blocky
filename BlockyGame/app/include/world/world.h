#pragma once


#include "logger.h"
#include "math/BMath.h"
#include "clock.h"
#include "graphics/VertexArray.h"
#include "graphics/shader.h"
#include <graphics/renderer.h>
#include "camera.h"
#include "world/block.h"
#include "world/chunk.h"
#include "core/aabb.h"
#include "world/block_types.hpp"

#include <map>
#include <array>
#include <cstdint>
#include <array>
#include "sky/moon.h"
#include "sky/sun.h"
#include <set>

namespace Blocky {
	class World
	{
	public:
		World();
		void CreateWorld(Camera& camera);
		void Draw(Camera& camera, Clock& clock);
		void update(Camera& camera, Clock& clock);
		std::vector<Chunk> chunks;
		inline double GetRotation() { return sunRotation; }

	private:
		int hashWorldSeed(const char* seed);
		bool CheckCollide(AABB aabb);
		int inChunk(Vec3 pos);
		void PlaceBlocks(std::map<Vec3, uint32_t> blocks);
		void InfiteWorldGen();
		void GenerateChunk(Vec3& location);
		void GeneratePrePlan();
		int RoundPow2(int number, int factor);

		std::string GenRandomSeed();
		std::vector<Chunk> left;
		std::vector<Chunk> right;
		std::unordered_map<uint32_t, BlockData> textureLocs;
		std::map<Vec3, bool> chunksToGen;
		std::map<Vec3, uint32_t> blocksToPlace;
		std::map<Vec3, uint32_t> blocksToPlaceCold;
		std::map<Vec2, int> hightMap;
		FastNoiseLite noise;

		int maxChunksGenerated = 2;
		bool underWater;
		float sunRotation;

		Sun sun;
		Moon moon;
		Vec3 playerPos;

		Chunk chunk;
		VertexArray va;
		VertexArray waterva;

		Shader shader;
		Shader waterShader;

		std::vector<std::string> faces
		{
			"sides.png",
			"sides.png",
			"top.png",
			"base.png",
			"sides.png",
			"sides.png"
		};

		void MergeComb(std::vector<Chunk>& arr, int start, int mid, int end);
		void mergeSort(std::vector<Chunk>& arr, int start, int end);
	};
}