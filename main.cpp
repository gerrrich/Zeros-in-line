#include <iostream>
#include <string>

using namespace std;

void print(char**a, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

char** gener(int n, int m) {
	char** a = new char*[n];
	for (int i = 0; i < n; i++) {
		a[i] = new char[m];
		for (int j = 0; j < m; j++) {
			a[i][j] = '0' + rand() % 2;
		}
	}
	return a;
}

char** func(char **a, int n, int m) {
	int maxans = 0, maxnum = 0, how = 0, maxi = 0, maxj = 0;
	unsigned int index = 0;
	string cur = "", temp = "";


	for (int i = 0; i < n; i++) {//по горизонтали (how=1)
		maxnum = 0;
		cur = a[i];
		temp = "0";
		for (int j = 0; j < m; j++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 1;
			maxi = i;
			maxj = index;
		}
	}

	for (int j = 0; j < m; j++) {//по вертикали (how=2)
		cur.clear();
		for (int i = 0; i < n; i++) {
			cur += a[i][j];
		}
		maxnum = 0;
		temp = "0";
		for (int i = 0; i < n; i++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 2;
			maxj = j;
			maxi = index;
		}
	}

	for (int i = 0; i < n; i++) {//на искосок "\" начиная с первого столбца по всем строкам (how=3)
		cur.clear();
		for (int j = 0; j < m && i + j < n; j++) {
			cur += a[i + j][j];
		}
		maxnum = 0;
		temp = "0";
		for (int j = 0; j < cur.length(); j++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 3;
			maxi = i + index;
			maxj = index;
		}
	}

	for (int j = 1; j < m; j++) {//на искосок "\" начиная с верхней строки по всем столбцам (how=4)
		cur.clear();
		for (int i = 0; j + i < m && i < n; i++) {
			cur += a[i][j + i];
		}
		maxnum = 0;
		temp = "0";
		for (int i = 0; i < cur.length(); i++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 4;
			maxi = index;
			maxj = j + index;
		}
	}

	for (int i = 0; i < n / 2; i++) {//переворот верх меняем с низом
		swap(a[i], a[n - i - 1]);
	}

	for (int i = 0; i < n; i++) {//после транспонирования тот же искосок уже идет "/" (how=5)
		cur.clear();
		for (int j = 0; j < m && i + j < n; j++) {
			cur += a[i + j][j];
		}
		maxnum = 0;
		temp = "0";
		for (int j = 0; j < cur.length(); j++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 5;
			maxi = i + index;
			maxj = index;
		}
	}

	for (int j = 1; j < m; j++) {//после транспонирования тот же искосок уже идет "/" (how=6)
		cur.clear();
		for (int i = 0; j + i < m && i < n; i++) {
			cur += a[i][j + i];
		}
		maxnum = 0;
		temp = "0";
		for (int i = 0; i < cur.length(); i++) {
			if (cur.find(temp) != UINT_MAX) {
				index = cur.find(temp);
				maxnum++;
			}
			else
				break;
			temp.append("0");
		}
		if (maxnum > maxans) {
			maxans = maxnum;
			how = 6;
			maxi = index;
			maxj = j + index;
		}
	}

	if (how == 5 || how == 6) {
		for (int i = 0; i < maxans; i++)
			a[maxi + i][maxj + i] = '8';

		for (int i = 0; i < n / 2; i++) {//возврат к исходной
			swap(a[i], a[n - i - 1]);
		}

		return a;
	}

	for (int i = 0; i < n / 2; i++) {//возврат к исходной
		swap(a[i], a[n - i - 1]);
	}

	if (how == 3 || how == 4) {
		for (int i = 0; i < maxans; i++)
			a[maxi + i][maxj + i] = '8';

		return a;
	}

	if (how == 1) {
		for (int i = 0; i < maxans; i++)
			a[maxi][maxj + i] = '8';
		return a;
	}

	if (how == 2) {
		for (int i = 0; i < maxans; i++)
			a[maxi + i][maxj] = '8';
		return a;
	}
}

int main()
{
	int n = 10, m = 10;
	char **a = gener(n, m);
	print(a, n, m);
	cout << endl;
	print(func(a, n, m),n,m);
}
