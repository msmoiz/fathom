#pragma once

#include <string>
#include <vector>

namespace fathom
{
	/**
	 * The Interpreter class is responsible for
	 * consuming Brainfuck source and executing
	 * the corresponding commands.
	 */
	class Interpreter
	{
	public:

		/** Interpret a source to completion. */
		void interpret(std::string&& source);

	private:

		// Full list of commands.
		void move_right();			// move cursor right
		void move_left();			// move cursor left
		void increment();			// increment element under cursor
		void decrement();			// decrement element under cursor
		void write();				// write element under cursor to output
		void read();				// replace element under cursor with input 
		unsigned jump_if_zero(std::string::iterator& it, std::string::iterator&& end);			// jump to matching ] if zero (returns distance traveled)
		unsigned jump_unless_zero(std::string::iterator& it, std::string::iterator&& begin);	// jump to matching [ if not zero (returns distance traveled)
		
		std::vector<uint8_t> data_{0};
		decltype(data_.size()) cursor_{0};
		unsigned counter_{0};
	};
}
