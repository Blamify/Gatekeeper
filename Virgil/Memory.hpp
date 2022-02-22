#include "Client.hpp"

class Memory
{
public:
	Memory();
	~Memory();
	UINT64 GetPattern(std::vector<BYTE> signature, UINT64 startaddress, UINT64 endaddress);
	UINT64 GetNonTerminatedStr(const char* dataset, int datasetLen, const char* target, int targetLen);
	uintptr_t GetDMA(uintptr_t pBase, UINT * pOffsets, UINT iNumOffsets);
	void WriteBytes(uintptr_t pAddress, BYTE * pBytes, UINT szSize);

	template <class T>
	T ReadValue(uintptr_t pAddress);

	template <class T>
	T ReadValue(uintptr_t pBase, UINT * pOffsets, UINT iNumOffsets);

	template <class T>
	bool WriteValue(uintptr_t pAddress, T data);

	template <class T>
	bool WriteValue(uintptr_t pBase, UINT * pOffsets, UINT iNumOffsets, T data);
	
private:
	DWORD dwOldProt;
};

template<class T>
inline T Memory::ReadValue(uintptr_t pAddress)
{
	return *RC<T*>(pAddress);
}

template<class T>
inline T Memory::ReadValue(uintptr_t pBase, UINT* pOffsets, UINT iNumOffsets)
{
	return *RC<T*>(GetDMA(pBase, pOffsets, iNumOffsets));
}

template<class T>
inline bool Memory::WriteValue(uintptr_t pAddress, T data)
{
	if (VirtualProtect((void*)pAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &dwOldProt))
	{
		*RC<T*>(pAddress) = data;
	}

	else
	{
		return false;
	}

	VirtualProtect((void*)pAddress, sizeof(T), dwOldProt, nullptr);

	if (*RC<T*>(pAddress) != data)
	{
		return false;
	}

	else
	{
		return true;
	}
}

template<class T>
inline bool Memory::WriteValue(uintptr_t pBase, UINT* pOffsets, UINT iNumOffsets, T data)
{
	T* dmaAddy = RC<T*>(GetDMA(pBase, pOffsets, iNumOffsets));

	if (VirtualProtect((void*)dmaAddy, sizeof(T), PAGE_EXECUTE_READWRITE, &dwOldProt))
	{
		*dmaAddy = data;
	}

	else
	{
		return false;
	}

	VirtualProtect((void*)dmaAddy, sizeof(T), dwOldProt, nullptr);

	if (*dmaAddy != data)
	{
		return false;
	}

	else
	{
		return true;
	}
}