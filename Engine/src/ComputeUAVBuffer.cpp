//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

#include "ComputeUAVBuffer.h"
#include "DirectXDeviceMan.h"

namespace Azul
{

	// Assume pDeviceContext is a valid ID3D11DeviceContext pointer
// Assume pBuffer is the buffer you want to read from




	ComputeUAVBuffer::ComputeUAVBuffer(size_t _count, size_t _structSize)
		: count{_count},
		structSize{_structSize},
		pBuff{nullptr},
		poComputeUAVBuffer{nullptr},
		poUnorderedAccessView{nullptr},
		bCreate{false}
	{
		this->privCreate(_count, _structSize);
		// Create a staging buffer
	}

	void ComputeUAVBuffer::privCreate(size_t _count, size_t _structSize)
	{
		// in case set was called before
		assert(this->bCreate == false);
		this->bCreate = true;

		this->count = _count;
		this->structSize = _structSize;
		assert(count > 0);
		assert(structSize > 0);
	
		HRESULT hr;

		// --------------------------
		// Create the buffer
		// --------------------------

		D3D11_BUFFER_DESC BufferDesc{0};

		BufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS ;
		BufferDesc.ByteWidth = this->count * this->structSize;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		BufferDesc.StructureByteStride = this->structSize;

		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&BufferDesc,
														 nullptr,
														 &this->poComputeUAVBuffer);
		assert(SUCCEEDED(hr));


		// --------------------------
		// Create the UAV buffer
		// --------------------------

		D3D11_UNORDERED_ACCESS_VIEW_DESC sbUAVDesc;

		sbUAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		sbUAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

		sbUAVDesc.Buffer.FirstElement = 0;
		sbUAVDesc.Buffer.Flags = 0;
		sbUAVDesc.Buffer.NumElements = this->count;  // number of structures
	
		hr = DirectXDeviceMan::GetDevice()->CreateUnorderedAccessView(this->poComputeUAVBuffer,
																	  &sbUAVDesc,
																	  &this->poUnorderedAccessView);
		assert(SUCCEEDED(hr));



		D3D11_BUFFER_DESC desc;
		this->poComputeUAVBuffer->GetDesc(&desc);
		desc.Usage = D3D11_USAGE_STAGING;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.BindFlags = 0;
		desc.MiscFlags = 0;

		poStagingBuffer = nullptr;
		hr = DirectXDeviceMan::GetDevice()->CreateBuffer(&desc, nullptr, &poStagingBuffer);
		assert(SUCCEEDED(hr));
		
	}

	void ComputeUAVBuffer::Transfer(void *_pBuff)
	{
		// in case set was called before
		assert(this->bCreate == true);

		this->pBuff = _pBuff;
		assert(pBuff);

		DirectXDeviceMan::GetContext()->UpdateSubresource(poComputeUAVBuffer,
														  0,
														  nullptr,
														  pBuff,
														  0,
														  0);
	}

	void ComputeUAVBuffer::BindCompute(UnorderedAccessBufferSlot slot)
	{
		DirectXDeviceMan::GetContext()->CSSetUnorderedAccessViews((size_t)slot,
																  1,
																  &poUnorderedAccessView,
																  nullptr);

	}

	void ComputeUAVBuffer::Map(char* pBuff, size_t size)
	{
		// Copy the data to the staging buffer
		DirectXDeviceMan::GetContext()->CopyResource(poStagingBuffer, this->poComputeUAVBuffer);

		// Map the staging buffer
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		DirectXDeviceMan::GetContext()->Map(poStagingBuffer, 0, D3D11_MAP_READ, 0, &mappedResource);
		memcpy(pBuff, (char*)mappedResource.pData, size); // This might fuck up???
		DirectXDeviceMan::GetContext()->Unmap(poStagingBuffer, 0);
	}

	ComputeUAVBuffer::~ComputeUAVBuffer()
	{
		SafeRelease(this->poComputeUAVBuffer);
		SafeRelease(this->poUnorderedAccessView);
		poStagingBuffer->Release();
	
	}

}

//--- End of File ---
