#pragma once

namespace AI
{
	class GridBaseGraph
	{
	public:
		enum Directions
		{
			North,
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		struct Node
		{
			std::array<Node*, 8> neighbors = {};
			int column = 0;
			int row = 0;

			//Search parameters for pathfinding
			Node* parent = nullptr;
			bool opened = false;

			//Dijkstra info
			float g = 0.0f;

			//A*
			float h = 0.0f;
		};

		void Initialize(int x, int y);
		void ResetSearchParameters();


		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y) const;

		int GetColumns() const;
		int GetRows() const;

	private:
		int GetIndex(int x, int y) const;

		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};
}