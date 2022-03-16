#include "Memory.hpp"

Memory::Memory()
{
}

Memory::~Memory()
{
}

UINT64 Memory::GetPattern(std::vector<BYTE> signature, UINT64 startaddress, UINT64 endaddress)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	if (startaddress == 0)
	{
		startaddress = (UINT64)(si.lpMinimumApplicationAddress);
	}

	if (endaddress == 0)
	{
		endaddress = (UINT64)(si.lpMaximumApplicationAddress);
	}

	MEMORY_BASIC_INFORMATION mbi{};
	UINT64 protectflags = (PAGE_GUARD | PAGE_NOCACHE | PAGE_NOACCESS);

	for (UINT64 i = startaddress; i < endaddress - signature.size(); i++)
	{
		if (VirtualQuery((LPCVOID)i, &mbi, sizeof(mbi)))
		{
			if (mbi.Protect & protectflags || !(mbi.State & MEM_COMMIT))
			{
				i += mbi.RegionSize;
				continue;
			}

			for (UINT64 k = (UINT64)mbi.BaseAddress; k < (UINT64)mbi.BaseAddress + mbi.RegionSize - signature.size(); k++)
			{
				for (UINT64 j = 0; j < signature.size(); j++)
				{
					if (signature.at(j) != -1 && signature.at(j) != *(BYTE*)(k + j))
						break;
					if (j + 1 == signature.size())
						return k;
				}
			}

			i = (UINT64)mbi.BaseAddress + mbi.RegionSize;
		}
	}

	return NULL;
}

UINT64 Memory::GetNonTerminatedStr(const char* dataset, int datasetLen, const char* target, int targetLen)
{
	int datasetpos, targetpos;
	datasetLen -= targetLen;

	for (datasetpos = 0; datasetpos <= datasetLen; datasetpos++)
	{
		for (targetpos = 0; targetpos < targetLen; targetpos++)
		{
			if (dataset[datasetpos + targetpos] != target[targetpos])
			{
				break;
			}
		}

		if (targetpos == targetLen)
		{
			return datasetpos;
		}
	}

	return NULL;
}

uintptr_t Memory::GetDMA(uintptr_t pBase, UINT * pOffsets, UINT iNumOffsets)
{
	uintptr_t pResolved = *(uintptr_t*)pBase;

	for (UINT i = 0; i < iNumOffsets - 1; i++)
	{
		pResolved = *(uintptr_t*)(pResolved + pOffsets[i]);
	}
	
	return (pResolved + pOffsets[iNumOffsets - 1]);
}

void Memory::WriteBytes(uintptr_t pAddress, BYTE * pBytes, UINT szSize)
{
	VirtualProtect((void*)pAddress, szSize, PAGE_EXECUTE_READWRITE, &dwOldProt);
	{
		if (pBytes != nullptr)
		{
			memcpy((void*)pAddress, pBytes, szSize);
		}

		else
		{
			memset((void*)pAddress, 0x90, szSize);
		}
	}

	VirtualProtect((void*)pAddress, szSize, dwOldProt, nullptr);
}