#include <iostream>

#include "seakgChrysocyonParser.h"
#include "seakgExampleParser.h"


//class seakgChrysocyon::seakgChrysocyonContainer<char>;


int main()
{
	seakgExampleReader<char> reader; 
	
	std::string str = "Hallo vasy! \"Me\\\"ine\" Telefonnummer ist 676767."; 
	
	reader.setString(str);
	
	seakgChrysocyon::seakgChrysocyonContainer<char> *container;

	container = new seakgChrysocyon::seakgChrysocyonContainer<char>();

	//char ch = 0x33;
	//container->Push(ch);

	//seakgChrysocyon::seakgChrysocyonParser<char> parser();//();
	//parser = new seakgChrysocyon::seakgChrysocyonParser<char>();



	//parser->AddPuppy()

	std::cout << "\n";
	int sch = 0;
	while(!reader.Eof())
	{
		char ch = reader.GetNextElement();
		container->Push(ch);
		std::cout << ch;
		sch++;
	}
	std::cout << "\n\n";

	seakgChrysocyon::seakgChrysocyonContainer<char> *container2;
	container2 = new seakgChrysocyon::seakgChrysocyonContainer<char>();
	
	 
	container->PushAllTo(container2);
	
	
	std::cout << "container : ";
	for(int i=0; i<sch; i++)
	{
		char ch1 = container->Pop();
		std::cout << ch1;
	}

	std::cout << "\n\n";
	
	std::cout << "container2 : ";
	for(int i=0; i<sch; i++)
	{
		char ch1 = container2->Pop();
		std::cout << ch1;
	}

	std::cout << "\n\n";
	
	return 0;
};
