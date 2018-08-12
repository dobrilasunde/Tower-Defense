#include "Grid.hpp"
#include "Tile.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include<algorithm>

Grid::Grid(class Game* game) : Actor(game), mSelectedTile(nullptr)
{
	//resize the 2d vector to fit the exact number of rows and columns (7 rows and 16 columns)
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); ++i)
	{
		mTiles[i].resize(NumCols);
	}

	//create tile grid
	for (size_t i = 0; i < NumRows; ++i)
	{
		for (size_t j = 0; j < NumCols; ++j)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize / 2.0f + j * TileSize, StartY + i * TileSize));
		}
	}

	//set start and end tiles
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);

	//adding adjacent tiles to the vector
	for (size_t i = 0; i < NumRows; ++i)
	{
		for (size_t j = 0; j < NumCols; ++j)
		{
			if (i > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
			}
			if (i < NumRows - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
			}
			if (j > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
			}
			if (j < NumCols - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
			}
		}
	}

	//reverse so we dont have to backtrack to find the path for the enemy
	FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());

	mNextEnemy = EnemyTime;
}

void Grid::SelectTile(size_t row, size_t col)
{
	Tile::TileState tstate = mTiles[row][col]->GetTileState();

	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}

		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

void Grid::ProcessClick(int x, int y)
{
	y -= static_cast<int>(StartY - TileSize / 2);
	if (y >= 0)
	{
		x /= static_cast<int>(TileSize);
		y /= static_cast<int>(TileSize);
		if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
		{
			SelectTile(y, x);
		}
	}
}

//A* search algorithm
bool Grid::FindPath(Tile* start, Tile* goal)
{
	for (size_t i = 0; i < NumRows; ++i)
	{
		for (size_t j = 0; j < NumCols; ++j)
		{
			mTiles[i][j]->g = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}

	std::vector<Tile*> openSet;

	Tile* current = start;
	current->mInClosedSet = true;

	do
	{
		for (Tile* neighbour : current->mAdjacent)
		{
			if (neighbour->mBlocked)
			{
				continue;
			}

			if (!neighbour->mInClosedSet)
			{
				if (!neighbour->mInOpenSet)
				{
					neighbour->mParent = current;
					//h(x) is the euclidean distance between the current and goal node
					neighbour->h = (neighbour->GetPosition() - goal->GetPosition()).Length();
					//g(x) is the parent's g + cost of traversing the edge in the tree (actual path cost)
					neighbour->g = current->g + TileSize;
					neighbour->f = neighbour->h + neighbour->g;
					openSet.emplace_back(neighbour);
					neighbour->mInOpenSet = true;
				}
				else
				{
					//compute g(x) cost if current becomes the parent
					float newG = current->g + TileSize;
					if (newG < neighbour->g)
					{
						//adopt this node
						neighbour->mParent = current;
						neighbour->g = newG;
						neighbour->f = neighbour->g + neighbour->h;
					}
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(), [](Tile* a, Tile* b) { return a->f < b->f; });

		current = *iter;
		openSet.erase(iter);
		current->mInOpenSet = false;
		current->mInClosedSet = true;
	} while (current != goal);

	return (current == goal) ? true : false;
}

void Grid::UpdatePathTiles(class Tile* start)
{
	for (size_t i = 0; i < NumRows; ++i)
	{
		for (size_t j = 0; j < NumCols; ++j)
		{
			if (!(i == 3 && j == 0) && !(i == 3 && j == 15))
			{
				mTiles[i][j]->SetTileState(Tile::EDefault);
			}
		}
	}

	
	Tile* t = start->mParent;
	while (t != GetEndTile())
	{
		t->SetTileState(Tile::EPath);
		t = t->mParent;
	}
}

void Grid::BuildTower()
{
	if (mSelectedTile && !mSelectedTile->mBlocked)
	{
		mSelectedTile->mBlocked = true;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			Tower* t = new Tower(GetGame());
			t->SetPosition(mSelectedTile->GetPosition());
		}
		else
		{
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		UpdatePathTiles(GetStartTile());
	}
}

Tile* Grid::GetStartTile()
{
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mNextEnemy -= deltaTime;
	if (mNextEnemy <= 0.0f)
	{
		new Enemy(GetGame());
		mNextEnemy += EnemyTime;
	}
}