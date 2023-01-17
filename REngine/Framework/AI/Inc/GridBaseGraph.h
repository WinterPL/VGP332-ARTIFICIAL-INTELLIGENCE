#pragma once

namespace AI
{
	class GridBaseGraph {
	public:
		enum Directions {
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
			
			//search 
			Node* parent = nullptr;
			bool opened = false;
			bool closed= false;
		};
		void initialize(int columns, int rows);
		void ResetSearchParameter();


		Node* GetNode(int x, int y);
		const Node* GetNode(int x, int y)const;

		int GetColumns()const;
		int GetRows()const;

	private:
		int GetIndex(int x, int y) const;

		std::vector<Node> mNodes;
		//std::vector<std::vector<Node>> mNodes;
		int mColumns = 0;
		int mRows = 0;

	};
}