#include <iostream>
#include <unordered_map>
#include <string>
#include "TUnorderedMap.h"
#include "Timer.h"

using namespace std;

int main()
{
	unordered_map<int, int> kl;
	{
		Timer t1;
		kl.insert(pair<int, char>(1,'a'));
		kl.insert(pair<int, char>(2,'b'));
		kl.insert(pair<int, char>(3,'c'));

	}
	kl.find(1);
	TUnorderedMap<int, char> map;
	{
		Timer t2;
		map.InsertElement(pair<int, char>(1, 'a'));
		map.InsertElement(pair<int, char>(2, 'b'));
		map.InsertElement(pair<int, char>(3, 'c'));
	}
	
	map.Print();
	cout << map[3].first << " " << map[3].second << " " << map.isEmpty() << endl;

	auto a = map.Find(2);
	cout << a->Element.first << " " << a->Element.second << endl;

	map.Clear();	
	map.InsertElement(pair<int, char>(1, 'a'));
	map.Print();

	for (MapElement<pair<int,char>> iter : map)
	{
		cout << iter.Element.first << iter.Element.second << iter.isHashed << endl;
	}
	
}