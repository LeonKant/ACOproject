1. Put coordinate points into points.txt

2. Run ACOproject.cpp 
	a. a and b parameters can be updated in the (CGraph::assignProb) function
	b. # of points in points.txt must match value in main function
	c. # of journeys and ants can be set in CGraph::ACO() function
	d. file to store avg lengths per journey can be set in CGraph::ACO()

3. Paths of all ants will be stored in points.txt
	a. to run again, clear points.txt except for coordinate points