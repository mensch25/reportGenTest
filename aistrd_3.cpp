#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX_LEN 256
using namespace std;


struct ListNode {
    ListNode(char val) : val(val) {}
    char val;
    ListNode* next = nullptr;
};

class LinearList {
public:
    ListNode* head = nullptr;
    ListNode* last = nullptr;
    //метод вставки в конец списка
    void push_back(char val) {
        if (last == nullptr) {
            last = new ListNode(val);
            head = last;
            return;
        }
        last->next = new ListNode(val);
        last = last->next;
    }
    //метод вставки в начало
    void push(char val) {
        ListNode* tmp = new ListNode(val);
        tmp->next = head;
        head = tmp;
        if (!last) {
            last = head;
        }
    }
    //метод вставки по индексу
    void insert(int pos, char val) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return;
        }
        if (pos == 0) {
            push(val);
            return;
        }
        ListNode* cur = head;
        //переходим к нужному индексу
        while (pos > 1) {
            pos--;
            if (cur->next == nullptr) {
                cout << "Выход за пределы списка\n";
                return;
            }
            cur = cur->next;
        }
        ListNode* tmp = new ListNode(val);
        tmp->next = cur->next;
        cur->next = tmp;
    }
    //метод удаления из начала
    void remove_first() {
        ListNode* newHead = head->next;
        delete head;
        head = newHead;
    }
    //метод удаления из конца
    void remove_last() {
        ListNode* cur = head;
        while (cur->next != last) {
            cur = cur->next;
        }
        cur->next = nullptr;
        delete last;
        last = cur;
    }
    //метод удаления по индексу
    void remove(int pos) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return;
        }
        if (pos == 0) {
            remove_first();
            return;
        }
        ListNode* cur = head;
        //переходим к нужному индексу
        while (pos > 1) {
            pos--;
            if (cur->next == nullptr) {
                cout << "Выход за пределы списка\n";
                return;
            }
            cur = cur->next;
        }
        ListNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
    }
    //вывод списка
    void print() {
        cout << "Ваш список: ";
        ListNode* cur = head;
        while (cur != nullptr) {
            cout << ' ' << cur->val;
            cur = cur->next;
        }
        cout << '\n';
    }
    //поиск по значению
    int findByValue(char val) {
        ListNode* cur = head;
        int id = 0;
        while (cur != nullptr) {
            if (cur->val == val) {
                return id;
            }
            id++;
            cur = cur->next;
        }
        return -1;
    }
    //поиск по индексу
    char findByIndex(int pos) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return -1;
        }
        ListNode* cur = head;
        //переходим к нужному индексу
        while (pos > 0) {
            pos--;
            if (cur->next == nullptr) {
                cout << "Выход за пределы списка\n";
                return -1;
            }
            cur = cur->next;
        }
        return cur->val;
    }
};

class DinArray {
    int size = 0;
    int memSize;
    char* array;
    //увеличение памяти под массив
    void resize() {
        //создаем новый массив
        char* newArr = new char[memSize+10];
        //копируем данные в новый массив
        memcpy(newArr, array, size);
        size = memSize+10;
        delete [] array;
        array = newArr;
    }
public:
    DinArray(int memSize) : memSize(memSize) {
        array = new char[memSize];
    }
    //метод вставки в конец
    void push_back(char val) {
        if (size == memSize) {
            resize();
        }
        array[size++] = val;
    }
    //метод вставки в начало
    void push(char val) {
        if (size == memSize) {
            resize();
        }
        //перемещаем массив на одну ячейку
        memcpy(array+1, array, size);
        array[0] = val;
        size++;
    }
    //метод вставки по индексу
    void insert(int pos, char val) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return;
        }
        if (pos == 0) {
            push(val);
            return;
        }
        if (pos >= size) {
            cout << "Выход за пределы списка\n";
            return;
        }
        if (size == memSize) {
            resize();
        }
        //перемещаем массив на одну ячейку
        memcpy(array+pos+1, array+pos, size);
        array[pos] = val;
        size++;
    }
    //метод удаления из начала
    void remove_first() {
        memcpy(array, array+1, size);
        size--;
    }
    //метод удаления из конца
    void remove_last() {
        size--;
    }
    //метод удаления по индексу
    void remove(int pos) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return;
        }
        if (pos == 0) {
            remove_first();
            return;
        }
        if (pos >= size) {
            cout << "Выход за пределы списка\n";
            return;
        }
        //перемещаем массив на одну ячейку
        memcpy(array+pos, array+pos+1, size);
        size--;
    }
    //вывод списка
    void print() {
        cout << "Ваш массив: ";
        for (int i = 0; i < size; i++) {
            cout << array[i];
            cout << ' ';
        }
        cout << '\n';
    }
    //поиск по значению
    int findByValue(char val) {
        for (int i = 0; i < size; i++) {
            if (array[i] == val) {
                return i;
            }
        }
        return -1;
    }
    //поиск по индексу
    char findByIndex(int pos) {
        if (pos < 0) {
            cout << "Некорректный индекс\n";
            return -1;
        }

        if (pos >= size) {
            cout << "Выход за пределы массива\n";
            return -1;
        }

        return array[pos];
    }
};

class Stack {
    LinearList list;
public:
    void push(char val) {
        list.push(val);
    }

    char pop() {
        char val = list.head->val;
        list.remove_first();
        return val;
    }

    char top() {
        if (list.head != nullptr)
            return list.head->val;
        else return -1;
    }

    bool isEmpty() {
        if (this->top() == -1)
            return true;
        return false;
    }
};

void PostfixNotation(const char* _infix, char* _postfix) {
    Stack stack;
	int out_index = 0;      // индекс выходной строки
	int in_index = 0;       // индекс  входной строки
	if (_infix)				// входящая строка не должна быть пустой
	{
		do
		{
			char c = _infix[in_index];  // берем текущий символ входной строки
			switch (c)
			{
			case '+':
			case '-':
				// С учетом приоритета / > или = / выталкиваем из стека в выходную строку все операторы
				while (!stack.isEmpty())
				{
					char op = stack.top();  // оператор в вершине стека
					if (op != '(')  // все операторы, кроме откр. скобки имеют больший или равный приоритет
					{
						_postfix[out_index++] = op; // добавляем оператор в выходную строку
						stack.pop();         // удаляем оператор из стека
					}
					else break;
				}
				// помещаем оператор в стек
				stack.push(c);
				break;
			case '*':
			case '/':
				while (!stack.isEmpty())
				{
					char op = stack.top();
					if ((op == '^') || (op == '*') || (op == '/'))
					{
						_postfix[out_index++] = op; // добавляем оператор в выходную строку
                        stack.pop();       // удаляем оператор из стека
					}
					else
						break;
				}
				// помещаем оператор в стек
				stack.push(c);
				break;

			case '(':
				// просто помещаем в стек
                stack.push(c);
				break;

			case ')':
				// выталкиваем из стека в выходную строку все элементы до открывающей скобки (откр. скобку просто отбрасываем)
				while (!stack.isEmpty())
				{
					char op = stack.pop();          // забираем из стека оператор
					if (op == '(')                  // если достигли открывающей скобки
						break;                      // выталкивание закончили
					else
					{
						_postfix[out_index++] = op; // добавили оператор в выходную строку
					}
				}
				break;

			case '^':
				// помещаем оператор в стек /выталкивать ничего не нужно, нет операторов с большим приоритетом/
                stack.push(c);
				break;

			default:        // символ цифры
				_postfix[out_index] = c;    // добавление во выходную строку
				out_index++;
				break;
			}
			in_index++;
		} while (_infix[in_index] != 0);
	}
	else
	{
		cout << "\nОшибка! Строка Пуста! Нажмите Enter, чтобы начать сначала." << endl;
	};

	while (!stack.isEmpty())		// выталкиваем все операторы в выходную строку
	{
		_postfix[out_index++] = stack.pop();
	}
	_postfix[out_index] = 0;			// завершающий символ нуля
}

void listWork() {
    int count; //вспомогательная переменная, используется для хранения кол-ва элементов
    int id; //вспомогательная переменная, используется для хранения индексов
    char tmp; //вспомогательная переменная, используется для хранения значений
    LinearList list; //инициализируем списк
    cout << "//////// Работа со списком /////////\n";
    cout << "Введите количество элементов списка: ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        char val;
        cout << "Введите значение: ";
        cin >> val;
        list.push_back(val);
    }
    list.print();
    cout << "//Добавление в начало, введите значение: ";
    cin >> tmp;
    list.push(tmp);
    list.print();
    cout << "//Добавление в конец, введите значение: ";
    cin >> tmp;
    list.push_back(tmp);
    list.print();
    cout << "//Добавление в середину, введите значение: ";
    cin >> tmp;
    cout << "Введите индекс: ";
    cin >> id;
    list.insert(id, tmp);
    list.print();
    cout << "//Удаление из начала\n";
    list.remove_first();
    list.print();
    cout << "//Удаление из конца\n";
    list.remove_last();
    list.print();
    cout << "//Удаление из середины, введите индекс: ";
    cin >> id;
    list.remove(id);
    list.print();
    cout << "//Поиск по значению, введите значение: ";
    cin >> tmp;
    int res = list.findByValue(tmp);
    if (res < 0) {
        cout << "Элемент не найден\n";
    } else {
        cout << "Индекс элемента равен ";
        cout << res;
        cout << '\n';
    }
    cout << "//Поиск по индексу, введите индекс: ";
    cin >> id;
    char res_ = list.findByIndex(id);
    if (res_ != -1) {
        cout << "Значение элемента равно ";
        cout << res_;
        cout << '\n';
    }
    cout << "//Вставка элементов перед элементом с заданным значением, введите число элементов: ";
    cin >> count;
    cout << "Введите значение элемента, перед которым нужно вставить: ";
    cin >> tmp;
    id = list.findByValue(tmp);
    while (id < 0) {
        cout << "Элемент не найден, попробуйте снова: ";
        cin >> tmp;
        id = list.findByValue(tmp);
    }
    id = list.findByValue(tmp);
    cout << "Введите значения элементов для вставки\n";
    for (int i = 0; i < count; i++) {
        char val;
        cout << i;
        cout << ": ";
        cin >> val;
        list.insert(id+i, val);
    }
    list.print();
}

void dinArrayWork() {
    int count; //вспомогательная переменная, используется для хранения кол-ва элементов
    int id; //вспомогательная переменная, используется для хранения индексов
    char tmp; //вспомогательная переменная, используется для хранения значений
    DinArray array(10); //инициализируем списк
    cout << "//////// Работа с массивом /////////\n";
    cout << "Введите количество элементов массива: ";
    cin >> count;
    for (int i = 0; i < count; i++) {
        char val;
        cout << "Введите значение: ";
        cin >> val;
        array.push_back(val);
    }
    array.print();
    cout << "//Добавление в начало, введите значение: ";
    cin >> tmp;
    array.push(tmp);
    array.print();
    cout << "//Добавление в конец, введите значение: ";
    cin >> tmp;
    array.push_back(tmp);
    array.print();
    cout << "//Добавление в середину, введите значение: ";
    cin >> tmp;
    cout << "Введите индекс: ";
    cin >> id;
    array.insert(id, tmp);
    array.print();
    cout << "//Удаление из начала\n";
    array.remove_first();
    array.print();
    cout << "//Удаление из конца\n";
    array.remove_last();
    array.print();
    cout << "//Удаление из середины, введите индекс: ";
    cin >> id;
    array.remove(id);
    array.print();
    cout << "//Поиск по значению, введите значение: ";
    cin >> tmp;
    int res = array.findByValue(tmp);
    if (res < 0) {
        cout << "Элемент не найден\n";
    } else {
        cout << "Индекс элемента равен ";
        cout << res;
        cout << '\n';
    }
    cout << "//Поиск по индексу, введите индекс: ";
    cin >> id;
    char res_ = array.findByIndex(id);
    if (res_ != -1) {
        cout << "Значение элемента равно ";
        cout << res_;
        cout << '\n';
    }
    cout << "//Вставка элементов перед элементом с заданным значением, введите число элементов: ";
    cin >> count;
    cout << "Введите значение элемента, перед которым нужно вставить: ";
    cin >> tmp;
    id = array.findByValue(tmp);
    while (id < 0) {
        cout << "Элемент не найден, попробуйте снова: ";
        cin >> tmp;
        id = array.findByValue(tmp);
    }
    id = array.findByValue(tmp);
    cout << "Введите значения элементов для вставки\n";
    for (int i = 0; i < count; i++) {
        char val;
        cout << i;
        cout << ": ";
        cin >> val;
        array.insert(id+i, val);
    }
    array.print();
}

int main() {
	setlocale(LC_ALL, "rus");
	listWork();
	dinArrayWork();
	cout << "\n///////Преобразование записи алгебраического выражения из инфиксной в постфиксную/////////\n";
	cout << "Допустимые операторы: +,-,*,/,(,),^; все операции будем считать лево-ассоциативными\n";
	cout << "Все операнды - односимвольные.\nВведите выражение для перевода из инфиксной формы в постфиксную\n";
	cin.get();

    char str_infix[MAX_LEN];
//	gets_s(str_infix);  // тот же gets для Visual Studio
    cin.getline(str_infix, 256); //если не будет работать поменяй назад на строку выше, у меня не VS, предыдущий вариант не работал
    char str_postfix[MAX_LEN];
	cout << "Вы ввели: " << str_infix << endl;
	PostfixNotation(str_infix, str_postfix);
	cout << "Постфиксная форма выражения: " << str_postfix << endl;
	return 0;
}