#pragma once
#include "Object.h"

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

class Player : public Object
{
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// Pos GetFirePos();

	// Fortress
	wstring GetMeshKey(); 

	void SetPlayerId(int32 playerId) { _playerId = playerId; }
	void SetPlayerType(PlayerType playerType) { _playerType = playerType; }
	void SetPlayerTurn(bool playerTurn) { _playerTurn = playerTurn; }

	int32 GetPlayerId() { return _playerId; }
	PlayerType GetPlayerType() { return _playerType; }
	bool GetPlayerTurn() { return _playerTurn; }

public:
	// float _barrelAngle = 0.f; // 포신 각도
	// float _barrelLength = 100.f; // 포신 길이

	// Fortress
	int32 _playerId = 0; // 턴제
	PlayerType _playerType = PlayerType::CanonTank;
	bool _playerTurn = false; // 턴제
	float _fireAngle = 0.f; // 포신 각도
};

