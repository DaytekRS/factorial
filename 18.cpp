#include <iostream>
#include <algorithm>
#include <cstring>
char* rotateStr(char* str, int size) {
	char* rotateStr = (char*)malloc((size+1) * sizeof(char));
	for (int i = 0, j = strlen(str) - 1; i < size; i++, j--) {
		if (j < 0) rotateStr[i] = '0';
		else rotateStr[i] = str[j];
	}
	rotateStr[size] = 0;
	return rotateStr;
}

char* sum(char* a, char* b) {
	char* sum = (char*)calloc(std::max(strlen(a), strlen(b)) + 2, sizeof(char));


	a = rotateStr(a, std::max(strlen(a), strlen(b)));
	b = rotateStr(b, std::max(strlen(a), strlen(b)));

	int temp = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		int c = a[i] + b[i] - 48 * 2 + temp;
		if (c > 9)
		{
			temp = 1;
			c %= 10;
		}
		else temp = 0;
		sum[i] = c + 48;
	}

	if (temp != 0) sum[strlen(a)] = 49;

	free(a);
	free(b);
	return rotateStr(sum, strlen(sum));
}

char* mul(char* a, char* b) {
	char* mul= (char*)calloc(strlen(a)+strlen(b)+2, sizeof(char));
	mul[0] = '0';
	
	if (strlen(a) < strlen(b)) {
		char* temp = b;
		b = a;
		a = temp;
	}

	char* c = (char*)calloc(strlen(a) + strlen(b) + 2, sizeof(char));
	int temp = 0;
	for (int i = strlen(b)-1; i >=0 ; i--) {
		for (int j = strlen(a)-1; j >= 0 ; j--) {
			int cycle = strlen(b) + strlen(a) - i - j -2;
			for (int m = 0; m < strlen(b) - 1 - i; m++) c[m] = '0';
			c[cycle] = (b[i] - 48) * (a[j] - 48) + temp;
			temp = c[cycle] / 10;
			c[cycle] = (c[cycle] % 10) + 48;
			
		}
		if (temp != 0) c[strlen(c)] = temp + 48;
		temp = 0;
		char* rotateC = rotateStr(c, strlen(c));
		
		char* del_mul = mul;
		mul=sum(rotateC, mul);
		free(del_mul);
		free(rotateC);
	}
	free(c);
	return mul;
}

char* intToChar(int n) {
	char* arr = (char*)malloc(0);
	int i = 0;
	while (n != 0) {
		arr = (char*)realloc(arr, (i + 2) * sizeof(char));
		arr[i++] = (n % 10) + 48;
		arr[i] = 0;
		n = n / 10;
	}
	char* rotateArr = rotateStr(arr, strlen(arr));
	free(arr);
	return rotateArr;
}

char* factorial(int n) {
	char* factorial = (char*)calloc(2, sizeof(char));
	factorial[0] = '1';
	if (n == 0) {
		return factorial;
	}
	for (int i = 1; i <= n; i++) {
		char* delFactorial = factorial;
		char* delArr = intToChar(i);
		factorial = mul(factorial,delArr);
		free(delFactorial);
		free(delArr);
	}
	return factorial;
}

int main() {
	int n;
	std::cin >> n;
	char* fac = factorial(n);
	std::cout << fac;
	free(fac);
	system("pause");
	return 0;
}
