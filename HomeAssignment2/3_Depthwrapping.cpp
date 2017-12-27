#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstdlib>

using namespace std;

template <typename T> class Graph;
template <typename T> class Node;
template <typename T> void Wrap(Graph <T> *graph, int(*function)(T &, unsigned), unsigned start, bool *visited, unsigned *created, unsigned *finished);

mutex m;


template <typename T> class Node
{
	friend class Graph <T>;
	friend void Wrap <T>(Graph <T> *graph, int(*function)(T &, unsigned), unsigned start, bool *visited, unsigned *created, unsigned *finished);

	T data;
	Graph <T> *Ancestor;
	vector <Node<T>*> Heir;

	Node(T d, Graph <T> *f)
	{
		data = d;
		Ancestor = f;
	}

	unsigned index()
	{
		for (int i = 0; i < Ancestor->v.size(); i++)
        {
			if (Ancestor->v[i] == this)
			{
				return i;
			}
		}
	}

	unsigned neighborPos(unsigned index)
	{
		for (int i = 0; i < Heir.size(); i++)
        {
			if (Heir[i] == Ancestor->v[index])
			{
				return i;
			}
		}
	}

};

template <typename T> class Graph
{
public:
	Graph()
	{}

	~Graph()
	{
		for (int i = 0; i < v.size(); i++)
        {
			delete v[i];
		}
		v.clear();
	}

	unsigned size()
	{
		return v.size();
	}

	unsigned push(T d, unsigned HeirsAmount = 0, ...)
	{
		Node <T> *newNode = new Node <T>(d, this);

		unsigned *ptr = &HeirsAmount;
		for (int i = 0; i < HeirsAmount; i++)
        {
			unsigned HeirsIndex = *(ptr + i + 1);
			if (HeirsIndex >= v.size())
			{
				exit(1);
			}
			else
			{
				newNode->Heir.push_back(v[HeirsIndex]);
				v[HeirsIndex]->Heir.push_back(newNode);
			}
		}
		v.push_back(newNode);
		return v.size();
	}

	T pop(unsigned index)
	{
		if (index >= v.size())
        {
			exit(1);
		}
		for (int i = 0; i < v[index]->Heir.size(); i++)
		{
			Node <T> *Heirs = v[index]->Heir[i];
			unsigned pos = Heirs->neighborPos(index);
			Heirs->Heir.erase(Heirs->Heir.begin() + pos);
		}
		T result = v[index]->data;
		delete v[index];
		v.erase(v.begin() + index);
		return result;
	}

	T &operator[] (unsigned index)
	{
		if (index >= v.size())
        {
			exit(1);
		}
		return v[index]->data;
	}

	bool check(unsigned Index_1, unsigned Index_2)
	{
		if (Index_1 >= v.size() || Index_2 >= v.size())
        {
			exit(1);
		}
		for (int i = 0; i < v[Index_1]->Heir.size(); i++)
        {
			if (v[Index_2] == v[Index_1]->Heir[i])
			{
				return true;
			}
		}
		return false;
	}

	bool link(unsigned Index_1, unsigned Index_2)
	{
		if (check(Index_1, Index_2))
        {
			return false;
		}

		v[Index_1]->Heir.push_back(v[Index_2]);
		v[Index_2]->Heir.push_back(v[Index_1]);
		return true;
	}
	void depth(int(*function)(T &, unsigned), unsigned start = 0)
	{
		if (start >= v.size())
        {
			exit(1);
		}
		bool *visited = new bool[v.size()];
		for (int i = 0; i < v.size(); i++)
		{
			visited[i] = false;
		}
		unsigned *created = new unsigned(1);
		unsigned *finished = new unsigned(0);
		Wrap(this, function, start, visited, created, finished);
		while (*created != *finished) {}
		delete[] visited;
	}


private:
	friend class Node <T>;
	friend void Wrap <T>(Graph <T> *graph, int(*function)(T &, unsigned), unsigned start, bool *visited, unsigned *created, unsigned *finished);

	vector<Node<T> *> v;
};

template <typename T> void Wrap(Graph <T> *graph, int(*function)(T &, unsigned), unsigned start, bool *visited, unsigned *created, unsigned *finished)
{
	m.lock();

	if (start >= graph->v.size())
    {
		exit(1);
	}
	if (!visited[start])
	{
		visited[start] = true;
		function(graph->v[start]->data, start);
		m.unlock();
		for (int i = 0; i < graph->v[start]->Heir.size(); i++) {
			m.lock();
			*created = *created + 1;
			m.unlock();

			unsigned newIndex = graph->v[start]->Heir[i]->index();
			thread inDepthThread(Wrap <T>, graph, function, newIndex, visited, created, finished);
			inDepthThread.detach();
		}
		m.lock();
	}
	*finished = *finished + 1;
	m.unlock();
}

int f(int &data, unsigned index)
{
	data+=1;
	cout << "There is " << data << " in " << index << " node\n";
	return 0;
}

int main()
{
	Graph <int> g;
	g.push(0);
	g.push(1, 1, 0);
	g.push(2, 2, 1, 0);
	g.push(3, 3, 0, 1, 2);
	g.push(4, 4, 0, 1, 2, 3);
	g.push(5, 5, 0, 1, 2, 3, 4);
	g.depth(f, 1);

	return 0;
}
