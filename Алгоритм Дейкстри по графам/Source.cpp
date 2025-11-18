#include <iostream>
#include <Windows.h>
using namespace std;

struct Duga {
	int x;
	int y;
	int w;
};
Duga* Add_dugi(Duga* mas, int& n, Duga tmp) {
	bool f = 0;
	for (int i = 0; i < n; i++) {
		if (mas[i].x == tmp.x && mas[i].y == tmp.y) {
			f = 1;
			break;
		}
	}
	if (f == 0) {
		mas = (Duga*)realloc(mas, (n + 1) * sizeof(Duga));
		mas[n] = tmp;
		n++;
	}
	else {
		cout << ">> ТАКА ДУГА ВЖЕ Є...\n";
	}
	return mas;
}
int Max_nomer_vershini(Duga* mas, int n) {
	int max = mas[0].x;
	for (int i = 0; i < n; i++) {
		if (mas[i].x > max) {
			max = mas[i].x;
		}
		if (mas[i].y > max) {
			max = mas[i].y;
		}
	}
	return max;
}
int** Iz_Spisku_dug_do_Matrci_vah(Duga* mas, int n_dug, int n) {
	const int max = INT_MAX;
	int** matr = new int* [n];
	for (int i = 0; i < n; i++) {
		matr[i] = new int[n];
		for (int j = 0; j < n; j++) {
			if (i == j) {
				matr[i][j] = 0;
			}
			else {
				matr[i][j] = max;
			}
		}
	}
	for (int i = 0; i < n_dug; i++) {
		matr[mas[i].x - 1][mas[i].y - 1] = mas[i].w;
	}
	return matr;
}
void Dijkstra(int** matr, int n, int s) {
	const int max = INT_MAX;
	int* dist = new int[n];
	bool* tutbyl = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = max;
		tutbyl[i] = false;
	}
	dist[s] = 0;
	for (int i = 0; i < n - 1; i++) {
		int min = max, u = -1;
		for (int j = 0; j < n; j++) {
			if (!tutbyl[j] && dist[j] < min) {
				min = dist[j];
				u = j;
			}
		}
		if (u == -1) {
			break;
		}
		else {
			tutbyl[u] = true;
		}
		for (int v = 0; v < n; v++) {
			if (!tutbyl[v] && matr[u][v] != max && dist[u] + matr[u][v] < dist[v]) {
				dist[v] = dist[u] + matr[u][v];
			}
		}
	}
	cout << "----------------------------------------\n";
	cout << ">> Найкоротші відстані від вершини " << s + 1 << ":\n";
	cout << "----------------------------------------\n";
	for (int i = 0; i < n; i++) {
		cout << "| До вершини " << i + 1 << " -> ";
		if (dist[i] == max) {
			cout << "НЕДОСЯЖНО...\n";
		}
		else {
			cout << dist[i] << " |\n";
		}
	}
	delete[] dist;
	delete[] tutbyl;
}
void Delete(int** matr, int n) {
	for (int i = 0; i < n; i++) {
		delete[] matr[i];
	}
	delete[] matr;
}
int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Duga* graph = nullptr;
	int n_dug = 0, n, s;
	char ch;
	cout << "\n";
	cout << "========= СТВОРЕННЯ СПИСКУ ДУГ =========\n";
	cout << "----------------------------------------\n";
	do {
		Duga tmp;
		cout << ">> Введіть вершину початку: ";
		cin >> tmp.x;
		cout << ">> Введіть вершину кінця: ";
		cin >> tmp.y;
		cout << ">> Введіть вагу ребра: ";
		cin >> tmp.w;
		graph = Add_dugi(graph, n_dug, tmp);
		cout << ">> Додати ще дугу? (y/n): ";
		cin >> ch;
		cout << "----------------------------------------\n";
	} while (ch == 'y' || ch == 'Y');
	int max_v = Max_nomer_vershini(graph, n_dug);
	do {
		cout << ">> Введіть кількість вершин (n): ";
		cin >> n;
		if (n < max_v) {
			cout << ">> Значення повинно бути > або = " << max_v << "!\n";
		}
	} while (n < max_v);
	int** matr = Iz_Spisku_dug_do_Matrci_vah(graph, n_dug, n);
	cout << "----------------------------------------\n";
	cout << ">> Введіть початкову вершину (1 - " << n << "): ";
	cin >> s;
	Dijkstra(matr, n, s - 1);
	cout << "----------------------------------------\n";
	cout << "========================================\n\n";
	free(graph);
	Delete(matr, n);
}