#define _CRT_SECURE_NO_WARNINGS

#include "Client.hpp"
#include "Exports.hpp"
#include "Memory.hpp"

static HINSTANCE User32Lib;

uintptr_t ModuleBase;
HMODULE hNtDll;
HMODULE hWinHttpDll;

typedef HINTERNET(__stdcall* _WinHttp_WinHttpOpenRequest)(HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName, LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR *ppwszAcceptTypes, DWORD dwFlags);
_WinHttp_WinHttpOpenRequest WinHttp_WinHttpOpenRequest;
_WinHttp_WinHttpOpenRequest WinHttp_WinHttpOpenRequestT;

typedef HINTERNET(__stdcall* _WinHttp_WinHttpConnect)(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved);
_WinHttp_WinHttpConnect WinHttp_WinHttpConnect;
_WinHttp_WinHttpConnect WinHttp_WinHttpConnectT;

uintptr_t MemCheck;

bool isEnabled = true;
bool isGameLoading = false;
bool isMHInit = false;
bool isActive = true;

HINTERNET WinHttpOpenRequestHook(HINTERNET hConnect, LPCWSTR pwszVerb, LPCWSTR pwszObjectName, LPCWSTR pwszVersion, LPCWSTR pwszReferrer, LPCWSTR *ppwszAcceptTypes, DWORD dwFlags)
{
	if (isActive == true)
	{
		dwFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA | WINHTTP_FLAG_ESCAPE_PERCENT | WINHTTP_FLAG_SECURE;
	}

	return WinHttp_WinHttpOpenRequestT(hConnect, pwszVerb, pwszObjectName, pwszVersion, pwszReferrer, ppwszAcceptTypes, dwFlags);
}

HINTERNET WinHttpConnectHook(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved)
{
	if (isActive == true)
	{
		pswzServerName = (L"anvillocalhost.com");
		nServerPort = 443;
	}

	return WinHttp_WinHttpConnectT(hSession, pswzServerName, nServerPort, dwReserved);
}

DWORD HookFunction(LPVOID pTarget, LPVOID pDetour, LPVOID pTrampoline, BOOL isWriteCopy)
{
	if (isMHInit == false)
	{
		if (MH_Initialize() != MH_OK)
		{
			cout << "Error: MHInit failed." << "\n";
			return 1;
		}

		isMHInit = true;
	}

	if (MH_CreateHook(pTarget, pDetour, (LPVOID*)pTrampoline) != MH_OK)
	{
		cout << "Error: MHCreateHook failed." << "\n";
		return 1;
	}

	if (MH_EnableHook(pTarget, isWriteCopy) != MH_OK)
	{
		cout << "Error: MHEnableHook failed." << "\n";
		return 1;
	}

	return 0;
}

DWORD SetupHook()
{
	hNtDll = LoadLibrary(TEXT("ntdll.dll"));
	hWinHttpDll = LoadLibrary(TEXT("winhttp.dll"));

	if (hNtDll != NULL && hWinHttpDll != NULL)
	{
		WinHttp_WinHttpConnect = (_WinHttp_WinHttpConnect)((uintptr_t)GetProcAddress(hWinHttpDll, "WinHttpConnect"));
		WinHttp_WinHttpOpenRequest = (_WinHttp_WinHttpOpenRequest)((uintptr_t)GetProcAddress(hWinHttpDll, "WinHttpOpenRequest"));

		Sleep(1000);

		Memory().WriteBytes((uintptr_t)GetProcAddress(hNtDll, "ZwProtectVirtualMemory"), (BYTE*)"\x4C\x8B\xD1\xB8\x50\x00\x00\x00\xF6\x04\x25\x08\x03\xFE\x7F\x01\x75\x03", 0x12);

		if (isEnabled == true)
		{
			HookFunction(WinHttp_WinHttpConnect, &WinHttpConnectHook, &WinHttp_WinHttpConnectT, FALSE);
			HookFunction(WinHttp_WinHttpOpenRequest, &WinHttpOpenRequestHook, &WinHttp_WinHttpOpenRequestT, FALSE);

			while (isGameLoading == true)
			{
				MemCheck = _byteswap_uint64(Memory().ReadValue<UINT64>((uintptr_t)ModuleBase + 0x0));
				cout << std::hex << MemCheck << "\n";

				if (MemCheck == 0x0)
				{
					isGameLoading = false;
				}
			}

			//HookFunction(sub_000000, &HaloHook, &sub_000000T, TRUE);
		}
	}

	return 0;
}

DWORD WINAPI MainThread(LPVOID param)
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stderr);
	freopen("CONOUT$", "w", stdout);

	std::cout << "Anvil v0.6.1 - By Xe" << "\n";

	ModuleBase = (uintptr_t)GetModuleHandle(L"HaloInfinite.exe");

	SetupHook();

	std::cout << "Base Address: " << std::hex << ModuleBase << "\n";

	while (isEnabled == true)
	{
		if (GetAsyncKeyState(VK_OEM_PLUS) & 1)
		{
			std::cout << "Key [+] pressed." << "\n";

			isActive = false;

			std::cout << "Override Enabled: " << "Using MS Servers." << "\n";
		}
	}

	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hInst);
		CreateThread(0, 0, MainThread, hInst, 0, 0);
		User32Lib = LoadLibrary(_T("C:\\Windows\\system32\\user32.dll"));

		if (!User32Lib)
		{
			return FALSE;
		}
	}

	if (reason == DLL_PROCESS_DETACH)
	{
		FreeLibrary(User32Lib);
	}

	return TRUE;
}