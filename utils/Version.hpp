#ifndef VERSION_HPP
#define VERSION_HPP

namespace ds
{
	struct Version
	{
	public:
		enum Enum
		{
			V0,
			V1,
			V2,
			V3
		};
	};

	struct IterRecur
	{
	public:
		enum Enum
		{
			Iterative,
			Recursive
		};
	};

	struct MinMax
	{
	public:
		enum Enum
		{
			MIN,
			MAX,
		};
	};
}

#endif