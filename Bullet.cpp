#include "Bullet.h"
#include "BindableBase.h"
#include <cmath>

Bullet::Bullet(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX, float offsetY, float offsetZ, float direction) : transform(DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ)), pos(offsetX, offsetY, offsetZ)
{
    velocity = DirectX::XMFLOAT3(0.0F, 0.0F, -3.0F);
    velocity = DirectX::XMFLOAT3(velocity.x * std::cosf(direction) - velocity.z * std::sinf(direction),
        0.0F,
        velocity.x * std::sinf(direction) + velocity.z * std::cosf(direction));
    AddBind(std::make_unique<PixelShader>(Rnd, L"PixelShader.cso"));
    AddBind(std::make_unique<VertexShader>(Rnd, L"VertexShader.cso",
        std::vector<D3D11_INPUT_ELEMENT_DESC>{
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    }));
    AddBind(std::make_unique<VertexBuffer>(Rnd, std::vector<Vertex>
    {
        { -sizeX, -sizeY, -sizeZ, 0.0F, 0.0F },
        { +sizeX, -sizeY, -sizeZ, 1.0F, 0.0F },
        { -sizeX, -sizeY, +sizeZ, 0.0F, 1.0F },
        { +sizeX, -sizeY, +sizeZ, 1.0F, 1.0F },
        { -sizeX, +sizeY, -sizeZ, 0.0F, 0.0F },
        { +sizeX, +sizeY, -sizeZ, 1.0F, 0.0F },
        { -sizeX, +sizeY, +sizeZ, 0.0F, 1.0F },
        { +sizeX, +sizeY, +sizeZ, 1.0F, 1.0F },
        { -sizeX, -sizeY, +sizeZ, 0.0F, 1.0F },
        { +sizeX, -sizeY, +sizeZ, 1.0F, 1.0F },
        { -sizeX, +sizeY, +sizeZ, 0.0F, 0.0F },
        { +sizeX, +sizeY, +sizeZ, 1.0F, 0.0F },
        { -sizeX, -sizeY, -sizeZ, 1.0F, 1.0F },
        { +sizeX, -sizeY, -sizeZ, 0.0F, 1.0F },
        { -sizeX, +sizeY, -sizeZ, 1.0F, 0.0F },
        { +sizeX, +sizeY, -sizeZ, 0.0F, 0.0F },
        { -sizeX, -sizeY, +sizeZ, 1.0F, 1.0F },
        { -sizeX, +sizeY, +sizeZ, 1.0F, 0.0F },
        { -sizeX, -sizeY, -sizeZ, 0.0F, 1.0F },
        { -sizeX, +sizeY, -sizeZ, 0.0F, 0.0F },
        { +sizeX, -sizeY, +sizeZ, 0.0F, 1.0F },
        { +sizeX, +sizeY, +sizeZ, 0.0F, 0.0F },
        { +sizeX, -sizeY, -sizeZ, 1.0F, 1.0F },
        { +sizeX, +sizeY, -sizeZ, 1.0F, 0.0F },
    }));
    AddBind(std::make_unique<IndexBuffer>(Rnd, std::vector<unsigned short>{
        0, 2, 1, 2, 3, 1,
            4, 5, 6, 6, 5, 7,
            8, 10, 9, 9, 10, 11,
            12, 13, 14, 13, 15, 14,
            16, 18, 17, 17, 18, 19,
            20, 21, 22, 22, 21, 23
    }));
    AddBind(std::make_unique<Texture>(Rnd, L"bullet.jpg"));
    AddBind(std::make_unique<TextureSampler>(Rnd));
}

void Bullet::Draw(Renderer& Rnd)
{
    if (!isDestroyed)
    {
        Drawable::Draw(Rnd);
        Rnd.SetModelMatrix(transform);
        Rnd.GetContext()->DrawIndexed(36U, 0U, 0U);
    }
}



void Bullet::Update(GameTime& time)
{
    pos.x += velocity.x * time.DeltaTime();
    pos.y += velocity.y * time.DeltaTime();
    pos.z += velocity.z * time.DeltaTime();
    transform = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
}
