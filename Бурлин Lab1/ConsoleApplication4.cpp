
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct truba{
	int id;
	double length;
	double diameter;
	bool repair;
};
struct cs {
	int id;
	string name;
	int number_work;
	int number_inwork;
	double effect;
};

bool check_value(int x) {
	return x > 0 ? true : false;
}
bool check_value(double x) {
	return x > 0 ? true : false;
}


truba create_truba() {
	truba new_truba;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите диаметр: " << endl;
		cin >> new_truba.diameter;
	} while (!check_value(new_truba.diameter) || cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введит длину: " << endl;
		cin >> new_truba.length;
	} while (!check_value(new_truba.length) || cin.fail());
	new_truba.repair = false;
	new_truba.id = -1;
	return new_truba;
}

cs create_cs() {
	cs new_cs;
	cout <<"Введите имя: " << endl;
	cin >> new_cs.name;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите кол-во цехов: " << endl;
		cin >> new_cs.number_work;
	} while (!check_value(new_cs.number_work) || cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите кол-во рабочих цехов: " << endl;
		cin >> new_cs.number_inwork;
	} while (!(check_value(new_cs.number_inwork) && (new_cs.number_inwork <= new_cs.number_work)) || cin.fail());

	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Введите эффективность: " << endl;
		cin >> new_cs.effect;
	} while (!check_value(new_cs.effect) || cin.fail());
	new_cs.id = -1;
	return new_cs;
}

void write_truba_info(const truba& t) 
{
	cout << "Диаметр: " << t.diameter << endl;
	cout << "Длина: " << t.length << endl;
	cout << "id: " << t.id << endl;
	cout << (t.repair ? "В ремонте" : "Не в ремонте") << endl;
}
void write_cs_info(const cs& c) 
{
	cout << "имя:" << c.name << endl;
	cout << "кол-во цехов: " << c.number_work << endl;
	cout << "Кол-во рабочих цехов: " << c.number_inwork << endl;
	cout << "Эффективность: " << c.effect <<endl ;
}


void change_status(bool& status) {
	status = !status;
}


void save_to_fileT(truba t) {
	ofstream fout;
	fout.open("DataTruba.txt", ios::out);
	if (fout.is_open()) {
		fout << t.id << endl << t.diameter << endl << t.length << endl << t.repair;
		fout.close();
	}
}
void save_to_fileC(cs c) {
	ofstream fout;
	fout.open("DataCS.txt", ios::out);
	if (fout.is_open()) {
		fout << c.id << endl << c.name << endl << c.number_work << endl << c.number_inwork << endl << c.effect;
		fout.close();
	}
}

truba load_from_fileT() {
	ifstream fin;
	fin.open("DataTruba.txt", ios::in);
	truba t;
	if (fin.is_open()) {
		fin >> t.id;
		fin >> t.diameter;
		fin >> t.length;
		fin >> t.repair;
		fin.close();
		return t;
	}
}
cs load_from_fileC() {
	ifstream fin;
	fin.open("DataCS.txt", ios::in);
	cs c;
	if (fin.is_open()) {
		fin >> c.id;
		fin >> c.name;
		fin >> c.number_work;
		fin >> c.number_inwork;
		fin >> c.effect;
		return c;
		fin.close();
	}
}


void stop_work(cs& c) 
{
	c.number_inwork--;
}
void continue_work(cs& c) 
{
	c.number_inwork++;
}



void PrintMenu() {
	cout << "1. Загрузить трубу из файла" << endl;
	cout << "2. Создать трубу" << endl;
	cout << "3. Создать компрессорную станцию" << endl;
	cout << "4. Изменить состояние с трубы" << endl;
	cout << "5. Вывести информацию" << endl;
	cout << "6. Сохранить в файл" << endl;
	cout << "7. Обновить компрессорную станцию" << endl;
	cout << "0. Выход" << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	cs c;
	truba t;
	int i;
	while (1) {
		cout << "Выберите действие:" << endl;
		PrintMenu();
		cin >> i;
		switch (i)
		{
		case 1:
			t = load_from_fileT();
			c = load_from_fileC();
			break;
		case 2: 
			t = create_truba();
			break;
		case 3:
			c = create_cs();
			break;
		case 4:
			change_status(t.repair);
			break;
		case 5:
			write_truba_info(t);
			write_cs_info(c);
			break;
		case 6:
			save_to_fileT(t);
			save_to_fileC(c);
			break;
		case 7:
			cout << "\t Выберите действие:" << endl;
			cout << "\t 1. Начало работы" << endl;
			cout << "\t 2. Прекращение работы" << endl;
			cout << "\t 0. Назад" << endl;
			cin >> i;
			switch (i)
			{
			case 1:
				continue_work(c);
				break;
			case 2:
				stop_work(c);
				break;
			case 0:
				break;
			default:
				cout << "Выберите действие: " << endl;
				break;
			}
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "Выберите действие: " << endl;
			break;
		}

	}
}

