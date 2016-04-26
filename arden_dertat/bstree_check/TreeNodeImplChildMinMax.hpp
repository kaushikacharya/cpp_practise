#ifndef TreeNode_Impl_Child_Min_Max_HPP
#define TreeNode_Impl_Child_Min_Max_HPP

#include "../../data_structure/impl/TreeNodeImpl0.hpp"
#include <algorithm>
/*
Each node keeps min and max of the sub-tree rooted at that node including the node itself.
*/
namespace ds
{
	template<typename T>
	class TreeNodeChildMinMax;

	template<typename T>
	class TreeNodeChildMinMax : public TreeNode<Version::V0,T>
	{
	public:
		TreeNodeChildMinMax(T item, TreeNodeChildMinMax<T>* left=NULL, TreeNodeChildMinMax<T>* right=NULL, TreeNodeChildMinMax<T>* parent=NULL);
	public:
		T getMin();
		T getMax();
		void setMin(T val);
		void setMax(T val);
	private:
		T min_;
		T max_;
	};

	template<typename T>
	TreeNodeChildMinMax<T>::TreeNodeChildMinMax(T item, TreeNodeChildMinMax<T>* left, TreeNodeChildMinMax<T>* right, TreeNodeChildMinMax<T>* parent)
		: TreeNode<Version::V0,T>(item,left,right,parent)
	{
		//we will populate min,max of subtree at each node as we do the BS Tree check
		/*
		if ((left == NULL) && (right == NULL) && (parent == NULL))
		{
			min_ = item;
			max_ = item;
		}
		else
		{
			if (left)
			{
				min_ = std::min(item, (*left).getMin());
				max_ = std::max(item, (*left).getMax());
			}
			else if (right)
			{
				min_ = std::min(item, (*right).getMin());
				max_ = std::max(item, (*right).getMax());
			}
			else // parent
			{
				min_ = item;
				max_ = item;
				// TBD: update parent's min/max value
				(*parent).getMin()
				
			}
		}
		*/
	}

	template<typename T>
	T TreeNodeChildMinMax<T>::getMin()
	{
		return min_;
	}

	template<typename T>
	T TreeNodeChildMinMax<T>::getMax()
	{
		return max_;
	}

	template<typename T>
	void TreeNodeChildMinMax<T>::setMin(T val)
	{
		min_ = val;
	}

	template<typename T>
	void TreeNodeChildMinMax<T>::setMax(T val)
	{
		max_ = val;
	}

}

#endif