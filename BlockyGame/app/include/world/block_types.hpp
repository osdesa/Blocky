#pragma once

#include "math/BMath.h"
#include <unordered_map>
#include <iostream>
#include <array>

namespace Blocky {

	const float textureSize = 256.0f;
	const float spriteSize = 32.0f;

	enum BlockTypes {
		Air = 0,
		Stone = 1,
		Bedrock = 2,
		Grass = 3,
		Dirt = 4,
		Water = 5,
		oak = 6,
		leaf = 7,
		birch = 8
	};

	struct BlockData {
		std::array<float, 8> topFace;
		std::array<float, 8> front;
		std::array<float, 8> back;
		std::array<float, 8> right;
		std::array<float, 8> left;
		std::array<float, 8> bottomFace;

		bool operator() (BlockData* v1, BlockData* v2) const
		{
			return
				v1->topFace == v2->topFace &&
				v1->front == v2->front &&
				v1->back == v2->back;
			v1->right == v2->right &&
				v1->bottomFace == v2->bottomFace &&
				v1->left == v2->left;
		}
	};

	static std::array<float, 8> GetTextureCoord(int x, int y)
	{
		return {
			(x * spriteSize) / textureSize,
			(y * spriteSize) / textureSize,
			 ((x + 1) * spriteSize) / textureSize ,
			(y * spriteSize) / textureSize,
			 ((x + 1) * spriteSize) / textureSize ,
			((y + 1) * spriteSize) / textureSize,
			 (x * spriteSize) / textureSize ,
			((y + 1) * spriteSize) / textureSize
		};
	}

	/// <summary>
	/// Fixes texture coordinates for front,right and left faces takes in values as ref
	/// </summary>
	/// <param name="frontFace"></param>
	/// <param name="rigthFace"></param>
	/// <param name="leftFace"></param>
	/// <param name="correctFace"></param>
	static void CorrectFaces(std::array<float, 8>& frontFace, std::array<float, 8>& rigthFace,
		std::array<float, 8>& leftFace, std::array<float, 8>& correctFace)
	{
		auto zerox = correctFace[0];
		auto xeroy = correctFace[1];
		auto onex = correctFace[2];
		auto oney = correctFace[3];
		auto twox = correctFace[4];
		auto twoy = correctFace[5];
		auto threex = correctFace[6];
		auto threey = correctFace[7];

		frontFace = { twox, twoy , threex, threey, zerox, xeroy, onex, oney };
		rigthFace = frontFace;
		leftFace = { threex, threey, zerox, xeroy, onex, oney, twox, twoy };
	}

	/// <summary>
	/// Creates hash map off all blocks and there face texture location 
	/// </summary>
	/// <returns></returns>
	static std::unordered_map<uint32_t, BlockData> CreateTextureCache()
	{
		std::unordered_map<uint32_t, BlockData> cache;
		std::array<float, 8> topFace = { 0 };
		std::array<float, 8> frontFace = { 0 };
		std::array<float, 8> backFace = { 0 };
		std::array<float, 8> rightFace = { 0 };
		std::array<float, 8> leftFace = { 0 };
		std::array<float, 8> bottomFace = { 0 };

		cache[BlockTypes::Air] = { topFace, topFace, topFace, topFace, topFace, topFace };

		// Stone Block
		topFace = GetTextureCoord(0, 7);
		backFace = GetTextureCoord(0, 7);
		bottomFace = GetTextureCoord(0, 7);
		CorrectFaces(frontFace, rightFace, leftFace, backFace);
		cache[BlockTypes::Stone] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// Dirt Block
		topFace = GetTextureCoord(1, 7);
		backFace = GetTextureCoord(1, 7);
		bottomFace = GetTextureCoord(1, 7);
		CorrectFaces(frontFace, rightFace, leftFace, backFace);
		cache[BlockTypes::Dirt] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// Grass
		bottomFace = GetTextureCoord(1, 7);
		backFace = GetTextureCoord(2, 7);
		topFace = GetTextureCoord(3, 7);

		CorrectFaces(frontFace, rightFace, leftFace, backFace);

		cache[BlockTypes::Grass] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// Bedrock Block
		bottomFace = GetTextureCoord(4, 7);
		backFace = GetTextureCoord(4, 7);
		topFace = GetTextureCoord(4, 7);

		CorrectFaces(frontFace, rightFace, leftFace, backFace);

		cache[BlockTypes::Bedrock] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// Water Block
		bottomFace = GetTextureCoord(5, 7);
		backFace = GetTextureCoord(5, 7);
		topFace = GetTextureCoord(5, 7);

		CorrectFaces(frontFace, rightFace, leftFace, backFace);

		cache[BlockTypes::Water] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// oak log
		bottomFace = GetTextureCoord(7, 7);
		backFace = GetTextureCoord(6, 7);
		topFace = GetTextureCoord(7, 7);

		CorrectFaces(frontFace, rightFace, leftFace, backFace);
		cache[BlockTypes::oak] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		// leaf 
		bottomFace = GetTextureCoord(0, 6);
		cache[BlockTypes::leaf] = { bottomFace, bottomFace, bottomFace, bottomFace, bottomFace, bottomFace };

		// birch log
		bottomFace = GetTextureCoord(2, 6);
		backFace = GetTextureCoord(1, 6);
		topFace = GetTextureCoord(2, 6);

		CorrectFaces(frontFace, rightFace, leftFace, backFace);
		cache[BlockTypes::birch] = { topFace, frontFace, backFace, frontFace, leftFace, bottomFace };

		return cache;
	}
}