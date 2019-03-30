#include<iostream>
#include<Windows.h>
#include<Psapi.h>
#include<TlHelp32.h>
#pragma comment(lib,"Psapi.lib")
using namespace std;
int main()
{
	DWORD dwFlags = TH32CS_SNAPPROCESS;
	DWORD th32ProcessID = 0;
	HANDLE handle = CreateToolhelp32Snapshot(dwFlags, th32ProcessID);
	if (handle == INVALID_HANDLE_VALUE)
	{
		cout << "failed:" << GetLastError() << endl;
	}
	else {
		cout << handle << endl;
	}
	PROCESSENTRY32 processEntry32 = { 0 };
	processEntry32.dwSize = sizeof(processEntry32);
	int processCnt = 0;
	BOOL hasNext = Process32First(handle, &processEntry32);
	while (hasNext)
	{
		processCnt++;
		cout << processCnt << "  PID:" << processEntry32.th32ProcessID << " cntThreads:" << processEntry32.cntThreads << " parentPID:" << processEntry32.th32ParentProcessID << " exe:" << processEntry32.szExeFile << endl;
		hasNext = Process32Next(handle, &processEntry32);
	}
	DWORD pid;
	cout << "enter process id to terminal " << endl;
	cin >> pid;
	HANDLE termHandle = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (termHandle != NULL && termHandle != INVALID_HANDLE_VALUE)
	{
		int ret = TerminateProcess(termHandle, 0);
		cout <<"ret code:" << ret << endl;
		CloseHandle(termHandle);
	}
	CloseHandle(handle);
	return 0;
}