#include "world/world.h"
#include "external/FastNoiseLite.h"
#include "core/utils.h"
#include <thread>
#include <algorithm>
#include "core/GameState.h"

namespace Blocky{
	// inits the variables and creates the texture cachce
	World::World()
		: textureLocs(CreateTextureCache()), underWater(false), sunRotation(0)
	{
	}

	void World::CreateWorld(Camera& camera)
	{
		// if the user has not enterd a seed generate a random seed
		if (GameState::seed.empty()) GameState::seed = GenRandomSeed();

		// display the basic infomation of the world generation
		Logger::output(KEYINFO, "Creating new world Seed: %s : %d : size %d: ",
			GameState::seed.c_str(), hashWorldSeed(GameState::seed.c_str()), GameState::worldSize);

		// sets the random seed to the 
		srand(hashWorldSeed(GameState::seed.c_str()));

		// makes all the vectors the correct size as otherwise the gates of hell open and randomness can seep through
		chunks.resize(GameState::worldSize);
		left.resize(GameState::worldSize);
		right.resize(GameState::worldSize);

		// creates the sun and the moon
		sun.Create(camera);
		moon.Create(camera);

		// sets the noise settings 
		noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
		noise.SetSeed(hashWorldSeed(GameState::seed.c_str()));
		noise.SetFractalType(FastNoiseLite::FractalType_FBm);
		noise.SetFractalOctaves(9);

		// gets the postition of the camera and sets up some basic varaibles
		Vec3 posistion = camera.GetPosition();
		int index = 0;
		uint32_t xPos = (int)posistion.x;
		uint32_t zPos = (int)posistion.z;

		// loops through all the chunks
		for (size_t x = xPos - (GameState::chunkSize * 8); x < xPos + (GameState::chunkSize * 8); x += 16)
		{
			for (size_t z = zPos - (GameState::chunkSize * 8); z < zPos + (GameState::chunkSize * 8); z += 16)
			{
				// gets the location
				Vec2 location = Vec2(x, z);
				// sets up the vertex solid blocks array and water blocks array
				va.Create();
				waterva.Create();
				// creates the basic landscape of the terrain and the block types
				chunk.Shape(va, waterva, shader, waterShader, x, z, noise, hightMap, hashWorldSeed(GameState::seed.c_str()));
				// sets the distance of the chunk from the player
				chunk.SetDistance(posistion);
				// moves the chunk into the storage of chunks
				chunks[index] = std::move(chunk);
				index++;
			}
		}

		for (index = 0; index < GameState::worldSize; index++) {
			// generates trees
			blocksToPlace = chunks[index].GenerateDetails(textureLocs, hightMap, noise, blocksToPlace);

			// if there is a tree block
			if (blocksToPlace.size() > 1) {
				// place the needed blocks
				PlaceBlocks(blocksToPlace);
			}
			blocksToPlace.clear();
		}

		// Generate Mesh
		for (index = 0; index < GameState::worldSize; index++)
		{
			// generates the actual visable parts includeing the textures
			chunks[index].GenerateMesh(textureLocs, hightMap, noise);
		}
		// sorts the chunks based on their distance from the player
		mergeSort(chunks, 0, GameState::worldSize - 1);
		Logger::output(KEYINFO, "world generated");
	}

	int World::hashWorldSeed(const char* seed)
	{
		int hash = 0;
		// simlpe style has shich works by looping through the whole string
		for (int i = 0; seed[i] != '\0'; i++) {
			// adds the char value to the hash value
			hash += (char)seed[i];
		}
		return hash;
	}

	bool World::CheckCollide(AABB aabb)
	{
		// find the nearest blocks to the camera
		Vec3 pos = aabb.GetMin();

		// use linear search to find which chunk the aabb is in as chunks are sorted should 
		// always be one of the first for the camera
		int chunkIndex = inChunk(pos);
		// Check the 27 blocks around the player

		// checks if the player is currently under water
		if (chunks[chunkIndex].GetBlock((int)pos.x % 16, pos.y, (int)pos.z % 16) == BlockTypes::Water)
			underWater = true;
		else
			underWater = false;

		// loops around the player in a 3x3x3 grid 

		for (int x = -1; x <= 1; x++) {
			int xPos = ceil(pos.x) + x;
			for (int z = -1; z <= 1; z++) {
				int zPos = ceil(pos.z) + z;
				for (int y = -1; y <= 1; y++) {
					// gets the current posistion of the block
					int yPos = ceil(pos.y) + y;
					Vec3 blockPos = { (float)xPos, (float)yPos, (float)zPos };

					// gets which block is at this postistion
					uint8_t block = chunks[chunkIndex].GetBlock(xPos % 16, yPos, zPos % 16);
					// if the block is solid
					if (!((block == BlockTypes::Air) || (block == BlockTypes::Water))) {
						// creates the collider of the block
						AABB block;
						block.Update(blockPos, blockPos + 1);
						// checks if the player is inside the currently being check
						bool colide = AABB::collide(aabb, block);
						if (colide)
							return true;
					}
				}
			}
		}
		return false;
	}

	int World::inChunk(Vec3 pos)
	{
		// seachs from the back as the current chunk should be the last one
		int chunkIndex = GameState::worldSize;
		for (chunkIndex > 0; chunkIndex--;) {
			Vec2 center = chunks[chunkIndex].GetCenter();
			// checks if the player is inside the chunk
			if ((pos.x >= center.x - 8) && (pos.x <= center.x + 8)) {
				if ((pos.z >= center.y - 8) && (pos.z <= center.y + 8)) {
					return chunkIndex;
				}
			}
		}
		return -1;
	}

	void World::PlaceBlocks(std::map<Vec3, uint32_t> blocks)
	{
		// loops through all the blocks that need to be placed
		for (const auto block : blocks) {
			// gets which chunk the player is in
			int chunkIndex = inChunk(block.first);

			// if the chunk exist
			if (chunkIndex != -1)
				chunks[chunkIndex].SetBlock((int)block.first.x % 16, (int)block.first.y, (int)block.first.z % 16, block.second);
			// the chunk is not loaded so store it for later use
			else {
				Logger::output(INFO, "Block for ungenerated chunk count : %d", blocksToPlaceCold.size());
				blocksToPlaceCold[block.first] = block.second;
			}
		}

	}

	std::string World::GenRandomSeed()
	{
		// sets the random seed
		srand(time(NULL));
		// generates random natural number
		uint32_t seed = floor(abs(rand()) * PI * 52313266);
		return std::to_string(seed);
	}

	void World::update(Camera& camera, Clock& clock)
	{
		// Generate pre planed chunks
		GeneratePrePlan();

		// Moves the player based upon inputs
		camera.Update(clock.DT());

		// checks if player is now colliding with the world
		bool colide = CheckCollide(camera.GetAABB());
		if (colide) {
			camera.ResetMove();
		}
		// gets the current posistion and upadtes the last pos
		playerPos = camera.GetPosition();
		Vec3 lastPos = camera.GetLastPosition();

		// gets the chunk location 
		Vec2 chunkLoc = Vec2(playerPos.x, playerPos.z);
		Vec2 chunkLastLoc = Vec2(lastPos.x, lastPos.z);
		if (playerPos == lastPos) return;
		// calulate distance from player
		for (Chunk& chunk : chunks) {
			chunk.SetDistance(playerPos);
		}
		// sort the chunks based on distance
		mergeSort(chunks, 0, GameState::worldSize - 1);

		if (GameState::infinte)
			InfiteWorldGen();
	}

	void World::InfiteWorldGen()
	{
		int chunksGenerated = 0;
		// loops through the world size
		for (int x = -GameState::chunkSize * 8; x < GameState::chunkSize * 8; x += 16) {
			for (int z = -GameState::chunkSize * 8; z < GameState::chunkSize * 8; z += 16) {
				// gets the current chunk location
				Vec3 location = Vec3(playerPos.x + x, 0, playerPos.z + z);
				// if the current chunk does not exist
				if (inChunk(location) == -1) {
					chunksGenerated++;
					// gets the nearest chunk x and z coordinates which is where the chunk should generate
					location.x = RoundPow2(location.x, 16) - 16;
					location.z = RoundPow2(location.z, 16) - 16;
					// calulates the distance int the x and z axis
					float dist = ((playerPos.x - location.x) * ((playerPos.x - location.x))) + ((playerPos.z - location.z) * ((playerPos.z - location.z)));
					// if this chunk is closer than the farest away chunk
					if (dist < chunks[0].GetDistance()) {
						// sets the distance of the farest chunk to be this chunks distance
						chunks[0].ForceSetDist(dist);
						// sets the new chunk to be generated
						chunksToGen[location] = true;
					}
				}
			}
		}
	}

	void World::GenerateChunk(Vec3& location)
	{
		// creates the vertex array for both solid and water blocks
		va.Create();
		waterva.Create();
		// shapes the chunk and creates the basic shape of the terrain
		chunk.Shape(va, waterva, shader, waterShader, location.x, location.z, noise, hightMap, hashWorldSeed(GameState::seed.c_str()));
		// sets the distance of the chunk
		chunk.SetDistance(playerPos);
		// moves this chunk into the chunk which has the greatest distance
		chunks[0] = std::move(chunk);

		// generates the trees
		blocksToPlace = chunks[0].GenerateDetails(textureLocs, hightMap, noise, blocksToPlace);
		if (blocksToPlace.size() > 1) {
			PlaceBlocks(blocksToPlace);
		}

		// Check for ungenerated blocks
		if (blocksToPlaceCold.size() > 1) {
			PlaceBlocks(blocksToPlaceCold);
		}

		// clears the blocks
		blocksToPlace.clear();
		// generates the mesh and then sorts them
		chunks[0].GenerateMesh(textureLocs, hightMap, noise);
		mergeSort(chunks, 0, GameState::worldSize - 1);
	}

	void World::GeneratePrePlan()
	{
		int chunksGenerated = 0;
		// loops through all the values in the dictionary
		for (auto& chunkCoord : chunksToGen) {
			// if the chunk should be generated
			if (chunkCoord.second == true) {
				// generates the chunk
				Vec3 temp = Vec3(chunkCoord.first.x, 0, chunkCoord.first.z);
				GenerateChunk(temp);
				chunksGenerated++;
				// set it so that it doesnt need to be generated
				chunksToGen[chunkCoord.first] = false;
				chunksToGen.erase(chunkCoord.first);
			}
			else {
				chunksToGen.erase(chunkCoord.first);
			}
			if (chunksGenerated >= maxChunksGenerated) break;

		}
	}

	int World::RoundPow2(int number, int factor)
	{
		// mathmatical method to round powers of 2 to there nearest factor
		// eg 17 -> 32
		// eg 16 -> 16
		return (number + factor - 1) & -factor;
	}

	void World::Draw(Camera& camera, Clock& clock)
	{
		// gets the suns rotation
		sunRotation = sun.GetRotation();
		// graphical translation of the cos graph for sun lighting
		float rotation = (cos(sunRotation) + 2.5) / 4;

		// loops through all the chunks and then draws them
		for (Chunk& chunk : chunks) {
			chunk.Draw(camera, underWater, rotation);
		}

		sun.Draw(camera, clock.DT());
		moon.Draw(camera, clock.DT());
	}

	void World::MergeComb(std::vector<Chunk>& arr, int start, int mid, int end)
	{
		// gets the left pointer 
		int leftP = mid - start + 1;
		// gets the right pointer
		int rightP = end - mid;

		// inits both the left and right vectors
		for (auto i = 0; i < leftP; i++)
			left[i] = std::move(arr[start + i]);
		for (auto j = 0; j < rightP; j++)
			right[j] = std::move(arr[mid + 1 + j]);

		int leftIndex = 0;
		int rightIndex = 0;
		int mergeIndex = start;

		// loops while values need to be inputed and both the left and right have values
		while (leftIndex < leftP && rightIndex < rightP) {
			// checks which chunk is closer
			if (left[leftIndex].GetDistance() > right[rightIndex].GetDistance()) {
				// if the left chunk is closer to the camera
				arr[mergeIndex] = std::move(left[leftIndex]);
				leftIndex++;
			}
			else {
				// if the right chunk is closer to the player
				arr[mergeIndex] = std::move(right[rightIndex]);
				rightIndex++;
			}
			mergeIndex++;
		}

		// while left values 
		while (leftIndex < leftP) {
			// moves over all of the left over values into the vector from the left
			arr[mergeIndex] = std::move(left[leftIndex]);
			leftIndex++;
			mergeIndex++;
		}
		// while right values
		while (rightIndex < rightP) {
			// moves over all the right values to the main vector from the right vector
			arr[mergeIndex] = std::move(right[rightIndex]);
			rightIndex++;
			mergeIndex++;
		}
	}

	void World::mergeSort(std::vector<Chunk>& arr, int start, int end)
	{
		// while not to split
		if (start >= end) return;

		// gets the midpoint of the 2 vectors
		int mid = (start)+(end - start) / 2;
		// sorts the left side of the vector
		mergeSort(arr, start, mid);
		// sorts the right side of the vector
		mergeSort(arr, mid + 1, end);
		// combines the vectors into one completing the merege sorts
		MergeComb(arr, start, mid, end);
	}
}