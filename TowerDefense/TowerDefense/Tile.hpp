#pragma once
#include "Actor.hpp"
#include <vector>

class Tile : public Actor
{
public:
	enum TileState
	{
		EDefault,
		EPath,
		EStart,
		EBase
	};

	Tile(class Game* game);
	void SetTileState(TileState state);
	TileState GetTileState() const { return mTileState; }
	void ToggleSelect();
	const Tile* GetParent() const { return mParent; }

private:
	TileState mTileState;
	void UpdateTexture();
	class SpriteComponent* mSprite;
	bool mSelected;
	
	Tile* mParent;
	std::vector<Tile*> mAdjacent;
	float f;
	float g;
	float h;
	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;
};
