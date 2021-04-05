#include "HashTable.h"
using namespace std;
HashTable::HashTable(int max_size, unsigned int resize_occupancy) {
    this->max_size = max_size;
    if (max_size < 10) max_size = 10;
    table = new Game[max_size];
    this->resize_occupancy = resize_occupancy;
    occupancy = 0;

    is_use = new int[max_size];
    for (int i = 0; i < max_size; i++) {
        is_use[i] = 0;
    }
}

HashTable::~HashTable() {
    delete[] table;
    delete[] is_use;
}


int HashTable::HashF1(size_t key) const {
    return (int)key% max_size;
}

int HashTable::HashF2(int h1, int n = 0) const {
    int h2 = (h1 + c * n + d * n * n) % max_size;
    return h2;
}

int HashTable::AddHash(Game cell) {
    int count = 0;
    int h1 = HashF1(cell.key);
    int h2 = HashF2(h1, count);
    bool flag = false;
    int flagH = -1;

    while ((is_use[h2] == 1 || is_use[h2] == 2) && count < max_size)
    { // посмотрели на наличие этой игры в таблице
        if (is_use[h2] == 2)
        { // если нашли пустое место, после удаления, то занесём туда
            flag = h2;
            flag = true;
        }
        if (is_use[h2] == 1 && cell == table[h2])
        {
            cout << "Данная игра уже добавленна! ";
            cout << cell << endl;
            return 0;
        }

        count++;
        h2 = HashF2(h1, count);
    }

    if (count == max_size || ((float)occupancy / (float)max_size) * 100 >= (float)resize_occupancy)
    {
        ReSize(); // увеличиваем на N
        AddHash(cell);
    }
    else
    {
        occupancy++; // считаем добавление;
        if (flag)
        {
            is_use[flagH] = 1;
            table[flagH] = cell;
            return 1;
        }
        else
        {
            is_use[h2] = 1;
            table[h2] = cell;
            return 1;
        }
    }
}

int HashTable::DelHash(Game cell)
{
    int count = 0;
    int h1 = HashF1(cell.key);
    int h2 = HashF2(h1, count);

    while (is_use[h2] != 0)
    {
        if (is_use[h2] == 1 && cell == table[h2])
        {

            occupancy--;
            is_use[h2] = 2;
            if (((float)occupancy / (float)max_size) * 100 < (float)resize_occupancy - 10)
            { //???
                ReHash();
            }
            return 1; // найдено, удалено (состоние 2)
        }
        count++;
        h2 = HashF2(h1, count);
    }
    return 0; // не найдено
}

bool HashTable::SearchCell(Game cell)
{
    int count = 0;
    int h1 = HashF1(cell.key);
    int h2 = HashF2(h1, count);

    while (is_use[h2] != 0)
    {

        if (is_use[h2] != 2 && (cell == table[h2]))
        {

            return true; // найдено
        }
        count++;
        h2 = HashF2(h1, count);
    }
    return false; // не найдено
}



int HashTable::ReSize()
{ // расширение
    this->occupancy = 0;

    Game *helpTable = table; // запомнили ссылки на наши таблицы
    int *help_is_use = is_use;

    int help_max_size = max_size; // расширенеи размера
    this->max_size *= 2;

    this->is_use = new int[max_size]; // создание новой таблицы
    this->table = new Game[max_size];

    for (int i = 0; i < max_size; i++)
    {
        is_use[i] = 0;
    }

    for (int i = 0; i < help_max_size; i++)
    {
        if (help_is_use[i])
        {
            AddHash(helpTable[i]);
        }
    }

    // удалить прошлую таблицу
    delete[] help_is_use;
    delete[] helpTable;
}

int HashTable::ReHash()
{ // попытка сужения
    this->occupancy = 0;

    Game *helpTable = table; // запомнили ссылки
    int *help_is_use = is_use;

    int help_max_size = max_size;
    this->max_size /= 2;
    if (max_size < 10) max_size = 10;

    this->is_use = new int[max_size];
    this->table = new Game[max_size];

    for (int i = 0; i < max_size; i++)
    {
        is_use[i] = 0;
    }

    for (int i = 0; i < help_max_size; i++)
    {
        if (help_is_use[i] == 1)
        {
            AddHash(helpTable[i]);
        }
    }

    // удалить прошлую таблицу
    delete[] help_is_use;
    delete[] helpTable;
}

ostream& operator<<(ostream& out, const HashTable& ht)
{
	out << "---------------------------------Hash Table---------------------------------" << endl;
	for (int i = 0; i < ht.max_size; i++)
	{
		out << i + 1 << ". ";
		if (ht.is_use[i] == 1)
		{
			out << ht.table[i] << endl;
		}
		else if (ht.is_use[i] == 0)
		{
			out << "-" << endl;
		}
		else
		{
			out << "Del" << endl;
		}
	}
	out << endl;
	return out;
	
}
