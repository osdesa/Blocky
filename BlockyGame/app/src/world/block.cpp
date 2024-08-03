#include "world/block.h"
#include "world/block_types.hpp"
#include <logger.h>
#include "world/NoiseGenerator.h"

namespace Blocky {
	Block::Block(uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT], BlockData& blockTexCoords,
		float offsetX, float offsetZ, float offsetY, std::map<Vec2, int>& hightMap, FastNoiseLite noise)
		: x(offsetX), y(offsetY), z(offsetZ), facesPlaced(0), texCoords(blockTexCoords), heights(hightMap), lNoise(noise)
	{
		// Gets the posistion within the chunk as every chunk is 16  by 16 in the x and y axis
		int localZ = abs(z) % 16;
		int localX = abs(x) % 16;

		// if the block is water
		if (Blocks_data[localX][localZ][y] == BlockTypes::Water) {
			// if the block above is not water
			if (Blocks_data[localX][localZ][y + 1] != BlockTypes::Water)
			{
				AddFace(waterTopFace, FaceId::top);
			}
		}
		else
		{
			// trys to add the faces to the left and right of the center
			AddZFacePos(localX, localZ, Blocks_data);
			// trys to add the faces to the front and back of the center
			AddXFacePos(localX, localZ, Blocks_data);

			// if the block is bellow the max height
			if (y < 127) {
				// if the block to the above is transprent
				if (Blocks_data[localX][localZ][y + 1] == BlockTypes::Air || Blocks_data[localX][localZ][y + 1] == BlockTypes::Water)
					AddFace(topFace, FaceId::top);
			}
			// if the block is above the min y level
			if (y > 0) {
				// if the block bellow is transpernt
				if (Blocks_data[localX][localZ][y - 1] == BlockTypes::Air || Blocks_data[localX][localZ][y - 1] == BlockTypes::Water)
					AddFace(bottomFace, FaceId::bottom);
			}

		}

	}

	void Block::AddZFacePos(int localX, int localZ, uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT])
	{
		// if the block is not on the edge to the right
		if (localZ < 15) {
			// if the block to its right is transprent
			if (Blocks_data[localX][localZ + 1][y] == BlockTypes::Air || Blocks_data[localX][localZ + 1][y] == BlockTypes::Water)
				AddFace(frontFace, FaceId::front);
		}
		else {
			TryAddFaceOutsideChunk(x, z + 1, frontFace, FaceId::front);
		}
		// if the block is not on the left most edge of the chunk
		if (localZ > 0) {
			// if the block to its left is a transprent block
			if (Blocks_data[localX][localZ - 1][y] == BlockTypes::Air || Blocks_data[localX][localZ - 1][y] == BlockTypes::Water)
				AddFace(backFace, FaceId::back);
		}
		else {
			TryAddFaceOutsideChunk(x, z - 1, backFace, FaceId::back);
		}
	}

	void Block::AddXFacePos(int localX, int localZ, uint32_t Blocks_data[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT])
	{
		// if the block to its left is inside its own chunk
		if (localX < 15) {
			// if the block to the left is transprent
			if (Blocks_data[localX + 1][localZ][y] == BlockTypes::Air || Blocks_data[localX + 1][localZ][y] == BlockTypes::Water)
				AddFace(leftFace, FaceId::left);
		}
		else {
			TryAddFaceOutsideChunk(x + 1, z, leftFace, FaceId::left);
		}
		// if the block to the left is inside the current chunk
		if (localX > 0) {
			// if the block is non transprent
			if (Blocks_data[localX - 1][localZ][y] == BlockTypes::Air || Blocks_data[localX - 1][localZ][y] == BlockTypes::Water)
				AddFace(rightFace, FaceId::right);
		}
		else {
			TryAddFaceOutsideChunk(x - 1, z, rightFace, FaceId::right);
		}
	}

	void Block::TryAddFaceOutsideChunk(int xPos, int zPos, float faces[20], FaceId id)
	{
		// Gets the max height of the block coloum provided
		int maxHeight = GetHeight(xPos, zPos);
		// if the max height is less than the current blocks y then add the provided face=
		if (maxHeight < y)
			AddFace(faces, id);
	}

	int Block::GetHeight(int x, int y)
	{
		return NoiseGen::GetHeight(x, y, lNoise, heights);
	}

	void Block::AddFace(float faces[20], FaceId face)
	{
		textureIndex = 0;
		for (int count = 0; count < 20; count++) {
			// Vertex posistion
			// adds the x pos
			if (count % 5 == 0)
				vetexData.push_back(faces[count] + x);
			else if (count % 5 == 1)
				vetexData.push_back(faces[count] + y); // adds the y coordinate
			else if (count % 5 == 2) {
				vetexData.push_back(faces[count] + z); // adds the z value
			}
			// Texture coorinates
			else
				AddTextureFace(face);	// adds the texture positstions
		}

		for (uint32_t index : indexs) {
			// adds the indices by using the basic 0,1,2,2,3,0 and then adds on the number of faces to make it unique
			indices.push_back(index + (facesPlaced * 4)); 
		}
		facesPlaced++;
	}

	void Block::AddTextureFace(FaceId face)
	{
		// goes through the face and adds the correct texture coordinates based on where the face is
		switch (face)
		{
		case FaceId::top:
			vetexData.push_back(texCoords.topFace[textureIndex]);
			break;
		case FaceId::front:
			vetexData.push_back(texCoords.front[textureIndex]);
			break;
		case FaceId::back:
			vetexData.push_back(texCoords.back[textureIndex]);
			break;
		case FaceId::right:
			vetexData.push_back(texCoords.right[textureIndex]);
			break;
		case FaceId::left:
			vetexData.push_back(texCoords.left[textureIndex]);
			break;
		case FaceId::bottom:
			vetexData.push_back(texCoords.bottomFace[textureIndex]);
			break;
		default:
			Logger::output(WARNING, "Failed to find valid texture face");
			break;
		}
		textureIndex++;
	}
}