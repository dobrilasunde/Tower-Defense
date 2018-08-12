#include"Tile.hpp"
#include"Game.hpp"
#include"SpriteComponent.hpp"

Tile::Tile(Game* game) : Actor(game), mParent(nullptr), f(0.0f), g(0.0f), h(0.0f), mBlocked(false), mSprite(nullptr), mTileState(EDefault), mSelected(false)
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	mSelected = !mSelected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	std::string text;
	switch (mTileState)
	{
		case EStart:
			text = "Assets/TileTan.png";
			break;
		case EBase:
			text = "Assets/TileGrey.png";
			break;
		case EPath:
			if (mSelected)
			{
				text = "Assets/TileBrownSelected.png";
			}
			else
			{
				text = "Assets/TileBrown.png";
			}
			break;
		case EDefault:
		default:
			if (mSelected)
			{
				text = "Assets/TileGreenSelected.png";
			}
			else
			{
				text = "Assets/TileGreen.png";
			}
			break;
	}

	mSprite->SetTexture(GetGame()->GetTexture(text));
}

