#ifndef STEM_HPP
#define STEM_HPP

#include <string>

namespace ds
{
	class Stem
	{
	public:
		Stem(const std::string str);
		void operator()();
		std::string stem();
	private:
		std::size_t vc_measure(std::size_t stem_size);
		bool isVowel(std::size_t pos);
		bool isVowelPresent(std::size_t stem_size);
	private:
		void step2();
		void step3();
		void step4();
	private:
		std::string stem_;
		std::string input_str_;
	};
}

#endif