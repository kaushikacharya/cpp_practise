#include "..\ListNode.hpp"
#include <iostream>
#include <string>

int main( int argc, char* argv[] )
{
	using namespace ds;

	std::size_t test_case = 2;

	switch (test_case)
	{
	case 0:
#if 0
		ListNode<Version::V0,int> node0(89);
		ListNode<Version::V0,int> node1(88,&node0);
		//ListNode<Version::V0,char> node2('g',&node1); //should give compile error

		std::cout << "next of node1: " << (node1.next())->item() << std::endl;
		//TBD: find out why (node1.next())->item() is wrong?
#endif
		break;
	case 1:
#if 0
		ListNode<Version::V0,std::string> node0("run");
		ListNode<Version::V0,std::string> node1("walk",&node0);
		std::cout << "next of node1: " << (node1.next())->item() << std::endl;
#endif
		break;
    case 2:
        ListNode<Version::V1,std::string> node0("run");
        ListNode<Version::V1,std::string> node1("walk",&node0);
        std::cout << "prev of node1: " << (node1.prev())->item() << std::endl;
        std::cout << "next of node0: " << (node0.next())->item() << std::endl;
        break;
	}

	return 0;
}