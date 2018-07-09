#include <stdio.h>
#include <tchar.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // !WIN32


int main(int argc, int **argv) {
	//Init Process setting
	STARTUPINFO si = {0,};
	PROCESS_INFORMATION pi = {0, };
	si.cb = sizeof(si);


	char buf[100];
	sprintf(buf, "C:\\Temp\\mosquitto-1.4.14\\build\\src\\Release\\mosquitto.exe -v");
	
	
	
	TCHAR command[] = _T("C:\\Temp\\mosquitto-1.4.14\\build\\src\\Release\\mosquitto.exe -v");
	TCHAR command2[] = _T("C:\\Temp\\mosquitto-1.4.14\\build\\client\\Release\\mosquitto_pub.exe -t \"a/b\" -m \"2\" -q 0");
	//_T("abc") = L"abc", <- 유니코드 형태로 변환
	
	// Start the child process.	
	if (!CreateProcessW(NULL,      // app path //CreateProcessW for Win10
		command,     // Command line (needs to include app path as first argument. args seperated by whitepace)
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
/*
lpApplicationName : 생성한 프로세스의 실행파일 이름을 인자로 전달합니다. 경로명을 추가로 지정할 수 있으며 경로명을 지정하지 않을 경우에는 프로그램의 현재 디렉터리에서 찾게 됩니다. 현재 디렉토리에서 찾길 원하면 NULL값을 지정해 줍니다.

lpCommandLine : main 함수에 argc, argv라는 이름으로 전달되는 것 처럼 프로세스에 인자를 전달할 때 이용합니다. 또는 첫 번째 인자에 NULL을 준다음 이 두 번째 인자에 실행파일의 이름을 더불어 전달할 수도 있습니다. 이 경우엔 실행파일의 이름은 표준 검색경로 기준으로 찾게됩니다.

lpProcessAttribute : 프로세스의 보안 속성을 지정할 때 사용하며 NULL을 전달할 경우 디폴트 보안 속성이 지정됩니다.

lpThreadAttribute : 쓰레드의 보안 속성을 지정할 때 사용하게 됩니다. NULL을 전달할 경우 디폴트 보안 속성을 적용합니다.

hInheritHandle : 전달인자가 TRUE일 경우, 생성되는 자식 프로세스는 부모 프로세스가 소유하는 handle중 일부를 상속합니다.

dwCreationFlag : 생성하는 프로세스의 특성(특히 우선순위)를 결정지을 때 사용하는 옵션입니다. 설정 하지 않을 때는 0을 전달합니다.

lpEnvironment : 프로세스마다 Environment Block이라는 메모리 블록을 관리합니다. 이 블록을 이용 프로세스가 실행시 필요로 하는 문자열을 저장할 수 있습니다. 이 전달인자를 통해서 생성하는 Environment Block을 지정합니다. NULL을 던달하면 자식 프로세스는 부모 프로세스의 환경 블록에 저장되어 있는 문자열을 복사하게 됩니다.

lpCurrentDirectory : 생성하는 프로세스의 현재 디렉토리를 설정하는 인자입니다. 전달인자는 디렉터리 정보를 포함하는 완전경로로 구성해야하며 NULL전달시 부모프로세스의 디렉터리를 현재 디렉터리로 합니다.

lpStartInfo : STARTUPINFO 구조체 변수를 초기화 한다음에 이 변수의 포인터를 인수로 전달합니다.

lpProcessInformation : 생성하는 프로세스 정보를 얻기위해 사용되는 인자입니다. PROCESS_INFORMATION 구조체 변수의 주소값을 인자로 전달합니다.

*/