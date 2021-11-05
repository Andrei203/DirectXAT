#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Renderer& Rnd) noexcept
{
	return Rnd.pContext.Get();
}

ID3D11Device* Bindable::GetDevice(Renderer& Rnd) noexcept
{
	return Rnd.pDevice.Get();
}

