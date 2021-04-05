#include <iostream>
#include "HashTable.cpp"

using namespace std;
int main() {
    HashTable h(15, 80);
    Game a = Game("Aario", "Plat0", "21.22.22", "EA0");
    Game a1 = Game("Aario", "Plat0", "21.22.22", "EA0");
    string name = a.name;
	string name1 = a1.name;
	for (size_t i = 0; i <= 10; i++)
	{
		name[0]+=2;
		name[2] -= 2;
		a.setName(name);
		h.AddHash(a);
		name1[0]+=1;
		name1[2] -= 1;
		a1.setName(name1);
		h.AddHash(a1);
		
//		cout << "Add" << a << endl;
	//	cout << h;
		
	}
	cout << "------------------" << endl;
	cout << h;
	
//	h.DelHash(a);
//	cout << "DEL" << a << endl;
//	cout << h;
	for (size_t i = 0; i < 10; i++)
	{
		name[0]-=4;
		name[2] += 4;
		a.setName(name);
	h.DelHash(a);
//		cout << "DEL" << a << endl;
	//	cout << h;
	}
    
 //   cout << h;
	//name = a1.name;
	for (size_t i = 0; i <= 10; i++)
	{
		name[0]+=2;
		name[2] -= 2;
		a1.setName(name);
		h.AddHash(a1);
//		cout << "Add" << a << endl;
		//	cout << h;
		
	}
	cout << "------------------" << endl;
	cout << h;


    return 0;
}

