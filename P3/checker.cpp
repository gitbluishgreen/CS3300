#include <bits/stdc++.h>
using namespace std;
int getChar(FILE *f, bool ignWhite) {
	bool white;
	int ch;
	do {
		if ((ch = getc(f))==EOF)
			return -2;
		if (ch==' ' || ch=='\n' || ch=='\t' || ch=='\r')
			white=true;
		else white=false;
	} while (ignWhite && white);
	if (white)
		return -1;
	return ch;
}


void myexit() {
  cout<<"Accepted!\n";
  exit(0);
}

int main(int argc,char **argv) {
	FILE* fp1 = fopen(argv[1],"r");
	FILE* fp2 = fopen(argv[2],"r");
	int ch1 = getChar(fp1, true);
	int ch2 = getChar(fp2, true);
	while (ch1 == ch2) {
		if (ch1==-2)
			myexit();
		bool ignWhite;
		if (ch1==-1)
			ignWhite =true;
		else
			ignWhite=false;
		ch1 = getChar(fp1, ignWhite);
		ch2 = getChar(fp2, ignWhite);
	};
	if (ch1 == -2 && ch2 == -1 && getChar(fp1, true)==-2 )
		myexit();
	if (ch2 == -2 && ch1 == -1 && getChar(fp2, true)==-2)
		myexit();
	cout<<"Wrong answer!\n";
	return 0;
}
