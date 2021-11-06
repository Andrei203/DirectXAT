#include "Cube.h"
#include "BindableBase.h"

Cube::Cube(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX, float offsetY, float offsetZ) : transform(DirectX::XMMatrixTranslation(offsetX,offsetY,offsetZ))
{
	AddBind(std::make_unique<PixelShader>(Rnd, L"PixelShader.cso"));
	AddBind(std::make_unique<VertexShader>(Rnd, L"VertexShader.cso", 
		std::vector<D3D11_INPUT_ELEMENT_DESC>{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		}));
    AddBind(std::make_unique<VertexBuffer>(Rnd, std::vector<Vertex>{
        { -sizeX, -sizeY, -sizeZ },
        { +sizeX, -sizeY, -sizeZ },
        { -sizeX, +sizeY, -sizeZ },
        { +sizeX, +sizeY, -sizeZ },
        { -sizeX, -sizeY, +sizeZ },
        { +sizeX, -sizeY, +sizeZ },
        { -sizeX, +sizeY, +sizeZ },
        { +sizeX, +sizeY, +sizeZ },
    }));
    AddBind(std::make_unique<IndexBuffer>(Rnd, std::vector<unsigned short>{
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    }));
}

void Cube::Draw(Renderer& Rnd)
{
    Drawable::Draw(Rnd);
    Rnd.SetModelMatrix(transform);
    Rnd.GetContext()->DrawIndexed(36U, 0U, 0U);
}
