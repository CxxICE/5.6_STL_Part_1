#include <iostream>
#include <set>
#include <string>


int readNumber(std::string question)
{
	std::string read;
	size_t idx;
	int number;
	do
	{
		std::cout << question << std::endl;
		try
		{
			std::getline(std::cin, read);
			number = std::stoi(read, &idx);
			if (idx < read.length())
			{
				std::cout << "Вы ввели нечисловое значение!\n";
			}
			else
			{
				break;
			}
		}
		catch (std::invalid_argument)
		{
			std::cout << "Вы ввели нечисловое значение!\n";
		}
		catch (std::out_of_range)
		{
			std::cout << "Введенное значение превышает границы int!\n";
		}
	} while (true);
	return number;
}


int main()
{
	setlocale(LC_ALL, "RU");
	std::string question;

	//Ввод количества элементов
    question = "Введите количество элементов:";
	int count;
	do
	{
		count = readNumber(question);
		if (count <= 0)
		{
			std::cout << "Значение должно быть больше нуля!\n";
		}
		else
		{
			break;
		}

	} while (true);
	

	//Ввод значений элементов	
	std::set<int,std::greater<int>> s;//Множество упорядоченное по убыванию
	
	for (int i = 0; i < count; ++i)
	{
		question = "Введите " + std::to_string(i) + " элемент:";
		int tmp = readNumber(question);		
		s.insert(tmp);		
	}

	//Вывод на экран
	std::cout << "[OUT]: " << std::endl;
	for (const auto &el : s)
	{
		std::cout << el << std::endl;
	}
}