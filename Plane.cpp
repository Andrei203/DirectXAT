#include "Plane.h"
#include "BindableBase.h"

Plane::Plane(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX, float offsetY, float offsetZ) : transform(DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ))
{
    AddBind(std::make_unique<PixelShader>(Rnd, L"PixelShader.cso"));
    AddBind(std::make_unique<VertexShader>(Rnd, L"VertexShader.cso",
        std::vector<D3D11_INPUT_ELEMENT_DESC>{
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    }));
    AddBind(std::make_unique<VertexBuffer>(Rnd, std::vector<Vertex>
    {
        { -sizeX, 0.0F, -sizeY, 0.0F, 0.0F },
        { -sizeX, 0.0F, +sizeY, 1.0F , 0.0F },
        { +sizeX, 0.0F, -sizeY, 0.0F, 1.0F  },
        { +sizeX, 0.0F, +sizeY, 1.0F, 1.0F },
    }));
    AddBind(std::make_unique<IndexBuffer>(Rnd, std::vector<unsigned short>{
        0, 2, 1, 2, 3, 1,
    }));
    AddBind(std::make_unique<Texture>(Rnd, L"Floor.png"));
    AddBind(std::make_unique<TextureSampler>(Rnd));
}

void Plane::Draw(Renderer& Rnd)
{
    Drawable::Draw(Rnd);
    Rnd.SetModelMatrix(transform);
    Rnd.GetContext()->DrawIndexed(36U, 0U, 0U);
}
