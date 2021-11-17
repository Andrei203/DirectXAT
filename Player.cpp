#include "Player.h"
#include <cmath>

void Player::Update(Keyboard& input, GameTime& timer)
{
	float inputX = static_cast<float>(input.GetKey('A')) - static_cast<float>(input.GetKey('D'));
	float inputY = static_cast<float>(input.GetKey('W')) - static_cast<float>(input.GetKey('S'));
	
	float relativeX = inputX * std::cosf(playerRot) - inputY * std::sinf(playerRot);
	float relativeY = inputX * std::sinf(playerRot) + inputY * std::cosf(playerRot);
	float inputCamera = static_cast<float>(input.GetKey(0x27)) - static_cast<float>(input.GetKey(0x25));
	
	player3pos.x += relativeX * timer.DeltaTime();
	player3pos.z += relativeY * timer.DeltaTime();
	playerRot += inputCamera * timer.DeltaTime();
}

void Player::Draw(Renderer& Rnd)
{
	DirectX::XMMATRIX matrix = DirectX::XMMatrixIdentity();
	matrix = DirectX::XMMatrixTranslation(player3pos.x, player3pos.y, player3pos.z) * matrix;
	matrix *= DirectX::XMMatrixRotationY(playerRot);
	
	Rnd.SetViewMatrix(matrix);
}
