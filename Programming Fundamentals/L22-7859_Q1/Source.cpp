#include<iostream>
using namespace std;
void main() {
	int start,end,pal,count,x,y;
	cout << "Enter starting range: ";
	cin >> start;
	cout << "Enter ending range: ";
	cin >> end;
	if (start >= 0 && end > start)
	{
		cout << "Prime numbers in the range are: ";
		for (int i = start; i <= end; i++) {
			if (i == 0 || i == 1) {
				continue;
			}
			count = 1;
			for (int j = 2; j <= i / 2; j++) {
				if (i % j == 0) {
					count = 0;
					break;
				}
			}
			if (count == 1)
			{
				cout << i << ",";
			}
		}
		cout << endl;
		cout << "Palindromes in the range are: ";
		for (int k = start; k <= end; k++) {
			y = k;
			pal = 0;
			while (y != 0) {
				x = y % 10;
				y = y / 10;
				pal = (pal * 10) + x;
			}

			if (k == pal) 
			{
				cout << k << ",";
			}
		}
	}
	else cout << "Range should be positive and ending range should be bigger than starting range";
	
}