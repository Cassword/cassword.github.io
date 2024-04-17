#include "Graph.h"

// digraph constructor.
// initialise size and vertices (a pointer to an array of graphVertex pointers)
// set all LLs to nullptrs, then use getAdjacencyList to add each edge to the adjacency list.
Graph::Graph(graphEdge edges[], int numEdges, int numVertices)
{
	size = numVertices;

	vertices = new graphVertex* [numVertices](); //"a pointer to an array of graphVertex pointers"

	// Initialize all adjacency lists
	for (int i = 0; i < numVertices; i++)
	{
		vertices[i] = nullptr;
	}

	// Add each edge to the appropriate adjacency list.
	for (int i = 0; i < numEdges; i++)
	{
		graphEdge edge = edges[i];
		vertices[edge.from] = getAdjacencyList(edge.to, edge.weight, vertices[edge.from]);
	}
}


// Builds a string representation of the graph showing the edges going from each vertex in the following form:
// e.g.: vertex 12 with edges to vertex 3 of weight 5 and vertex 13 of weight 1 would look like:
// "v12: 3 (w=5), 13 (w=1) 
// Notice the spaces, commas (not trailing). Also each vertex is on it's own line.
// Nothing should be printed by this method.
// hint: Use std::to_string(int val) to convert from integers to strings
std::string Graph::display() //GOING TO BE STRICTLY MARKED SO MAKE SURE IT'S RIGHT 
{
	std::string result;

	for (int i = 0; i < size; i++)
	{
		//Create a string for the current vertex
		std::string vertexStr = "v" + std::to_string(i) + ":";

		graphVertex* currentVertex = vertices[i];


		if (currentVertex == nullptr) //If the adjacency list is empty
		{
			vertexStr += " no outgoing edges."; //Not sure what to do in this case - not given example, but this seems alright.
		}
		else
		{
			while (currentVertex != nullptr)
			{
				vertexStr += " " + std::to_string(currentVertex->to) + " (w=" + std::to_string(currentVertex->weight) + "),";
				currentVertex = currentVertex->next; //move on so we're ready for next iteration 
			}

			vertexStr = vertexStr.substr(0, vertexStr.length() - 1); //get the string but subtract the last character, where the trailing comma would be 
		}

		//Add strings together
		result += vertexStr + "\n";
	}

	return result;
}


//Use Dijkstra's algorithm to find the shortest path from start to end.
//returns a structure with the path length and a stack with all vertices on the path with the start on the top.
//You can assume all edge weights will be under 1000.
//pathInformation is defined at the top of Graph.h
//HINT:	pQueue.top() gets a reference to the first element, but does not remove it. 
//			pQueue.pop() removes the first element but does not get a reference to it.
//				.. so use both.
pathInformation Graph::dijkstra(int start, int end) {
	// Initial DSs, provided.
	std::map<int, int> distanceTo;  // maps from vertices to best distance found to start (start->start = 0)
	std::map<int, int> pathTaken;  // maps from vertices to last vertex visited as part of best distance found so far.
	std::map<int, bool> visited;  // maps from vertices to whether or not the vertex has been visited yet so we do not visit vertices multiple times.
	// priority queue of distances to vertices yet to visit alongside their index. DISTANCE FIRST, index second.
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> frontier;

	// Set initial distances to 1000 given the intial distance will be larger than any given edge weight - which we are told to assume is < 1000 - unsure how else this info is intended to be used if not this
	//examples have this as "infinity" but given instructions suggest it's not necessary
	for (int i = 0; i < size; i++) {
		distanceTo[i] = 1000;
	}
	distanceTo[start] = 0;

	//Add start to frontier.
	frontier.push(std::make_pair(0, start));

	//Main loop
	while (!frontier.empty()) { //While the frontier is not empty 

		int vertex = frontier.top().second; //Get the index of the top element (because it's in a pair in the Pqueue with DISTANCE FIRST, index second.)

		if (visited[vertex] == true) { //Get closest unvisited Node by checking if we've visited it, if we have, then not interested.
			frontier.pop();
			continue;
		}
		frontier.pop();
		visited[vertex] = true; //set it to true now we're looking over it 

		graphVertex* currentVertex = vertices[vertex]; //Get adjacency list for our current vertex 
		while (currentVertex != nullptr) {
			int to = currentVertex->to;
			int weight = currentVertex->weight;
			if (distanceTo[vertex] + weight < distanceTo[to]) { //check the path via the visited node, if it is less (shorter) then update the values and push to the list
				distanceTo[to] = distanceTo[vertex] + weight;
				pathTaken[to] = vertex;
				frontier.push(std::make_pair(distanceTo[to], to));
			}
			currentVertex = currentVertex->next; //move on to the next - continue until we're at the end
		}
	}
	//Create a return a pathInformation struct
	pathInformation result;
	result.length = distanceTo[end];

	//Traceback
	std::stack<int> path;
	int currentNode = end;
	while (currentNode != start) { //go back until we reach the start - hence traceback, basically
		path.push(currentNode);
		currentNode = pathTaken[currentNode];
	}
	path.push(start);

	//Store the stack in the structure and return it.
	result.path = path;
	return result;



}

