#include "world/chunk.h"
#include "world/block.h"
#include "logger.h"
#include "world/NoiseGenerator.h"
#include "world/block_types.hpp"
#include "graphics/VertexBuffer.h"
#include <graphics/Texture.h>

namespace Blocky {

	Chunk::~Chunk()
	{
	}
 
	void Chunk::Shape(VertexArray& vao, VertexArray& waterVa, 
		Shader& shader, Shader& WaterShader, int centerX, int centerZ, FastNoiseLite noise, std::map<Vec2, int>& hightMap,
		int hash)
	{
		// sets up the basic variables
		centx = centerX; centz = centerZ; 
		va = std::move(vao); waterVao = std::move(waterVa);
		chunkShader = std::move(shader);  waterShader = std::move(WaterShader);

		// makes the center be in the mid point of the chunk
		center = Vec2(centx+8, centz+8);

		// removes any data left in the vectors
		// mostly just in case should not matter
		vertexData.clear();
		indicesData.clear();

		waterVertexData.clear();
		waterIndicesData.clear();

		// the chunks must have coordinates which are mmultiples of 16 as the chunks are 16 x 16 x 128
		if ((centx % 16 != 0) || (centz % 16 != 0)) {
			Logger::output(FATAL, "Can not create chunk with x and z coordinate of multipule of 16");
		}

		// makes the blockmeshdata vector the correct size and makes every block air
		blockMeshData.resize(16, std::vector<std::vector<uint8_t> >(16, std::vector<uint8_t>(128, BlockTypes::Air)));

		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				// gets the max height of a given coloumn
				int maxHeight = NoiseGen::GetHeight(x + centx, z + centz, noise, hightMap);
				// checks if the highest block should be the noise generated block or if it should be the water level
				int height = maxHeight > WATERLEVEL ? maxHeight : WATERLEVEL;
				for (int y = 0; y <= height; y++) {
					// the settings for what block should be placed in which spot
					if (y == maxHeight)
						blockMeshData[x][z][y] = BlockTypes::Grass;
					else if (y < maxHeight && y > maxHeight - 3)
						blockMeshData[x][z][y] = BlockTypes::Dirt;
					else if (y <= maxHeight - 3 && y > 2)
						blockMeshData[x][z][y] = BlockTypes::Stone;
					else if (y <= 2)
						blockMeshData[x][z][y] = BlockTypes::Bedrock;
					else if (y <= WATERLEVEL) 
						blockMeshData[x][z][y] = BlockTypes::Water;
					else
						blockMeshData[x][z][y] = BlockTypes::Air;
				}
			}
		}
	}

	void Chunk::GenerateMesh(std::unordered_map<uint32_t, BlockData>& texLoc, std::map<Vec2, int>& hightMap, FastNoiseLite noise)
	{
		// creates a 3D array to use for generation as the speed up is around 100x from using the vector
		uint32_t Blocks[CHUNK_WIDTH][CHUNK_DEPTH][CHUNK_HEIGHT] = {};
		for (size_t x = 0; x < 16; x++) {
		for (size_t z = 0; z < 16; z++) {
		for (size_t y = 0; y < 128; y++){
			Blocks[x][z][y] = blockMeshData[x][z][y];
		}
		}
		}

		// handy variables mostly used for debuging and minor optimistions
		int facesMeshed = 0;
		int waterFacesMeshed = 0;
		// loops through the world
		for (int x = 0; x < 16; x++) {
			for (int z = 0; z < 16; z++) {
				for (int y = 0; y < 128; y++) {
					// if the current block is not air
					if (Blocks[x][z][y] != BlockTypes::Air) {
						// gets the current block texture
						BlockData blockTexCoords = texLoc[Blocks[x][z][y]];
						// creates the block with given parameters
						Block block(Blocks, blockTexCoords, x + centx, z + centz, y, hightMap, noise);
						// if the current block is not water
						if (Blocks[x][z][y] != BlockTypes::Water)
						{
							// adds blocks vertex data to the chunks vertex data
							for (auto vertex : block.GetVertexData())
								vertexData.push_back(vertex);
							// adds the blocks indices data to the chunks indices dat
							for (auto indice : block.GetIndices()) {
								// adds the indice and accounts for how many faces have already been added
								indicesData.push_back(indice + (facesMeshed * 4));
							}
							facesMeshed += block.GetFaces();
						}
						else {

							// adds blocks vertex data to the chunks vertex data
							for (auto vertex : block.GetVertexData())
								waterVertexData.push_back(vertex);
							for (auto indice : block.GetIndices()) {
								// adds the indice and accounts for how many faces have already been added
								waterIndicesData.push_back(indice + (waterFacesMeshed * 4));
							}
							waterFacesMeshed += block.GetFaces();
						}
					}
				}
			}
		}
		// binds the vao for solid blocks
		va.Bind();
		// creates the vertex buffer with the vertex data
		vb.Create(vertexData.data(), vertexData.size() * sizeof(float));
		// creates the index buffer with the indices of the chunk
		ib.Create(indicesData.data(), indicesData.size());

		// frees up the no longer used memory
		vertexData.clear();
		indicesData.clear();

		// tells the gpu to read the data as a vec3 and vec2 with normilised floats
		VBLayout layout{};
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		// adds the vertex buffer and layout to the vao
		va.AddBuffer(vb, layout);

		// creates the shader for the solid blocks
		chunkShader.Create("app/res/shaders/vertex.glsl", "app/res/shaders/fragment.glsl");
		chunkShader.Bind();
		// creates the texture which will be used by both the solid blocks and water
		texture.Create("app/res/textures/SpriteSheet.png", GL_NEAREST);
		texture.Bind();

		// binds the water vertex array
		waterVao.Bind();
		// creates the water vertex buffer amd populates the buffer with the vertex data 
		waterVb.Create(waterVertexData.data(), waterVertexData.size() * sizeof(float));
		// creates the index buffer and populates the buffer with the indices
		waterIb.Create(waterIndicesData.data(), waterIndicesData.size());

		// tells adds the same layout as for solid blocks
		waterVao.AddBuffer(waterVb, layout);

		// creates the shader to be used by the water 
		waterShader.Create("app/res/shaders/waterVertex.glsl", "app/res/shaders/waterFrag.glsl");
		waterShader.Bind();
	}

	std::map<Vec3, uint32_t>& Chunk::GenerateDetails(std::unordered_map<uint32_t, BlockData>& texLoc, std::map<Vec2, int>& hightMap,
		FastNoiseLite noise, std::map<Vec3, uint32_t>& blocksToPlace)
	{
		// sets the random seed
		srand(seed + centx + centz);
		// loops through the chunk x and z
		for (int x = 0; x < CHUNK_WIDTH; x++) {
			for (int z = 0; z < CHUNK_DEPTH; z++) {
				// gets a random number between 0 and 999
				int rng = rand() % 1000;
				if (rng > 995) {
					// Generate tree at x,z and y
					int maxHeight = NoiseGen::GetHeight(x + centx, z + centz, noise, hightMap);
				
					BlockTypes type;
					// gives a 1 in 1000 chance to generte a birch tree
					if (rng > 998) type = BlockTypes::birch;
					else type = BlockTypes::oak;
					// block is not too close to the water to give more accurate looking tree generation
					if (maxHeight > WATERLEVEL + 2)
						PlaceTree(x, z, maxHeight, blocksToPlace, type);
				}
			}
		}
		return blocksToPlace;
	}

	std::map<Vec3, uint32_t>& Chunk::PlaceTree(int x, int z, int y, std::map<Vec3, uint32_t>& blocksToPlace, BlockTypes type)
	{
		// places the basic stump of the tree with 5 blocks of tree log and 2 leaves above them
		blockMeshData[x][z][y + 1] = type;
		blockMeshData[x][z][y + 2] = type;
		blockMeshData[x][z][y + 3] = type;
		blockMeshData[x][z][y + 4] = type;
		blockMeshData[x][z][y + 5] = type;
		blockMeshData[x][z][y + 6] = BlockTypes::leaf;
		blockMeshData[x][z][y + 7] = BlockTypes::leaf;
		// gets the x and z of the block in world space instead of chunk space
		float vX = x + centx;
		float vY = (float)y;
		float vZ = z + centz;

		// sets the block to the left of the tree to be leafs
		blocksToPlace[{vX - 2, vY + 5, vZ}] = BlockTypes::leaf;
		blocksToPlace[{vX - 1, vY + 5, vZ}] = BlockTypes::leaf;
		blocksToPlace[{vX - 1, vY + 6, vZ}] = BlockTypes::leaf;

		// sets the blocks to the right of the tree to be leafs
		blocksToPlace[{vX + 2, vY + 5, vZ}] = BlockTypes::leaf;
		blocksToPlace[{vX + 1, vY + 5, vZ}] = BlockTypes::leaf;
		blocksToPlace[{vX + 1, vY + 6, vZ}] = BlockTypes::leaf;

		// sets the blocks to the back of the tree to be leafs
		blocksToPlace[{vX, vY + 5, vZ - 2}] = BlockTypes::leaf;
		blocksToPlace[{vX, vY + 5, vZ - 1}] = BlockTypes::leaf;
		blocksToPlace[{vX, vY + 6, vZ - 1}] = BlockTypes::leaf;

		// sets the blocks to the front of the tree to be leafs
		blocksToPlace[{vX, vY + 5, vZ + 2}] = BlockTypes::leaf;
		blocksToPlace[{vX, vY + 5, vZ + 1}] = BlockTypes::leaf;
		blocksToPlace[{vX, vY + 6, vZ + 1}] = BlockTypes::leaf;

		// sets the blocks in the corners to be leafs
		blocksToPlace[{vX + 1, vY + 5, vZ + 1}] = BlockTypes::leaf;
		blocksToPlace[{vX + 1, vY + 5, vZ - 1}] = BlockTypes::leaf;
		blocksToPlace[{vX - 1, vY + 5, vZ + 1}] = BlockTypes::leaf;
		blocksToPlace[{vX - 1, vY + 5, vZ - 1}] = BlockTypes::leaf;

		return blocksToPlace;
	}

	void Chunk::SetBlock(int x, int y, int z, uint32_t blockType)
	{
		blockMeshData[x][z][y] = blockType;
	}

	void Chunk::Draw(Camera& camera, bool underWater, float lightValue)
	{
		// binds the texture and shader
		texture.Bind();
		chunkShader.Bind();
		// sends the matrixs to the gpu
		chunkShader.SetMatrix4("u_Model", camera.GetModel());
		chunkShader.SetMatrix4("u_Projection", camera.GetProjection());
		chunkShader.SetMatrix4("u_View", camera.GetView());
		// sets the texture to be the basic texture
		chunkShader.SetUniform1i("uTexture", 0);
		// sets the lighting value to be the given float
		chunkShader.SetUniform1f("lighting", lightValue);

		// if the player is underwater than change screen to have a blue tint
		if(underWater)
			chunkShader.SetUniform1f("waterEffect", 0.85);
		else
			chunkShader.SetUniform1f("waterEffect", 1);

		// draws all the trinagles to the screen for solid blocks
		DrawElements(va, ib, chunkShader);

		// if there is water in the chunk
		if (waterIb.GetCount() > 0) {
			// binds the shader
			waterShader.Bind();
			// sends the matrixs to the gpu
			waterShader.SetMatrix4("u_Model", camera.GetModel());
			waterShader.SetMatrix4("u_Projection", camera.GetProjection());
			waterShader.SetMatrix4("u_View", camera.GetView());
			// sets the texture to be the base texture
			waterShader.SetUniform1i("uTexture", 0);
			// sets the lighting to be the given value
			waterShader.SetUniform1f("lighting", lightValue);
			// draws all the water traingles to the screen
			DrawElements(waterVao, waterIb, waterShader);
		}
	}

	void Chunk::SetDistance(Vec3& playerPos)
	{
		// calulates the pythagoren distance in the x and y axis with no cosideration of y
		pythaDis = ((playerPos.x - center.x) * ((playerPos.x - center.x))) + ((playerPos.z - center.y) * ((playerPos.z - center.y)));
	}
}
