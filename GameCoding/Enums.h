#pragma once

enum class SceneType
{
	None,
	DevScene, // �׽�Ʈ��
	GameScene, // ���� �ΰ��Ӿ�
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