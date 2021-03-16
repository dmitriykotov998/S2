#include <iostream>
#include <random>
#include <ctime>

using namespace std;

extern "C" {

        const int razmer = 10; //��������� ���������� ����� � ��������
        int tempRazmer = razmer; // ��� ASM ����

        int newArray[razmer];    // ������ ��� ASM ����

        int array[razmer][razmer]; //��������� ������
};

int main()
{
        srand(time(0));

        for (int i = 0; i < razmer; ++i)
        {
                for (int j = 0; j < razmer; ++j)
                {
                        array[i][j] = 0 + rand() % 1000; //��������� ��������� ����� �� 1000
                }
        }

        cout << "Matrix:" << endl; //����� �������
		for (int i = 0; i < razmer; i++)
		{
			for (int j = 0; j < razmer; j++)
			{
			cout << array[i][j] << " ";
			}
			cout << endl;
		}

        //��� �� ����������
        __asm
        (
        R"(
                .intel_syntax noprefix ; //���������� ��������� intel
                ;//{
                mov esi, 0                              ; //������� ��� ������ ����� ��������� ����������� �������
                mov ecx, 0                              ; //������� ��� ��������� ����� ��������� ���������� �������
                mov dl, 0                               ; //������� ��� ������� ���������� ���������� �����

                        Start:
                mov dh, 0                               ; //������� ��� ������� ���������� ���������� ��������� �������
                mov ebx, 1001               ; //�������� ������������ ��������

                        Main:
                mov eax, array[ecx]         ; //����� ��� ������������ ��������
                cmp eax, ebx                ; // ��������� ������������ � ����������� �� ������ ������
                jl Min                      ; // ���� ������, �� � ����� Min

                jmp Inc                     ; // ������� � �����

                        Min:
                mov ebx, eax                ; // ����� ������� ����������� ��������

                        Inc:
                add ecx, 4                  ; // ������� � ���������� ��������
                add dh, 1                   ; // ����������� �������� dh
                
						Check:
                cmp dh, BYTE PTR tempRazmer ; // ���� ���� ������, �� � ����� Main
                jl Main

                mov newArray[esi], ebx      ; // ������� ����� �������� � ��������� ������
                add esi, 4                  ; // ������� � ������� �������� �������

                        CheckEnd:
                add dl, 1                   ; // ����������� ���������� ��������� �����
                cmp dl, BYTE PTR tempRazmer ; // ���������, ���� �� ��� ������
                jl Start                    ; // ���� ����, �� � ����� �����
        ;//}
        .att_syntax
        )"
        );

        //����� ����������� ��������� �������
        cout << "Minimum elements in a matrix:" << endl;
        for (int i = 0; i < razmer; i++)
        {
                cout << newArray[i] << " ";
        }
        cout << endl;

        return 0;
}	
            
