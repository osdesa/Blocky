#pragma once
#include <cstdint>
#include "math/BMath.h"
#include <vector>
#include "block_types.hpp"
#include "chunk.h"
#include "external/FastNoiseLite.h"

namespace Blocky {


	enum FaceId {
		top = 0,
		front = 1,
		back = 2,
		left = 3,
		right = 4,
		bottom = 5,
	};

	class Block
	{
	private:
		int x;
		int y;
		int z;

		static const int CHUNK_WIDTH = 16;
		static const int CHUNK_DEPTH = 16;
		static const int CHUNK_HEIGHT = 128;

		int facesPlaced;
		int textureIndex;

		std::vector<float> vetexData;
		std::vector<uint32_t> indices;

		void AddFace(float faces[20], FaceId face);
		void AddTextureFace(FaceId face);

		void AddZFacePos(int localX, int localZ, uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT]);
		void AddXFacePos(int localX, int localZ, uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT]);
		void TryAddFaceOutsideChunk(int xPos, int zPos, float faces[20], FaceId id);

		int GetHeight(int x, int y);

		std::map<Vec2, int>& heights;
		FastNoiseLite lNoise;

	public:
		Block(uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT], BlockData& blockTexCoords
			, float offsetX, float offsetY, float offsetZ, std::map<Vec2, int>& hightMap, FastNoiseLite noise);

		int GetFaces() { return facesPlaced; }

		std::vector<float> GetVertexData() { return vetexData; }
		std::vector<uint32_t> GetIndices() { return indices; }

		BlockData& texCoords;

	private:
		float frontFace[20] = {
			1,1,1,1,1,
			0,1,1,1,0,
			0,0,1,0,0,
			1,0,1,0,1,
		};

		float backFace[20] = {
			1,0,0,1,1,
			0,0,0,1,0,
			0,1,0,0,0,
			1,1,0,0,1,
		};

		float topFace[20] = {
			1,1,1,1,1,
			1,1,0,0,1,
			0,1,0,0,0,
			0,1,1,0,1,
		};


		float waterTopFace[20] = {
			1,0.7,1,1,1,
			1,0.7,0,0,1,
			0,0.7,0,0,0,
			0,0.7,1,0,1,
		};

		float bottomFace[20] = {
			1,0,1,1,1,
			0,0,1,0,1,
			0,0,0,0,0,
			1,0,0,0,1,
		};

		float rightFace[20] = {
			0,1,1,1,1,
			0,1,0,0,1,
			0,0,0,0,0,
			0,0,1,0,1,
		};

		float leftFace[20] = {
			1,1,1,1,1,
			1,0,1,0,1,
			1,0,0,0,0,
			1,1,0,0,1,
		};

		uint32_t indexs[6] = {
			0,1,2,2,3,0
		};

	};
}