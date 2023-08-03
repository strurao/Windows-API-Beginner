#pragma once

enum class SceneType
{
	None,
	DevScene, // 테스트용
	GameScene, // 실제 인게임씬
	EditScene,

	// Fortress
	MenuScene,
	FortressScene
};

enum class PlayerType
{
	CanonTank,
	MissileTank
};

enum class Dir
{
	Left,
	Right
};