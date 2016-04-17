#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

bool const READ_FROM_FILE = true;

template<typename T>
class Edge
{
public:
	Edge(T source, T target);
	~Edge();
public:
	T source();
	T target();
private:
	T source_;
	T target_;
};
//---------------------
template<typename T>
class Graph
{
public:
	Graph();
	~Graph();
public:
	void read_input(std::ifstream& pFile);
	T compute_completion_time();
private:
	void tokenize(std::string strLine, std::vector<std::string>& vecToken);
	void record_task(const std::vector<std::string>& vecToken);
	void populate_graph();
	void dfs_traversal(T vertex);
private:
	std::map<char,T> mapTaskIndex_;
	std::vector<T> vecTaskTime_;
	std::vector<Edge<char> > vecEdge_;
	std::vector<std::vector<T> > adjList_;
	std::vector<bool> vecVisited_;
	std::vector<T> vecVertexInFinishOrder_;
	T order_;
};
//----------------------
template<typename T>
Edge<T>::Edge(T source, T target)
: source_(source)
, target_(target)
{}
template<typename T>
Edge<T>::~Edge()
{}
template<typename T>
T Edge<T>::source()
{
	return source_;
}
template<typename T>
T Edge<T>::target()
{
	return target_;
}
//----------------------
template<typename T>
Graph<T>::Graph()
{
	vecTaskTime_.reserve(26); //26 - upper limit
}
template<typename T>
Graph<T>::~Graph()
{}
template<typename T>
void Graph<T>::read_input(std::ifstream& pFile)
{
	if (READ_FROM_FILE)
	{
		while (!pFile.eof())
		{
			std::string strLine;
			std::getline(pFile,strLine);
			//Now split the string using space as delimiter
			std::vector<std::string> vecToken;
			tokenize(strLine,vecToken);
			record_task(vecToken);
			int gh = 0;
		}
	}

	populate_graph();
}
template<typename T>
void Graph<T>::tokenize(std::string strLine, std::vector<std::string>& vecToken)
{
	std::string::size_type beginPos = 0;
	std::string::size_type endPos = 0;
	
	while (endPos != strLine.npos)
	{
		beginPos = strLine.find_first_not_of(" ",endPos);
		endPos = strLine.find_first_of(" ",beginPos);
		vecToken.push_back(strLine.substr(beginPos,endPos-beginPos));
	}
	int gh = 0;
}

template<typename T>
void Graph<T>::record_task(const std::vector<std::string>& vecToken)
{
	char task = vecToken[0][0];
	//char task = static_cast<char>(vecToken[0].c_str());
	T time = atoi(vecToken[1].c_str());
	mapTaskIndex_[task] = vecTaskTime_.size();
	vecTaskTime_.push_back(time);
	//Now store the edges if present in this record
	if (vecToken.size() > 2)
	{
		for (std::string::size_type char_i = 0; char_i != vecToken[2].size(); ++char_i)
		{
			Edge<char> edge(vecToken[2][char_i],task);
			vecEdge_.push_back(edge);
		}
	}
	
	int gh = 0;
}

template<typename T>
void Graph<T>::populate_graph()
{
	//initialize
	adjList_.reserve(vecTaskTime_.size());
	vecVisited_.reserve(vecTaskTime_.size());
	vecVertexInFinishOrder_.reserve(vecTaskTime_.size());
	for (std::vector<T>::iterator it = vecTaskTime_.begin(); it != vecTaskTime_.end(); ++it)
	{
		adjList_.push_back(std::vector<T>());
		vecVisited_.push_back(false);
		vecVertexInFinishOrder_.push_back(std::numeric_limits<T>::max());
	}

	for (std::vector<Edge<char> >::iterator it = vecEdge_.begin(); it != vecEdge_.end(); ++it)
	{
		//Edge<T> edge(mapTaskIndex_[(*it).source()], mapTaskIndex_[(*it).target()]);
		adjList_[mapTaskIndex_[(*it).source()]].push_back(mapTaskIndex_[(*it).target()]);
	}
}

template<typename T>
T Graph<T>::compute_completion_time()
{
	order_ = vecTaskTime_.size();
	for (std::vector<T>::iterator it = vecTaskTime_.begin(); it != vecTaskTime_.end(); ++it)
	{
		T task = std::distance(vecTaskTime_.begin(),it);
		if (!vecVisited_[task])
		{
			dfs_traversal(task);
		}
	}

	T total_time = 0;
	for (std::vector<T>::iterator taskIt = vecVertexInFinishOrder_.begin(); taskIt != vecVertexInFinishOrder_.end(); ++taskIt)
	{
		total_time += vecTaskTime_[*taskIt];
	}

	return total_time;
}

template<typename T>
void Graph<T>::dfs_traversal(T vertex)
{
	if (vecVisited_[vertex])
	{
		return;
	}
	for (std::vector<T>::iterator it = adjList_[vertex].begin(); it != adjList_[vertex].end(); ++it)
	{
		if (!vecVisited_[*it])
		{
			dfs_traversal(*it);
		}
	}
	vecVisited_[vertex] = true;
	--order_;
	vecVertexInFinishOrder_[order_] = vertex;
}

int main(int argc, char* argv[])
{
	/*
	int n = -5;
	std::cout << n/2 << std::endl;
	*/
	std::ifstream pFile;
	if (READ_FROM_FILE)
	{
		pFile.open("D:/cpp_practise/online_judge/uva/452_project_scheduling_input.txt",std::ios::in);
	} 
	Graph<unsigned int> graph;
	graph.read_input(pFile);

	if (READ_FROM_FILE)
	{
		pFile.close();
	}
	std::cout << graph.compute_completion_time() << std::endl;

	int gh = 0;
}

/*
http://online-judge.uva.es/board/viewtopic.php?f=5&t=6272&p=214193
*/