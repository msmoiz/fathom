#include "interpreter.h"

#include <iostream>
#include <stdexcept>

namespace fathom
{
	void Interpreter::interpret(std::string&& source)
	{
		for (auto it = source.begin(); it != source.end(); ++it)
		{
			static const char commands[] = 
			{
				'>', '<', '+', '-',
				'.', ',', '[', ']'
			};

			if (std::find(std::begin(commands), std::end(commands), *it) 
				== std::end(commands))
			{
				continue;
			}

			const char command = *it;
			try
			{
				switch (command)
				{
				case '>':
					move_right();
					break;
				case '<':
					move_left();
					break;
				case '+':
					increment();
					break;
				case '-':
					decrement();
					break;
				case '.':
					write();
					break;
				case ',':
					read();
					break;
				case '[':
					counter_ += jump_if_zero(it, source.end());
					break;
				case ']':
					counter_ -= jump_unless_zero(it, source.begin());
					break;
				default:
					break;
				}
			}

			catch (std::out_of_range& e)
			{
				std::cerr << "Failure with command '" << command << "' at position [" << counter_ << "]: " << e.what() << " ";
				break;
			}

			catch (std::logic_error& e)
			{
				std::cerr << "Failure with command '" << command << "' at position [" << counter_ << "]: " << e.what() << " ";
				break;
			}

			++counter_;
		}
	}

	void Interpreter::move_right()
	{
		if (cursor_ + 1 == data_.size())
		{
			data_.emplace_back(0);
		}

		++cursor_;
	}

	void Interpreter::move_left()
	{
		if (cursor_ == 0)
		{
			throw std::out_of_range("Array index less than 0.");
		}
		
		--cursor_;
	}

	void Interpreter::increment()
	{
		++data_[cursor_];
	}

	void Interpreter::decrement()
	{
		--data_[cursor_];
	}

	void Interpreter::write()
	{
		// need to cast to int, because uint8_t output overload converts output to ASCII
		// instead of printing raw integral value
		std::cout << static_cast<int>(data_[cursor_]) << " ";
	}

	void Interpreter::read()
	{
		std::cin >> data_[cursor_];

		if (std::cin.fail())
		{
			throw std::logic_error("Bad read.");
		}
	}

	unsigned Interpreter::jump_if_zero(std::string::iterator& it, std::string::iterator&& end)
	{
		unsigned moves{0};
		
		if (data_[cursor_] == 0)
		{
			unsigned nested_scopes{0};
			for (++it; it != end; ++it, ++moves)
			{
				if (*it == '[')
				{
					++nested_scopes;
				}

				else if (*it == ']')
				{
					if (!nested_scopes)
					{
						--it;
						break;
					}

					--nested_scopes;
				}
			}

			if (it == end)
			{
				throw std::logic_error("Missing matching closing bracket.");
			}
		}

		return moves;
	}

	unsigned Interpreter::jump_unless_zero(std::string::iterator& it, std::string::iterator&& begin)
	{
		unsigned moves{0};
		bool success{false};

		if (data_[cursor_] != 0)
		{
			unsigned nested_scopes{0};
			for (--it; it >= begin; --it, ++moves)
			{
				if (*it == ']')
				{
					++nested_scopes;
				}

				else if (*it == '[')
				{
					if (!nested_scopes)
					{
						success = true;
						--it;
						break;
					}

					--nested_scopes;
				}
			}

			if (!success)
			{
				throw std::logic_error("Missing matching opening bracket.");
			}
		}

		return moves;
	}
}
