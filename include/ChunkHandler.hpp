#pragma once

#include "Chunk.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <thread>
#include <mutex>
#include "Player.hpp"
#include "Maths.hpp"
#include "MapGeneration.hpp"

class ChunkHandler
{
	public:
		ChunkHandler(bool is_seed, unsigned int seed);
		~ChunkHandler();
		void									MapHandler();
		void									LoadChunks();
		std::map<std::string, Chunk*>			enabledChunks;
	private:
		std::map<std::string, Chunk*>		disabledChunks;
		MapGeneration						*mapgen;
		Chunk								*GenerateChunk(int x, int y);
		void								GenerateChunks();
		void								AddChunkAtPos(int x, int y);
		bool								CheckIfChunkAtPos(int x, int y);
		void								DisableChunks();
		void								RemoveFarChunks();
		Chunk								*GetChunkAtPos(int x, int y);
		void								CheckNeigbors(Chunk *chunk);
		void								debugChunkHole();
		std::thread							*t;
};
