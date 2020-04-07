/*
Автор: Мельников Владислав Андреевич
Группа: РИ280001

В данной программе выполнены следующие задания:
3. Сортировка массива указателями 
4. Макс мин элемент 
5. Пред макс, пред мин 
6. Нахождение недостающего элемента
7. Функция, создающая структуру с заданными полями
8. крестики нолики

*/

#include <iostream> 
#include <string> 
#include "PlayField.h"
#include "TreeNode.h"

using namespace std;

//prototypes....
void sort(int n, int* ptr, int start, int end);
void CreateAndPrintPerson();

#pragma region CrossesAndNoughts

int crossScore = 0, noughtScore = 0, drawScore = 0;

void printLine() {
	static const string line = "-------";
	cout << line << endl;
}


void PrintCell(PlayField::CellState cell) {
	string str = "| ";
	switch (cell) {
	case PlayField::csCross:
		str = "|X";
		break;
	case PlayField::csNought:
		str = "|O";
		break;
	default:
		break;
	}
	cout << str;
}

void PrintField(PlayField field) {
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) 
			PrintCell(field[PlayField::CellIdx::CreateCell(j, i)]);
		cout << "|" << endl;
	}
	printLine();
}

void recursiveTreeWalk(TreeNode*& root)
{
	for (int i = 0; i < 9; ++i) {
		auto startField = root->value();
		if (startField[PlayField::CellIdx::CreateCell(i % 3, i / 3)] == PlayField::csEmpty) {
			auto newField = startField.makeMove(PlayField::CellIdx::CreateCell(i % 3, i / 3));
			auto newRoot = new TreeNode(root, newField);
			root->addChild(newRoot);
		}
	}
	for (int i = 0; i < root->childCount(); i++)
	{
		auto newRoot = root->operator[](i);
		if (newRoot.isTerminal()) //если дошли до выйгрыша или тупика
		{
			// проверяем что же все-таки произошло....
			// на этапах проверки я не выводил поле и того кто победил, но при пустом поле вывод работает догло... 
			// поэтому он закомментирован
			auto stat = newRoot.fieldStatus();
			if (stat == PlayField::FieldStatus::fsCrossesWin)
			{
				//cout << "x" << endl;
				crossScore++;
			}
			else if (stat == PlayField::FieldStatus::fsNoughtsWin)
			{
				//cout << "o" << endl;
				noughtScore++;
			}
			else if (stat == PlayField::FieldStatus::fsDraw)
			{
				//cout << "draw" << endl;
				drawScore++;
			}
			//PrintField(newRoot.value());
		}
		else
		{ // ныряем глубже(прямиком на дно)
			TreeNode* temp = &newRoot;
			recursiveTreeWalk(temp);
		}
	}
}

//функция нужна для того чтобы задать начальное положение поля(сначала первыми всегда ходят крестики, смена строн происходит автоматически)
TreeNode AddCrossOrNought(TreeNode*& root, int index) 
{
	auto startField = root->value();
	auto newField = startField.makeMove(PlayField::CellIdx::CreateCell(index % 3, index / 3));
	auto newRoot = new TreeNode(root, newField);
	root->addChild(newRoot);
	return root->operator[](0);
}
#pragma endregion

int main()
{
	//Сортировка массива указателями 
#pragma region ArraySortByPointers
	int n = 10;
	int arr[] = { -12, 3523, 123, 12, 666, 5, 2, 310, 228, 69 };
	cout << "sort part of array form 3 to 6" << endl;
	sort(n, arr, 3, 6);
	cout << endl << "sort all array" << endl;
	sort(n, arr, 0, n - 1);
#pragma endregion

	//Макс мин элемент 
#pragma region MaxAndMin
	cout << endl << "Max: " << *(arr + n - 1) << endl;
	cout << "Min: " << *arr << endl;
	//Пред макс, пред мин 
	cout << endl << "Max without max: " << *(arr + n - 2) << endl;
	cout << "Min without min: " << *(arr+1) << endl;
	cout << endl << endl;
#pragma endregion
	//поиск недостающего элемента
#pragma region FindMissing
	int arr2[] = { 4, 5, 7, 8, 9, 10, 11 };
	int m = sizeof(arr) / sizeof(arr[0]);
	for (int i=1; i < m; i++) {
		if (arr2[i] - arr2[i - 1] != 1) {
			cout << arr2[i] - 1 << " is missing" << endl;
			break;
		}
	}
#pragma endregion
	//Функция, создающая структуру с заданными полями
#pragma region CreatingStucture
	CreateAndPrintPerson();
#pragma endregion
	//Крестики нолики
#pragma region CrossesAndNoughts
	cout << endl << endl;
	printLine();
	PlayField emptyField; //создаем пустое поле
	
	TreeNode root = TreeNode(nullptr, emptyField); // задаем корень дереву
	TreeNode* temp;
	
	// для того чтобы уменьшить время выполнения алгоритма лучше задать какую-то стартовую ситуацию
	temp = &root;
	root = AddCrossOrNought(temp, 0); // ставим крестик в верхний левый угол и перезаписываем корень(теперь это стартовая ситуация)

	temp = &root;
	root = AddCrossOrNought(temp, 4);// ставим нолик в центр и перезаписываем корень(теперь это стартовая ситуация)

	temp = &root;
	recursiveTreeWalk(temp);// "уходим нырять" и считаем победы или их отсутвие(ничья)
	cout << "crosses: "<< crossScore << " draw: " << drawScore << " noughts: " << noughtScore;
#pragma endregion
	return 0;
}

struct Person {
	int age;
	string name;
	char letter;
};

Person AddPerson(int age, string name, char letter)
{
	Person temp;
	temp.age = age;
	temp.name = name;
	temp.letter = letter;
	return temp;
}

void CreateAndPrintPerson()
{
	Person firstPerson = AddPerson(10, "Petya", 'b');
	cout << firstPerson.age << '\n';
	cout << firstPerson.name << '\n';
	cout << firstPerson.letter;
}

void sort(int n, int* ptr, int start, int end)
{
	int i, j, tmp;
 
	for (i = start; i <= end; i++) {
		for (j = i + 1; j <= end; j++) {
			if (*(ptr + j) < *(ptr + i)) {
				tmp = *(ptr + i);
				*(ptr + i) = *(ptr + j);
				*(ptr + j) = tmp;
			}
		}
	}

	for (i = 0; i < n; i++)
		cout << *(ptr + i) << " ";
}

int binSearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		if (arr[mid] == x)
			return mid;

		if (arr[mid] > x)
			return binSearch(arr, l, mid - 1, x);
		return binSearch(arr, mid + 1, r, x);
	}
	return -1;
}

