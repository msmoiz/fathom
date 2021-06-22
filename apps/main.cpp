#include <iostream>
#include <fstream>

#include "fathom/interpreter.h"

using fathom::Interpreter;

/**
 * This program reads a source file authored in
 * the illustrious Brainfuck language and interprets
 * its commands.
 *
 * The name of the source file should be passed as
 * the only argument.
 */
int main(int argument_count, const char** arguments)
{
	if (argument_count < 2)
	{
		std::cerr << "Insufficient arguments. No source file specified." << std::endl;
		return EXIT_FAILURE;
	}
	
	std::ifstream source_file(arguments[1]);
	if (!source_file.is_open())
	{
		std::cerr << "Failed to open file at: " << arguments[1] << "." << std::endl;
		return EXIT_FAILURE;
	}

	std::string source, line;
	while (std::getline(source_file, line))
	{
		source.append(line);
	}
	
	Interpreter interpreter;
	interpreter.interpret(std::move(source));
}
