#include "Graph.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <queue>

void compute_word_transformation(std::vector<std::string>& vecWords, std::string start_word, std::string end_word, std::vector<std::string>& word_transformation);
template<typename T>
void populate_adjacent_edges(ds::Graph<T>& G, std::vector<std::string>& vecWords,int src);
int compute_edit_distance(std::string str1, std::string str2);
void textReader(const char* textFile, std::vector<std::string>& vecWords);
void tokenize(std::string& line,std::vector<std::string>& lineSplit);

int main( int argc, char* argv[] )
{
	std::vector<std::string> vecWords;
	std::cout << "input: " << argv[1] << std::endl;
	textReader(argv[1],vecWords);
	std::string start_word = argv[2];
	std::string end_word = argv[3];
	std::vector<std::string> word_transformation;
	compute_word_transformation(vecWords,start_word,end_word,word_transformation);
	//now out the transformation
	if (word_transformation.empty())
	{
		std::cout << "No transformation found" << std::endl;
	}
	else
	{
		for (std::vector<std::string>::iterator it = word_transformation.begin(); it != word_transformation.end(); ++it)
		{
			std::cout << *it << std::endl;
		}
	}
	return 0;
}

//TBD: use const
void compute_word_transformation(std::vector<std::string>& vecWords, std::string start_word, std::string end_word, std::vector<std::string>& word_transformation)
{
	using namespace ds;
	Graph<int> G;
	
	for (int i=0; i < vecWords.size(); ++i)
	{
		G.add_vertex(i);
	}

	std::vector<std::string>::iterator it = std::find(vecWords.begin(), vecWords.end(), start_word);
	int ind_start_word = std::distance(vecWords.begin(),it);
	it = std::find(vecWords.begin(), vecWords.end(), end_word);
	int ind_end_word = std::distance(vecWords.begin(),it);

	//check if the two words are having same size

	//now do bfs traversal.
	// Here we populate the edges on a need basis.
	std::vector<int> predecessorInPath;
	predecessorInPath.reserve(vecWords.size());
	for (int i=0; i < vecWords.size(); ++i)
	{
		predecessorInPath.push_back(ind_start_word); //dummy assignment
	}

	bool flag_transformation = false;
	std::queue<int> Q;
	G.setExplored(ind_start_word);
	Q.push(ind_start_word);
	while (!Q.empty())
	{
		int front_elem = Q.front();
		Q.pop();
		if (front_elem == ind_end_word)
		{
			flag_transformation = true;
			break;
		}
		populate_adjacent_edges(G,vecWords,front_elem);
		std::set<int> adjacentVertices = G.adjacentVertices(front_elem);
		
		for (std::set<int>::iterator adjIt = adjacentVertices.begin(); adjIt != adjacentVertices.end(); ++adjIt)
		{
			if (G.isExplored(*adjIt) == false)
			{
				predecessorInPath[*adjIt] = front_elem;
				G.setExplored(*adjIt);
				Q.push(*adjIt);
			}
		}
	}

	if (flag_transformation)
	{
		std::vector<int> predecessorVec;
		predecessorVec.push_back(ind_end_word);
		while (predecessorInPath[predecessorVec.back()] != ind_start_word)
		{
			int predecessor = predecessorInPath[predecessorVec.back()];
			predecessorVec.push_back(predecessor);
		}
		predecessorVec.push_back(ind_start_word);

		for (std::vector<int>::reverse_iterator rIt = predecessorVec.rbegin(); rIt != predecessorVec.rend(); ++rIt)
		{
			word_transformation.push_back(vecWords[*rIt]);
		}

		int gh = 0;
	}

	int gh = 0;
}

template<typename T>
void populate_adjacent_edges(ds::Graph<T>& G, std::vector<std::string>& vecWords, int src)
{
	for (int i = 0; i < vecWords.size(); ++i)
	{
		if (i == src)
		{
			continue;
		}
		int edit_distance = compute_edit_distance(vecWords[src],vecWords[i]);
		if (edit_distance == 1)
		{
			G.add_edge(src,i);
		}
	}
}

int compute_edit_distance(std::string str1, std::string str2)
{
	//currently only handles substitution
	//assumption: str1,str2 having same size
	if (str1.size() != str2.size())
	{
		return std::max(str1.size(),str2.size());
	}

	int edit_distance = 0;
	for (int i = 0; i < str1.size(); ++i)
	{
		if (str1[i] != str2[i])
		{
			++edit_distance;
		}
	}
	return edit_distance;
}

void textReader(const char* textFile, std::vector<std::string>& vecWords)
{
	std::ifstream textFileStream;
	textFileStream.open(textFile);
	assert(textFileStream.is_open() && "invalid input text file");

	int countLine = 0;
	while (!textFileStream.eof())
	{
		std::string line;
		std::getline(textFileStream,line);
		if (!line.empty())
		{
			std::vector<std::string> lineSplit;
			tokenize(line,lineSplit);
			if (!lineSplit.empty())
			{
				vecWords.push_back(lineSplit[0]);
			}
		}
		++countLine;
	}

	textFileStream.close();
}

void tokenize(std::string& line,std::vector<std::string>& lineSplit)
{
	if (line == "")
	{
		return;
	}
	std::string::size_type start = 0;
	std::string::size_type end = 0;
	while(end < line.npos)
	{
		start = line.find_first_not_of(' ',end);
		end   = line.find_first_of(' ',start);
		if (start == end)
		{
			break;
		}
		lineSplit.push_back(line.substr(start,(end-start)));
	}
}