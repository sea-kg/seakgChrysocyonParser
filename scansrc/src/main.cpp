#include <iostream>
#include "../seakgChrysocyonParser/seakgChrysocyonParser.h"



int main(int argc, char *argv[]) {
	if(argc != 4) {
		std::cout << argv[0] << " <folder_with_sources> <project_name> <folder_for_output_xml> \n\n";
	};
};
