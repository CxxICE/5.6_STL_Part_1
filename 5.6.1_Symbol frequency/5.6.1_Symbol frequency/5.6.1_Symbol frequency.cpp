#include <iostream>
#include <string>
#include <map>


int main()
{
	setlocale(LC_ALL, "RU");
    
	std::string str = "Hello world!!";
	std::map<int, char> m;
	std::multimap<int, char, std::greater<int>> mm;
	
	std::cout << "[IN]: " << str << std::endl;
	{
		int i = 0;
		char letter;
		int quantity;
		while (letter = str[i])									//запись букв и их кол-ва в map для удаления дубликатов key = letter
		{
			quantity = std::count(&str[0], &str[str.length()], letter);
			m.emplace(std::make_pair(letter, quantity));
			++i;
		}
	}
	
	for (const auto &[letter, quantity] : m)					//вставка в multimap с key = quantity для сортировки по убыванию кол-ва
	{
		mm.emplace(std::make_pair(quantity,letter));
	}

	std::cout << "[OUT]:\n";									//вывод на экран
	for (const auto &el : mm)
	{
		std::cout << el.second << ": " << el.first << "\n";
	}

}