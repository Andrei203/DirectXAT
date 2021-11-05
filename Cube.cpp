#include "Cube.h"
#include "BindableBase.h"

Cube::Cube(Renderer& Rnd, float sizeX, float sizeY, float sizeZ, float offsetX, float offsetY, float offsetZ)
{
	AddBind(std::make_unique<PixelShader>(Rnd, L"PixelShader.cso"));
	AddBind(std::make_unique<VertexShader>(Rnd, L"VertexShader.cso", 
		std::vector<D3D11_INPUT_ELEMENT_DESC>{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		}));
    AddBind(std::make_unique<VertexBuffer>(Rnd, std::vector<Vertex>{
        { -sizeX + offsetX, -sizeY + offsetY, -sizeZ + offsetZ },
        { +sizeX + offsetX, -sizeY + offsetY, -sizeZ + offsetZ },
        { -sizeX + offsetX, +sizeY + offsetY, -sizeZ + offsetZ },
        { +sizeX + offsetX, +sizeY + offsetY, -sizeZ + offsetZ },
        { -sizeX + offsetX, -sizeY + offsetY, +sizeZ + offsetZ },
        { +sizeX + offsetX, -sizeY + offsetY, +sizeZ + offsetZ },
        { -sizeX + offsetX, +sizeY + offsetY, +sizeZ + offsetZ },
        { +sizeX + offsetX, +sizeY + offsetY, +sizeZ + offsetZ },
    }));
    AddBind(std::make_unique<IndexBuffer>(Rnd, std::vector<unsigned short>{
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    }));
    ConstantBuffer::ConstantBufferData cb;
    /*cb.model = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };*/
    cb.model = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
    cb.view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0F, 0.0F, -5.0f));
    cb.projection = {
        3.0F, 0.0f, 0.0f, 0.0f,
        0.0f, 4.0F, 0.0f, 0.0f,
        0.0f, 0.0f, -1.0f, -0.01f,
        0.0f, 0.0f, -1.0f, 0.0f
    };
    cb.projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveRH(1.0F, 3.0F / 4.0F, 0.1F, 100.0F));
    ConstantBuffer constantBuffer = ConstantBuffer(Rnd, cb);
    constantBuffer.Bind(Rnd, cb);
}

void Cube::Draw(Renderer& Rnd)
{
    Drawable::Draw(Rnd);
    Rnd.GetContext()->DrawIndexed(36U, 0U, 0U);
}
