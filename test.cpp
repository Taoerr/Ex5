#include<iostream>
using namespace std;

int main(){
	int a = 5;
	int sum = 0;
	for (int i = 1;i <= a;i++){
		sum += i;
	}
	cout << "sum is " << sum << endl;
}