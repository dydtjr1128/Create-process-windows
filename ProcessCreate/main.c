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
	//_T("abc") = L"abc", <- �����ڵ� ���·� ��ȯ
	
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
lpApplicationName : ������ ���μ����� �������� �̸��� ���ڷ� �����մϴ�. ��θ��� �߰��� ������ �� ������ ��θ��� �������� ���� ��쿡�� ���α׷��� ���� ���͸����� ã�� �˴ϴ�. ���� ���丮���� ã�� ���ϸ� NULL���� ������ �ݴϴ�.

lpCommandLine : main �Լ��� argc, argv��� �̸����� ���޵Ǵ� �� ó�� ���μ����� ���ڸ� ������ �� �̿��մϴ�. �Ǵ� ù ��° ���ڿ� NULL�� �ش��� �� �� ��° ���ڿ� ���������� �̸��� ���Ҿ� ������ ���� �ֽ��ϴ�. �� ��쿣 ���������� �̸��� ǥ�� �˻���� �������� ã�Ե˴ϴ�.

lpProcessAttribute : ���μ����� ���� �Ӽ��� ������ �� ����ϸ� NULL�� ������ ��� ����Ʈ ���� �Ӽ��� �����˴ϴ�.

lpThreadAttribute : �������� ���� �Ӽ��� ������ �� ����ϰ� �˴ϴ�. NULL�� ������ ��� ����Ʈ ���� �Ӽ��� �����մϴ�.

hInheritHandle : �������ڰ� TRUE�� ���, �����Ǵ� �ڽ� ���μ����� �θ� ���μ����� �����ϴ� handle�� �Ϻθ� ����մϴ�.

dwCreationFlag : �����ϴ� ���μ����� Ư��(Ư�� �켱����)�� �������� �� ����ϴ� �ɼ��Դϴ�. ���� ���� ���� ���� 0�� �����մϴ�.

lpEnvironment : ���μ������� Environment Block�̶�� �޸� ����� �����մϴ�. �� ����� �̿� ���μ����� ����� �ʿ�� �ϴ� ���ڿ��� ������ �� �ֽ��ϴ�. �� �������ڸ� ���ؼ� �����ϴ� Environment Block�� �����մϴ�. NULL�� �����ϸ� �ڽ� ���μ����� �θ� ���μ����� ȯ�� ��Ͽ� ����Ǿ� �ִ� ���ڿ��� �����ϰ� �˴ϴ�.

lpCurrentDirectory : �����ϴ� ���μ����� ���� ���丮�� �����ϴ� �����Դϴ�. �������ڴ� ���͸� ������ �����ϴ� ������η� �����ؾ��ϸ� NULL���޽� �θ����μ����� ���͸��� ���� ���͸��� �մϴ�.

lpStartInfo : STARTUPINFO ����ü ������ �ʱ�ȭ �Ѵ����� �� ������ �����͸� �μ��� �����մϴ�.

lpProcessInformation : �����ϴ� ���μ��� ������ ������� ���Ǵ� �����Դϴ�. PROCESS_INFORMATION ����ü ������ �ּҰ��� ���ڷ� �����մϴ�.

*/