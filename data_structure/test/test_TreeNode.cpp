#include "..\TreeNode.hpp"
#include <string>

int main(int argc, char* argv[])
{
	using namespace ds;
	std::size_t test_case = 0;

	switch (test_case)
	{
	case 0:
		TreeNode<Version::V0,std::string> treeNode0("my");
		TreeNode<Version::V0,std::string> treeNode1("name",NULL,NULL,&treeNode0);
		treeNode0.setLeft(&treeNode1);
		break;
	}

	return 0;
}