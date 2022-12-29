#pragma once
#include "common.hpp"
#include "iron_dome.h"
#include "defs.h"
#include <VersionHelpers.h>
#include <random>
#include <tchar.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <signal.h>
#include <stdlib.h>
#include "CRCpp.h"
#include <intrin.h>
#include "fiber_pool.hpp"
#define eax 0
#define ebx 1
#define ecx 2
#define edx 3

#pragma intrinsic(_ReturnAddress)
#if (defined(__ARM_NEON__) || defined(__ARM_NEON))
# define NEON_INTRINSICS_AVAILABLE 1
#else
# define NEON_INTRINSICS_AVAILABLE 0
#endif

#if BOOL_NEON_INTRINSICS_AVAILABLE
# include <arm_neon.h>
# if defined(__ARM_FEATURE_CRC32) || (__ARM_ACLE >= 200)
#  include <arm_acle.h>
# endif
#endif
#ifdef _WIN64
#define VALID_MACHINE IMAGE_FILE_MACHINE_AMD64
#else
#define VALID_MACHINE IMAGE_FILE_MACHINE_I386
#endif

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Psapi.lib")



namespace Hooks_Informastion
{
	HMODULE hNtDll = NULL;
	HMODULE hKernel = NULL;
	HMODULE hKernel32 = NULL;
	void* KIUEDRPage = NULL;
	DWORD CurrentProcessID = NULL;
	ULONG_PTR FPPID = NULL;

	// PEB.
	void* PEB_BeingDebuggedP = NULL;
	int32_t PEB_BeingDebuggedID = NULL;

	void* PEB_NtGlobalFlagP = NULL;
	int32_t PEB_NtGlobalFlagID = NULL;

	// HeapFlags
	void* FlagsHeapFlagsP = NULL;
	int32_t FlagsHeapFlagsID = NULL;

	// Some ntdll apis
	void* Nt_QueryProcessP = NULL;
	int32_t Nt_QueryProcessID = NULL;

	void* Nt_QuerySystemP = NULL;
	int32_t Nt_QuerySystemID = NULL;

	void* Nt_SetThreadInformationP = NULL;
	int32_t Nt_SetThreadInformationID = NULL;

	void* Nt_CloseP = NULL;
	int32_t Nt_CloseID = NULL;

	void* Nt_QueryObjectP = NULL;
	int32_t Nt_QueryObjectID = NULL;

	void* Nt_NtGetContextThreadP = NULL;
	int32_t Nt_NtGetContextThreadID = NULL;

	void* Nt_NtSetContextThreadP = NULL;
	int32_t Nt_NtSetContextThreadID = NULL;

	void* Nt_ContinueP = NULL;
	int32_t Nt_ContinueID = NULL;

	void* Nt_CreateThreadExP = NULL;
	int32_t Nt_CreateThreadExID = NULL;

	void* Nt_ExceptionDispatcherP = NULL;
	int32_t Nt_ExceptionDispatcherID = NULL;

	void* Nt_SetInformationProcessP = NULL;
	int32_t Nt_SetInformationProcessID = NULL;

	void* Nt_YieldExecutionP = NULL;
	int32_t Nt_YieldExecutionID = NULL;

	void* Nt_SetDebugFilterStateP = NULL;
	int32_t Nt_SetDebugFilterStateID = NULL;

	void* Kernel32_Process32FirstWP = NULL;
	int32_t Kernel32_Process32FirstWID = NULL;

	void* Kernel32_Process32NextWP = NULL;
	int32_t Kernel32_Process32NextWID = NULL;

	void* Kernel32_GetTickCountP = NULL;
	int32_t Kernel32_GetTickCountID = NULL;

	void* Kernel32_GetTickCount64P = NULL;
	int32_t Kernel32_GetTickCount64ID = NULL;
}

namespace big
{
	static bool RetrieveSystemDirectory(char* OutPut)
	{
#ifdef _WIN64
		GetSystemDirectoryA(OutPut, MAX_PATH);
#else
		GetSystemWow64DirectoryA(OutPut, MAX_PATH);
		if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
		{
			GetSystemDirectoryA(OutPut, MAX_PATH);
		}
#endif
		return true;
	}
	static bool IsAddressSection(ULONG_PTR address, ULONG_PTR Baseaddress, IMAGE_SECTION_HEADER* pSHeader, IMAGE_NT_HEADERS* ntheader, void** OutSBaseAddress,
		SIZE_T* OutSSize)
	{
		for (int i = 0; i < ntheader->FileHeader.NumberOfSections; i++)
		{
			if ((pSHeader->VirtualAddress <= (address - Baseaddress)) && ((address - Baseaddress) < (pSHeader->VirtualAddress + pSHeader->Misc.VirtualSize)))
			{
				*OutSBaseAddress = (void*)((ULONG_PTR)Baseaddress + pSHeader->VirtualAddress);
				*OutSSize = pSHeader->Misc.VirtualSize;
				return true;
			}
			pSHeader++;
		}
		return false;
	}
	static size_t ConvertRvaToOffset(ULONG_PTR address, ULONG_PTR Baseaddress, IMAGE_SECTION_HEADER* pSHeader, IMAGE_NT_HEADERS* ntheader)
	{
		for (int i = 0; i < ntheader->FileHeader.NumberOfSections; i++)
		{
			if ((pSHeader->VirtualAddress <= (address - Baseaddress)) && ((address - Baseaddress) < (pSHeader->VirtualAddress + pSHeader->Misc.VirtualSize)))
			{
				return (address - Baseaddress - pSHeader->VirtualAddress) + (pSHeader->PointerToRawData);
			}
			pSHeader++;
		}
		return NULL;
	}
	static bool IsAddressPresent(void** Buffer, void* Address, size_t size)
	{
		void** Start = Buffer;
		for (size_t i = 0; i < size; i++, Start++)
		{
			if (*Start == Address)
			{
				return true;
			}
		}
		return false;
	}
	void iron_dome::hidePeb()
	{
		void* PEB_BaseAddress = nullptr;
		void* _HeapAddress = nullptr;

		// Get PEB Address by the offset, or you can even call NtQueryInformationProcess.
		PEB_BaseAddress = (void*)GetPebFunction();

		if (PEB_BaseAddress)
		{
			// Check if we should patch the flags first.

			Hooks_Informastion::PEB_BeingDebuggedP = (void*)((ULONG_PTR)PEB_BaseAddress + PEB_BeingDebuggedOffset);
			*(BYTE*)Hooks_Informastion::PEB_BeingDebuggedP = 0;


			Hooks_Informastion::PEB_NtGlobalFlagP = (void*)((ULONG_PTR)PEB_BaseAddress + PEB_NtGlobalFlagOffset);
			*(BYTE*)Hooks_Informastion::PEB_NtGlobalFlagP = 0;


			// Get Process heap base address
			memcpy(&_HeapAddress, (void*)((ULONG_PTR)PEB_BaseAddress + HeapPEB_Offset), MAX_ADDRESS_SIZE);

			if (_HeapAddress)
			{
				// Check if the current Windows OS is Windows Vista or greater as different force flags and heap flags offsets in older versions.
				if (IsWindowsVistaOrGreater())
				{
					// Check if HEAP_GROWABLE flag is not setted, if not, we set it
					if (!(*(DWORD*)((ULONG_PTR)_HeapAddress + HeapFlagsBaseWinHigher) & HEAP_GROWABLE))
					{
						*(DWORD*)((ULONG_PTR)_HeapAddress + HeapFlagsBaseWinHigher) |= HEAP_GROWABLE;
					}
					*(DWORD*)((ULONG_PTR)_HeapAddress + HeapForceFlagsBaseWinHigher) = 0;
				}
				else
				{
					// Check if HEAP_GROWABLE flag is not setted, if not, we set it
					if (!(*(DWORD*)((ULONG_PTR)_HeapAddress + HeapFlagsBaseWinLower) & HEAP_GROWABLE))
					{
						*(DWORD*)((ULONG_PTR)_HeapAddress + HeapFlagsBaseWinLower) |= HEAP_GROWABLE;
					}
					*(DWORD*)((ULONG_PTR)_HeapAddress + HeapForceFlagsBaseWinLower) = 0;
				}
			}
		}
	}
	static CHAR SystemDirectory[MAX_PATH] = { 0 };
	void iron_dome::anti_attach()
	{
		// Vars
		void* Page = nullptr;
		void** ExportsPage = nullptr;
		void** ExportsPageDbg = nullptr;
		void* OriginalMappedNtdll = nullptr;

		size_t ExportsFunctions = 0;
		size_t fileSize = 0;

		HANDLE FileP = 0;

		// Check if the variable is empty 
		if (SystemDirectory[0] == 0)
		{
			RetrieveSystemDirectory(SystemDirectory);
			lstrcatA(SystemDirectory, "\\ntdll.dll");
		}

		// Read the file
		FileP = CreateFileA(SystemDirectory, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (FileP != INVALID_HANDLE_VALUE)
		{
			// Get file size
			fileSize = GetFileSize(FileP, NULL);

			Page = VirtualAlloc(nullptr, fileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			if (Page)
			{
				// Read the file and parse headers later
				DWORD READ;
				if (!ReadFile(FileP, Page, fileSize, &READ, NULL))
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				// Headers
				auto pDosHeader = (IMAGE_DOS_HEADER*)Hooks_Informastion::hNtDll;
				if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}
				auto pNtHeader = (IMAGE_NT_HEADERS*)((ULONG_PTR)Hooks_Informastion::hNtDll + pDosHeader->e_lfanew);
				if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}
				if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size <= 0)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}
				if (pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress <= 0)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				auto pDosHeaderFile = (IMAGE_DOS_HEADER*)Page;
				if (pDosHeaderFile->e_magic != IMAGE_DOS_SIGNATURE)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}
				auto pNtHeaderFile = (IMAGE_NT_HEADERS*)((ULONG_PTR)Page + pDosHeaderFile->e_lfanew);
				if (pNtHeaderFile->Signature != IMAGE_NT_SIGNATURE)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}
				if (pNtHeaderFile->FileHeader.Machine != VALID_MACHINE)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				// Map 
				OriginalMappedNtdll = VirtualAlloc(nullptr, pNtHeaderFile->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
				if (!OriginalMappedNtdll)
				{
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				memcpy(OriginalMappedNtdll, Page, pNtHeaderFile->OptionalHeader.SizeOfHeaders);
				auto pSecHeader = IMAGE_FIRST_SECTION(pNtHeaderFile);
				for (int i = 0; i < pNtHeaderFile->FileHeader.NumberOfSections; i++, pSecHeader++)
				{
					if (pSecHeader->SizeOfRawData)
					{
						memcpy((void*)((ULONG_PTR)OriginalMappedNtdll + pSecHeader->VirtualAddress), (void*)((ULONG_PTR)Page + pSecHeader->PointerToRawData),
							pSecHeader->SizeOfRawData);
					}
				}

				auto pExports = (IMAGE_EXPORT_DIRECTORY*)((ULONG_PTR)Hooks_Informastion::hNtDll + pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

				ExportsFunctions = (sizeof(void*) * pExports->NumberOfFunctions) + 0x100;
				ExportsPage = (void**)VirtualAlloc(0, ExportsFunctions, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if (!ExportsPage)
				{
					VirtualFree(OriginalMappedNtdll, 0, MEM_RELEASE);
					VirtualFree(Page, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				memset(ExportsPage, ExportsFunctions, 0);

				// Store exports pointers
				size_t DbgFunctionsCount = 0;
				DWORD* pExpNames = (DWORD*)((ULONG_PTR)Hooks_Informastion::hNtDll + pExports->AddressOfNames);
				WORD* pOrdinalName = (WORD*)((ULONG_PTR)Hooks_Informastion::hNtDll + pExports->AddressOfNameOrdinals);
				DWORD* pFunction = (DWORD*)((ULONG_PTR)Hooks_Informastion::hNtDll + pExports->AddressOfFunctions);

				for (unsigned int i = 0; i < pExports->NumberOfFunctions; i++)
				{
					for (unsigned int b = 0; b < pExports->NumberOfNames; b++)
					{
						if (pOrdinalName[b] == i)
						{
							auto pFunctionName = (PCHAR)((ULONG_PTR)Hooks_Informastion::hNtDll + pExpNames[b]);
							if (pFunctionName)
							{
								if (strncmp(pFunctionName, "Dbg", 3) == 0)
								{
									DbgFunctionsCount++;
								}
							}
						}
					}
					ExportsPage[i] = (void*)((ULONG_PTR)Hooks_Informastion::hNtDll + pFunction[i]);
				}

				ExportsPageDbg = (void**)VirtualAlloc(nullptr, (sizeof(void*) * DbgFunctionsCount) + 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
				if (!ExportsPageDbg)
				{
					VirtualFree(OriginalMappedNtdll, 0, MEM_RELEASE);
					VirtualFree(Page, 0, MEM_RELEASE);
					VirtualFree(ExportsPage, 0, MEM_RELEASE);
					CloseHandle(FileP);
					return;
				}

				memset(ExportsPageDbg, (sizeof(void*) * DbgFunctionsCount) + 0x100, 0);

				// Now store target functions that we must restore
				void** ExportsPageDbgFLoop = ExportsPageDbg;
				for (unsigned int i = 0; i < pExports->NumberOfNames; i++)
				{
					auto pFunctionName = (PCHAR)((ULONG_PTR)Hooks_Informastion::hNtDll + pExpNames[i]);
					if (pFunctionName)
					{
						if (strncmp(pFunctionName, "Dbg", 3) == 0)
						{
							*ExportsPageDbgFLoop = GetProcAddress(Hooks_Informastion::hNtDll, pFunctionName);
							ExportsPageDbgFLoop++;
						}
					}
				}

				// Restore
				for (size_t i = 0; i < DbgFunctionsCount; i++)
				{
					for (size_t m = 0; m < 0x100; m++)
					{
						PBYTE TargetRestoreAddr = (PBYTE)((ULONG_PTR)ExportsPageDbg[i] + m);
						DWORD CurrRVa;
						PBYTE pOrgByte;
						DWORD OLD;
						bool Break = false;
						if (m != 0)
						{
							// If we reach another export function then break.
							for (unsigned int x = 0; x < pExports->NumberOfFunctions; x++)
							{
								if (ExportsPage[x] == (void*)TargetRestoreAddr)
								{
									Break = true;
									break;
								}
							}
						}
						if (Break)
						{
							break;
						}
						CurrRVa = (DWORD)((ULONG_PTR)TargetRestoreAddr - (ULONG_PTR)Hooks_Informastion::hNtDll);
						pOrgByte = (PBYTE)((ULONG_PTR)OriginalMappedNtdll + CurrRVa);
						if (VirtualProtect(TargetRestoreAddr, sizeof(BYTE), PAGE_EXECUTE_READWRITE, &OLD))
						{
							*TargetRestoreAddr = *pOrgByte;
							VirtualProtect(TargetRestoreAddr, sizeof(BYTE), OLD, &OLD);
						}
					}
				}

				// Free
				VirtualFree(OriginalMappedNtdll, 0, MEM_RELEASE);
				VirtualFree(Page, 0, MEM_RELEASE);
				VirtualFree(ExportsPage, 0, MEM_RELEASE);
				VirtualFree(ExportsPageDbg, 0, MEM_RELEASE);
			}
			CloseHandle(FileP);
		}

	}
	void iron_dome::bsod()
	{
		typedef long (WINAPI* RtlSetProcessIsCritical)
			(BOOLEAN New, BOOLEAN* Old, BOOLEAN NeedScb);

		HMODULE ntdll = LoadLibraryA("ntdll.dll");

		if (ntdll) 
		{
			auto SetProcessIsCritical = (RtlSetProcessIsCritical)GetProcAddress(ntdll, "RtlSetProcessIsCritical");

			if (SetProcessIsCritical)SetProcessIsCritical(1, 0, 0);
		}
	}
	void iron_dome::force_crash()
	{
		volatile int* a = reinterpret_cast<volatile int*>(NULL);
		*a = 1;
		int* p = (int*)-1; *p = 1;
		char* freeThis;
		free(freeThis);
		abort();
	}
	WORD GetProcessIdFromName(LPCTSTR szProcessName)
	{
		
		PROCESSENTRY32 pe32;
		HANDLE hSnapshot = NULL;
		SecureZeroMemory(&pe32, sizeof(PROCESSENTRY32));

		// We want a snapshot of processes
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		// Check for a valid handle, in this case we need to check for
		// INVALID_HANDLE_VALUE instead of NULL
		if (hSnapshot == INVALID_HANDLE_VALUE) {
			return 0;
		}

		// Now we can enumerate the running process, also 
		// we can't forget to set the PROCESSENTRY32.dwSize member
		// otherwise the following functions will fail
		pe32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapshot, &pe32) == FALSE)
		{
			// Cleanup the mess
			CloseHandle(hSnapshot);
			return 0;
		}

		// Do our first comparison
		if (StrCmpI(pe32.szExeFile, szProcessName) == 0)
		{
			// Cleanup the mess
			CloseHandle(hSnapshot);
			return pe32.th32ProcessID;
		}

		// Most likely it won't match on the first try so 
		// we loop through the rest of the entries until
		// we find the matching entry or not one at all
		while (Process32Next(hSnapshot, &pe32))
		{
			if (StrCmpI(pe32.szExeFile, szProcessName) == 0)
			{
				// Cleanup the mess
				CloseHandle(hSnapshot);
				return pe32.th32ProcessID;
			}
		}

		// If we made it this far there wasn't a match, so we'll return 0
		// _tprintf(_T("\n-> Process %s is not running on this system ..."), szProcessName);

		CloseHandle(hSnapshot);
		return 0;
	}
	void iron_dome::process_check()
	{
		const TCHAR* szProcesses[] = {
		_T("ollydbg.exe"),			// OllyDebug debugger
		_T("ProcessHacker.exe"),	// Process Hacker
		_T("tcpview.exe"),			// Part of Sysinternals Suite
		_T("autoruns.exe"),			// Part of Sysinternals Suite
		_T("autorunsc.exe"),		// Part of Sysinternals Suite
		_T("filemon.exe"),			// Part of Sysinternals Suite
		_T("procmon.exe"),			// Part of Sysinternals Suite
		_T("regmon.exe"),			// Part of Sysinternals Suite
		_T("procexp.exe"),			// Part of Sysinternals Suite
		_T("idaq.exe"),				// IDA Pro Interactive Disassembler
		_T("idaq64.exe"),			// IDA Pro Interactive Disassembler
		_T("ImmunityDebugger.exe"), // ImmunityDebugger
		_T("Wireshark.exe"),		// Wireshark packet sniffer
		_T("dumpcap.exe"),			// Network traffic dump tool
		_T("HookExplorer.exe"),		// Find various types of runtime hooks
		_T("ImportREC.exe"),		// Import Reconstructor
		_T("PETools.exe"),			// PE Tool
		_T("LordPE.exe"),			// LordPE
		_T("SysInspector.exe"),		// ESET SysInspector
		_T("proc_analyzer.exe"),	// Part of SysAnalyzer iDefense
		_T("sysAnalyzer.exe"),		// Part of SysAnalyzer iDefense
		_T("sniff_hit.exe"),		// Part of SysAnalyzer iDefense
		_T("windbg.exe"),			// Microsoft WinDbg
		_T("joeboxcontrol.exe"),	// Part of Joe Sandbox
		_T("joeboxserver.exe"),		// Part of Joe Sandbox
		_T("joeboxserver.exe"),		// Part of Joe Sandbox
		_T("ResourceHacker.exe"),	// Resource Hacker
		_T("x32dbg.exe"),			// x32dbg
		_T("x64dbg.exe"),			// x64dbg
		_T("Fiddler.exe"),			// Fiddler
		_T("httpdebugger.exe"),		// Http Debugger
		};

		WORD iLength = sizeof(szProcesses) / sizeof(szProcesses[0]);
		for (int i = 0; i < iLength; i++)
		{
			TCHAR msg[256] = _T("");
			if (GetProcessIdFromName(szProcesses[i])) {

			   *((PINT)nullptr) = 0xDEADBEEF;

			   *((PINT)nullptr) = 0x69420;
			   *((PINT)nullptr) = 0xCU;
			   *((PINT)nullptr) = 0x69;
			   *((PINT)nullptr) = 0x420;
			
				iron_dome::force_crash();
			}
		}
	}
	void iron_dome::increase_image_size()
	{

#if defined (ENV64BIT)
		PPEB pPeb = (PPEB)__readgsqword(0x60);
#elif defined(ENV32BIT)
		PPEB pPeb = (PPEB)__readfsdword(0x30);
#endif


		// The following pointer hackery is because winternl.h defines incomplete PEB types
		PLIST_ENTRY InLoadOrderModuleList = (PLIST_ENTRY)pPeb->Ldr->Reserved2[1]; // pPeb->Ldr->InLoadOrderModuleList
		PLDR_DATA_TABLE_ENTRY tableEntry = CONTAINING_RECORD(InLoadOrderModuleList, LDR_DATA_TABLE_ENTRY, Reserved1[0] /*InLoadOrderLinks*/);
		PULONG pEntrySizeOfImage = (PULONG)&tableEntry->Reserved3[1]; // &tableEntry->SizeOfImage
		*pEntrySizeOfImage = (ULONG)((INT_PTR)tableEntry->DllBase + 0x100000);
	}
	void iron_dome::erase_pe_header()
	{
		DWORD OldProtect = 0;

		// Get base address of module
		char* pBaseAddr = (char*)GetModuleHandle(NULL);

		// Change memory protection
		VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
			PAGE_READWRITE, &OldProtect);

		// Erase the header
		SecureZeroMemory(pBaseAddr, 4096);
	}
	
	bool IsDebuggerPresent()
	{
		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (!hKernel32)
			return false;

		FARPROC pIsDebuggerPresent = GetProcAddress(hKernel32, "IsDebuggerPresent");
		if (!pIsDebuggerPresent)
			return false;

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot)
			return false;

		PROCESSENTRY32W ProcessEntry;
		ProcessEntry.dwSize = sizeof(PROCESSENTRY32W);

		if (!Process32FirstW(hSnapshot, &ProcessEntry))
			return false;

		bool bDebuggerPresent = false;
		HANDLE hProcess = NULL;
		DWORD dwFuncBytes = 0;
		const DWORD dwCurrentPID = GetCurrentProcessId();
		do
		{
			__try
			{
				if (dwCurrentPID == ProcessEntry.th32ProcessID)
					continue;

				hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
				if (NULL == hProcess)
					continue;

				if (!ReadProcessMemory(hProcess, pIsDebuggerPresent, &dwFuncBytes, sizeof(DWORD), NULL))
					continue;

				if (dwFuncBytes != *(PDWORD)pIsDebuggerPresent)
				{
					bDebuggerPresent = true;
					break;
				}
			}
			__finally
			{
				if (hProcess)
					CloseHandle(hProcess);
			}
		} while (Process32NextW(hSnapshot, &ProcessEntry));

		if (hSnapshot)
			CloseHandle(hSnapshot);
		return bDebuggerPresent;
	}
	void iron_dome::is_debugger_present()
	{
		if (IsDebuggerPresent())
		{
			iron_dome::force_crash();
		}
	}
#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)
	void iron_dome::nt_global_flag_check()
	{
#if defined (ENV64BIT)
		PPEB pPeb = (PPEB)__readgsqword(0x60);
#elif defined(ENV32BIT)
		PPEB pPeb = (PPEB)__readfsdword(0x30);
#endif
		DWORD offsetNtGlobalFlag = 0;
#ifdef _WIN64
		offsetNtGlobalFlag = 0xBC;
#else
		offsetNtGlobalFlag = 0x68;
#endif
		DWORD NtGlobalFlag = *(PDWORD)((PBYTE)pPeb + offsetNtGlobalFlag);
		if (NtGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED)
		{
			std::this_thread::sleep_for(500ms);
			exit(0);
			iron_dome::force_crash();
		}
		if (pPeb)
		{
			DWORD NtGlobalFlagWow64 = *(PDWORD)((PBYTE)pPeb + 0xBC);
			if (NtGlobalFlagWow64 & NT_GLOBAL_FLAG_DEBUGGED)
			{
				std::this_thread::sleep_for(500ms);
				abort();
				iron_dome::force_crash();
			}
		}
	}
	int GetHeapFlagsOffset(bool x64)
	{
		return x64 ?
			IsWindowsVistaOrGreater() ? 0x70 : 0x14 : //x64 offsets
			IsWindowsVistaOrGreater() ? 0x40 : 0x0C; //x86 offsets
	}
	int GetHeapForceFlagsOffset(bool x64)
	{
		return x64 ?
			IsWindowsVistaOrGreater() ? 0x74 : 0x18 : //x64 offsets
			IsWindowsVistaOrGreater() ? 0x44 : 0x10; //x86 offsets
	}
	void iron_dome::check_heap()
	{
#if defined (ENV64BIT)
		PPEB pPeb = (PPEB)__readgsqword(0x60);
#elif defined(ENV32BIT)
		PPEB pPeb = (PPEB)__readfsdword(0x30);
#endif
		PVOID heap = 0;
		DWORD offsetProcessHeap = 0;
		PDWORD heapFlagsPtr = 0, heapForceFlagsPtr = 0;
		BOOL x64 = FALSE;
#ifdef _WIN64
		x64 = TRUE;
		offsetProcessHeap = 0x30;
#else
		offsetProcessHeap = 0x18;
#endif
		heap = (PVOID) * (PDWORD_PTR)((PBYTE)pPeb + offsetProcessHeap);
		heapFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapFlagsOffset(x64));
		heapForceFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapForceFlagsOffset(x64));
		if (*heapFlagsPtr & ~HEAP_GROWABLE || *heapForceFlagsPtr != 0)
		{
			exit(0);
		}
		if (pPeb)
		{
			heap = (PVOID) * (PDWORD_PTR)((PBYTE)pPeb + 0x30);
			heapFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapFlagsOffset(true));
			heapForceFlagsPtr = (PDWORD)((PBYTE)heap + GetHeapForceFlagsOffset(true));
			if (*heapFlagsPtr & ~HEAP_GROWABLE || *heapForceFlagsPtr != 0)
			{
				exit(0);
			}
		}
	}
	void iron_dome::patch_dbg_breakpoint()
	{
		HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hNtdll)
			return;

		FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, "DbgBreakPoint");
		if (!pDbgBreakPoint)
			return;

		DWORD dwOldProtect;
		if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
			return;

		*(PBYTE)pDbgBreakPoint = (BYTE)0xC3; // ret
	}
#pragma pack(push, 1)
	struct DbgUiRemoteBreakinPatch
	{
		WORD  push_0;
		BYTE  push;
		DWORD CurrentPorcessHandle;
		BYTE  mov_eax;
		DWORD TerminateProcess;
		WORD  call_eax;
	};
#pragma pack(pop)
	void iron_dome::patch_dbg_remote_breakpoint()
	{
		HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
		if (!hNtdll)
			return;

		FARPROC pDbgUiRemoteBreakin = GetProcAddress(hNtdll, "DbgUiRemoteBreakin");
		if (!pDbgUiRemoteBreakin)
			return;

		HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
		if (!hKernel32)
			return;

		FARPROC pTerminateProcess = GetProcAddress(hKernel32, "TerminateProcess");
		if (!pTerminateProcess)
			return;

		DbgUiRemoteBreakinPatch patch = { 0 };
		patch.push_0 = '\x6A\x00';
		patch.push = '\x68';
		patch.CurrentPorcessHandle = 0xFFFFFFFF;
		patch.mov_eax = '\xB8';
		patch.TerminateProcess = (DWORD)pTerminateProcess;
		patch.call_eax = '\xFF\xD0';

		DWORD dwOldProtect;
		if (!VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), PAGE_READWRITE, &dwOldProtect))
			return;

		::memcpy_s(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch),
			&patch, sizeof(DbgUiRemoteBreakinPatch));
		VirtualProtect(pDbgUiRemoteBreakin, sizeof(DbgUiRemoteBreakinPatch), dwOldProtect, &dwOldProtect);
	}
	bool is_hw_breakpoint_active()
	{
		CONTEXT ctx;
		ZeroMemory(&ctx, sizeof(CONTEXT));
		ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

		if (!GetThreadContext(GetCurrentThread(), &ctx))
			return false;

		return ctx.Dr0 || ctx.Dr1 || ctx.Dr2 || ctx.Dr3;
	}
	void iron_dome::patch_hw_breakpoint()
	{
		//if (is_hw_breakpoint_active) {
			//std::this_thread::sleep_for(1000ms);
			//exit(0);
			//force_crash();
		//}
	}
		

	void iron_dome::patch_intrin()
	{
		PVOID pRetAddress = _ReturnAddress();
		if (*(PBYTE)pRetAddress == 0xCC) 
		{
			DWORD dwOldProtect;
			if (VirtualProtect(pRetAddress, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
			{
				*(PBYTE)pRetAddress = 0x90; 
				VirtualProtect(pRetAddress, 1, dwOldProtect, &dwOldProtect);
			}
		}
	}
	void iron_dome::patch_intrin2()
	{
		BYTE Patch = 0x90;
		PVOID pRetAddress = _ReturnAddress();
		if (*(PBYTE)pRetAddress == 0xCC)
		{
			DWORD dwOldProtect;
			if (VirtualProtect(pRetAddress, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
			{
				WriteProcessMemory(GetCurrentProcess(), pRetAddress, &Patch, 1, NULL);
				VirtualProtect(pRetAddress, 1, dwOldProtect, &dwOldProtect);
			}
		}
	}
	std::string iron_dome::RandomString(std::size_t StringLength)
	{
		const std::string Alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		
		std::random_device RandomDevice;
		std::mt19937 mtGen(RandomDevice());
		std::uniform_int_distribution<> uDistribution(0, Alphanumeric.size() - 1);

		std::string LoaderName;

		for (std::size_t i = 0; i < StringLength; i++) {

			LoaderName = LoaderName + Alphanumeric[uDistribution(mtGen)];
		}

		return LoaderName;


	}
}