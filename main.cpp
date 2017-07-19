#include <iostream>
using namespace std;
#include <malloc.h>

typedef struct Vector{
	int maximum;
	int* pointer;
};

void merge_vectors(Vector& v1,Vector& v2, Vector& v3)
{
	_asm{
		mov eax,[ebp+8]
		mov ebx,[ebp+12]
		mov ecx,[eax]
		mov edx,[ebx]
		cmp ecx,edx
		jb varianta1
		jmp varianta2
varianta1:
		xor edx,edx
		mov ebx,[ebp+8]
		mov eax,[ebx+4]
loop1:
		mov ebx,[eax+edx*4]
		push ebx
		sub esp,4
		add edx,1
		cmp edx,ecx
		je add_v2
		jmp loop1
add_v2:
		mov eax,ecx
		add eax,ecx
		mov edx,4
		mul edx 
		add esp,eax
		mov ebx,[ebp+12]
		mov eax,[ebx+4]
loop2:
		mov ebx,[eax+edx*4]
		sub esp,4
		push ebx
		add edx,1
		cmp edx,ecx
		je add_v2_urm
		jmp loop2
add_v2_urm:
		mov eax,[ebp+12]
		mov ecx,[eax]
		mov ebx,[eax+4]
loop3:
		mov eax,[ebx+edx*4]
		push eax
		add edx,1
		cmp edx,ecx
		je add_v3
		jmp loop3
add_v3:
		mov ebx,[ebp+16]
		mov eax,[ebx]
		mov edx, 4
		mul edx
		add esp,eax
		mov eax,[ebp+16]
		mov ecx,[eax]
		mov ebx,[eax+4]

loop4:
		sub esp,4
		mov eax,[esp]
		mov [ebx+edx*4],eax
		add edx,1
		cmp edx,ecx
		je finish
		jmp loop4
varianta2:
		mov ecx,0
		mov ebx,[ebp+12]
		mov eax,[ebx+4]
loop5:
		mov ebx,[eax+ecx*4]
		sub esp,4
		push ebx
		add ecx,1
		cmp ecx,edx
		je add_v2_2
		jmp loop5
add_v2_2:
		mov eax,edx
		add eax,edx
		mov edx,4
		mul edx 
		add esp,eax
		mov ebx,[ebp+8]
		mov eax,[ebx+4]
loop6:
		mov ebx,[eax+edx*4]
		push ebx
		sub esp,4
		add edx,1
		cmp edx,ecx
		je add_v1_urm_2
		jmp loop6
add_v1_urm_2:
		mov eax,[ebp+8]
		mov ebx,[eax]
		cmp ecx,ebx
		je add_v3_2
		mov eax,[ebp+8]
		mov edx,[eax]
		mov ebx,[eax+4]
loop7:
		mov eax,[ebx+ecx*4]
		push eax
		add ecx,1
		cmp ecx,edx
		je add_v3_2
		jmp loop7
add_v3_2:
		mov ebx,[ebp+16]
		mov eax,[ebx]
		mov edx, 4
		mul edx
		add esp,eax
		mov eax,[ebp+16]
		mov ecx,[eax]
		mov ebx,[eax+4]

loop8:
		sub esp,4
		mov eax,[esp]
		mov [ebx+edx*4],eax
		add edx,1
		cmp edx,ecx
		je finish
		jmp loop8

finish:
		mov eax,ecx
		mov edx,4
		mul edx
		add esp,eax
		
	}
}


void main() {
	Vector v1,v2,v3;
	cout << "Insert the maximum number of values of the first vector ";
	cin >> v1.maximum;
	cout << "\n";
	v1.pointer = (int*) calloc (v1.maximum,sizeof(int));
	cout << "Insert the maximum number of values of the second vector ";
	cin >> v2.maximum;
	cout << "\n";
	v2.pointer = (int*) calloc (v2.maximum,sizeof(int));
	v3.maximum = v1.maximum + v2.maximum;
	v3.pointer = (int*) calloc (v3.maximum,sizeof(int));
	for (int i=0; i < v1.maximum;i++) {
		cout << " val1 :";
		cin >> v1.pointer[i] ;
	}
	for (int i=0; i < v2.maximum; i++) {
		cout << " val2 :";
		cin >> v2.pointer[i] ;
	}
	merge_vectors(v1, v2, v3);

	for (int i=0; i < v3.maximum; i++) {
		cout << v3.pointer[i] << " ";
	}
	

}