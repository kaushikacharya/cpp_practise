#ifndef Dictionary_HPP
#define Dictionary_HPP

//#include <iostream>
#include <string>
#include <set>
#include <vector>

namespace ds
{
	class Dictionary
	{
	public:
		Dictionary(const char* dictFile);
		void operator()();
	public:
		static void convertToLowerCase(std::string& str);
	public:
		//utils
		std::size_t size();
		const std::set<std::string>& dictWords() const;
		// http://msdn.microsoft.com/en-us/library/2s2d2tez%28v=vs.80%29.aspx  C2662
		// This error can be caused by invoking a non-const member function on a const object. 
	private:
		const char* dictFile_;
		std::set<std::string> dictWords_;
	};
}

#endif