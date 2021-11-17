#include "WinCube.h"
#include "BindableBase.h"

WinCube::WinCube(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX, float offsetY, float offsetZ) : transform(DirectX::XMMatrixTranslation(offsetX, offsetY, offsetZ)), pos(offsetX, offsetY, offsetZ)
{
    AddBind(std::make_unique<PixelShader>(Rnd, L"PixelShader.cso"));
    AddBind(std::make_unique<VertexShader>(Rnd, L"VertexShader.cso",
        std::vector<D3D11_INPUT_ELEMENT_DESC>{
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    }));
    AddBind(std::make_unique<VertexBuffer>(Rnd, std::vector<Vertex>
    {
        { -sizeX, -sizeY, -sizeZ, 0.0F, 1.0F },
        { +sizeX, -sizeY, -sizeZ, 0.0F, 0.0F },
        { -sizeX, -sizeY, +sizeZ, 1.0F, 1.0F },
        { +sizeX, -sizeY, +sizeZ, 1.0F, 0.0F },
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
        0, 1, 2, 2, 1, 3,
            4, 6, 5, 6, 7, 5,
            8, 9, 10, 9, 11, 10,
            12, 14, 13, 13, 14, 15,
            16, 17, 18, 17, 19, 18,
            20, 22, 21, 22, 23, 21
    }));
    AddBind(std::make_unique<Texture>(Rnd, L"win.png"));
    AddBind(std::make_unique<TextureSampler>(Rnd));
}

void WinCube::Draw(Renderer& Rnd)
{
    Drawable::Draw(Rnd);
    Rnd.SetModelMatrix(transform);
    Rnd.GetContext()->DrawIndexed(36U, 0U, 0U);
}
