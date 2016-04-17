#include "Stem.hpp"

// http://snowball.tartarus.org/algorithms/porter/stemmer.html

// http://www.comp.lancs.ac.uk/computing/research/stemming/Links/porter.htm
// A consonant is a letter other than A, E, I, O, U and Y preceded by a consonant.
// e.g. 'boy' : consonants are 'b' 'y'
// e.g. 'try' : consonants are 't' 'r'
namespace ds
{
	Stem::Stem(const std::string input_str)
		: input_str_(input_str)
	{
	}

	void Stem::operator()()
	{
		std::size_t str_len = input_str_.length();
		stem_ = input_str_;
		
		if (str_len == 0)
		{
			return;
		}

		if (stem_[str_len-1] == 's')
		{
			//step 1a
			if ( (str_len > 4) && (stem_.compare(str_len-4,4,"sses") == 0) )
			{
				std::size_t rep_str_len = 4;
				stem_.replace(str_len-rep_str_len,rep_str_len,"ss");
				str_len -= 2;
			}
			else if ( (str_len > 3) && (stem_.compare(str_len-3,3,"ies") == 0) )
			{
				std::size_t rep_str_len = 3;
				stem_.replace(str_len-rep_str_len,rep_str_len,"i");
				str_len -= 2;
			}
			else if ( (str_len > 2) && (stem_.compare(str_len-2,2,"ss") == 0) )
			{
				//caress    ->  caress
			}
			else if ( (str_len > 1) && (stem_.compare(str_len-1,1,"s") == 0) )
			{
				std::size_t rep_str_len = 1;
				stem_.replace(str_len-rep_str_len,rep_str_len,"");
				str_len -= rep_str_len;
			}
		}

		//step 1b
		bool further_processing_step1b(false);
		if ( (str_len > 3) && (stem_.compare(str_len-3,3,"eed") == 0) )
		{
			if (vc_measure(str_len-3) > 0)
			{
				std::size_t rep_str_len = 3;
				stem_.replace(str_len-rep_str_len,rep_str_len,"ee");
				str_len -= 1;
			}
		}
		else if ( (str_len > 2) && (stem_.compare(str_len-2,2,"ed") == 0) )
		{
			if (isVowelPresent(str_len-2))
			{
				std::size_t rep_str_len = 2;
				stem_.replace(str_len-rep_str_len,rep_str_len,"");
				str_len -= rep_str_len;
				further_processing_step1b = true;
			}
		}
		else if ( (str_len > 3) && (stem_.compare(str_len-3,3,"ing") == 0) )
		{
			if (isVowelPresent(str_len-3))
			{
				std::size_t rep_str_len = 3;
				stem_.replace(str_len-rep_str_len,rep_str_len,"");
				str_len -= rep_str_len;
				further_processing_step1b = true;
			}
		}

		if (further_processing_step1b)
		{
			if ( (str_len > 1) )
			{
				if ( (stem_.compare(str_len-2,2,"at") == 0) ||
					(stem_.compare(str_len-2,2,"bl") == 0) ||
					(stem_.compare(str_len-2,2,"iz") == 0) )
				{
					stem_.append("e");
					++str_len;
				}
				else if ( !( (stem_[str_len-1] == 'l') ||
					(stem_[str_len-1] == 's') ||
					(stem_[str_len-1] == 'z') ) && (stem_[str_len-2] == stem_[str_len-1])  )
				{
					std::size_t rep_str_len = 1;
					stem_.replace(str_len-rep_str_len,rep_str_len,"");
					str_len -= rep_str_len;
				}
				//TBD: one more case need to be done
				//     		fil(ing) 		-> 		file 
			}
		}

		//step 1c
		if ( (stem_[str_len-1] == 'y') && isVowelPresent(str_len-1) )
		{
			//happy 		-> 		happi 
			std::size_t rep_str_len = 1;
			stem_.replace(str_len-rep_str_len,rep_str_len,"i");
		}

		step2();

	}

	
	std::string Stem::stem()
	{
		return stem_;
	}

	void Stem::step2()
	{
		std::size_t str_len = stem_.length();

		if (str_len < 4)
		{
			return;
		}
		//Hint: check the penultimate char
		//source: snowball webpage 
		switch (stem_[str_len-2])
		{
		case 'a':
			if (str_len > 6)
			{
				if (stem_.compare(str_len-6,6,"tional") == 0)
				{
					if ((str_len > 7) && (stem_[str_len-7] == 'a'))
					{
						stem_.replace(str_len-7,7,"ate");
					}
					else
					{
						stem_.replace(str_len-2,2,"");
					}
				}
			}
			break;
		case 'c':
			if (str_len > 4)
			{
				if (stem_.compare(str_len-4,4,"enci") == 0)
				{
					stem_.replace(str_len-1,1,"e");
				}
				else if (stem_.compare(str_len-4,4,"anci") == 0)
				{
					stem_.replace(str_len-1,1,"e");
				}
			}
			break;
		}

	}

	void Stem::step3()
	{
		std::size_t str_len = stem_.length();
	}

	void Stem::step4()
	{
		std::size_t str_len = stem_.length();
	}



	//compute the VC measure for str[0:(stem_size-1)]
	std::size_t Stem::vc_measure(std::size_t stem_size)
	{
		std::size_t measure = 0;
		std::size_t pos = 0;

		bool isVowelPrevChar = false;
		while (pos < stem_size)
		{
			bool isVowelCurChar = isVowel(pos);
			if ( !isVowelCurChar && isVowelPrevChar )
			{
				++measure;
			}
			++pos;
		}

		return measure;
	}

	//search if vowel present in str[0:(stem_size-1)]
	bool Stem::isVowelPresent(std::size_t stem_size)
	{
		bool flag(false);
		std::size_t pos = 0;

		while (pos < stem_size)
		{
			if (isVowel(pos))
			{
				flag = true;
				break;
			}
			++pos;
		}

		return flag;
	}

	bool Stem::isVowel(std::size_t pos)
	{
		bool flag;
		switch (stem_[pos])
		{
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u':
			flag = true;
			break;
		case 'y':
			if (pos > 0)
			{
				flag = !isVowel(pos-1);
			}
			else
			{
				flag = false;
			}
			break;
		default:
			flag = false;
		}

		return flag;
	}

}