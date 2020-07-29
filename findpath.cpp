////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "stlastar.h" // See header for copyright and usage information
#include "Subject.h"

#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <thread>
#include <chrono>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

// Global data

// The world map

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;

int world_map[ MAP_WIDTH * MAP_HEIGHT ] = 
{
        // 0001020304050607080910111213141516171819
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 00
                1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1,   // 01
                1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 02
                1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 03
                1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 04
                1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 05
                1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 06
                1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1,   // 07
                1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 08
                1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1,   // 09
                1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1,   // 10
                1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1,   // 11
                1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 12
                1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1,   // 13
                1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1,   // 14
                1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1,   // 15
                1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1,   // 16
                1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9,   // 17
                1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1,   // 18
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,   // 19

};

// map helper functions

int GetMap( int x, int y )
{
	if( x < 0 ||
	    x >= MAP_WIDTH ||
		 y < 0 ||
		 y >= MAP_HEIGHT
	  )
	{
		return 9;	 
	}

	return world_map[(y*MAP_WIDTH)+x];
}



// Definitions

class MapSearchNode:public Subject
{
public:
	int x;	 // the (x,y) positions of the node
	int y;	
	
	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo();

    void subscribe(Observer *o) override;

    void unsubscribe(Observer *o) override;

    void notify() override;

private:
    std::list<Observer*> observers;
};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
    return (x == rhs.x) &&
           (y == rhs.y);

}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", x,y );

	cout << str;
	notify();
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

    return (x == nodeGoal.x) &&
           (y == nodeGoal.y);

}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 9) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y-1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) < 9)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (GetMap( x, y+1 ) < 9) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}

void MapSearchNode::subscribe(Observer *o){
    this->observers.push_back(o);

}

void MapSearchNode::unsubscribe(Observer *o) {
    this->observers.remove(o);

}

void MapSearchNode::notify() {
    for(auto observer:observers)
    {
        observer->update();
    }

}

class TileMap: public Observer
{
public:
    explicit TileMap(MapSearchNode* m,sf::RenderWindow* view):node(m),window(view)
    {
        //Init TileMap
        tileMap.resize( MAP_WIDTH,std::vector<sf::RectangleShape>());

        for (std::size_t i = 0 ; i<MAP_WIDTH ; i++)
        {
            tileMap[i].resize( MAP_WIDTH ,sf::RectangleShape());
            for (std::size_t j = 0 ; j<MAP_HEIGHT ; j++)
            {
                //tileMap
                tileMap[i][j].setSize(sf::Vector2f(50.f,50.f));
                tileMap[i][j].setOutlineThickness(1.f);
                tileMap[i][j].setFillColor(sf::Color::White);
                tileMap[i][j].setOutlineColor(sf::Color::Black);
                tileMap[i][j].setPosition(i * 50.f, j * 50.f);
            }
        }
        attach();
    }

    ~TileMap()override
    {
        detach();
    }

    const vector<std::vector<sf::RectangleShape>> &getTileMap() const {
        return tileMap;
    }

    void setNode(MapSearchNode *node) {
        TileMap::node = node;
    }

    void attach()override
    {
        this->node->subscribe(this);
    }

    void detach()override
    {
        this->node->unsubscribe(this);
    }

    void update() override
    {
        this->x = this->node->x;
        this->y = this->node->y;
        show();
    }

    void show()
    {
        //Draw
        for (int i=0; i<MAP_WIDTH; i++) {
            for (int j = 0; j < MAP_HEIGHT; j++) {
                //Check if in (i,j) position there is  a wall
                if (GetMap(i, j) == 9) {
                    this->tileMap[i][j].setFillColor(sf::Color::Cyan);
                }

                //Check if (i,j) is the hero's node
                if (i == this->x && j == this->y) {
                    this->tileMap[i][j].setFillColor(sf::Color::Green);
                }
                this->window->draw(this->tileMap[i][j]);
            }
        }

        this->window->display();

    }
    std::vector<std::vector<sf::RectangleShape>> tileMap;
private:
    int x;
    int y;
    //Objects
    MapSearchNode* node;

    //SFML Objects
    sf::RenderWindow* window;


};


// Main

int main(  )
{

	cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	sf::RenderWindow window (sf::VideoMode(1000,1000),"AstarSearch",sf::Style::Titlebar | sf::Style::Close );

    sf::Mouse mouse;
    sf::Vector2u mousePosGrid;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    sf::RectangleShape tileSelector;

    tileSelector = sf::RectangleShape(sf::Vector2f(50.f,50.f));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Red);

    int posX=0;
	int posY=0;

	while (window.isOpen()) {
	    sf::Event event;
        //Update mouse position
        mousePosWindow = sf::Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0)
            mousePosGrid.x = static_cast<unsigned>(mousePosView.x) / 50.f ;
        if(mousePosView.y >= 0)
            mousePosGrid.y = static_cast<unsigned>(mousePosView.y) / 50.f ;

        //Update tileselector
        tileSelector.setPosition(mousePosGrid.x * 50.f, mousePosGrid.y * 50.f);

	    while (window.pollEvent(event))
	    {
	        switch (event.type)
            {
                case sf::Event::Closed:{
	                window.close();
	                break;
	            }
	            case sf::Event::MouseButtonPressed:
	                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
	                    AStarSearch<MapSearchNode> astarsearch;

	                    unsigned int SearchCount = 0;

	                    const unsigned int NumSearches = 1;

                        int selectTileX = mousePosGrid.x;
                        int selectTileY = mousePosGrid.y;

	                    while (SearchCount < NumSearches) {

                        // Create a start state
                        MapSearchNode nodeStart;
                        nodeStart.x = posX;
                        nodeStart.y = posY;

                        // Define the goal state
                        MapSearchNode nodeEnd;
                        nodeEnd.x = selectTileX;
                        nodeEnd.y = selectTileY;

                        // Set Start and goal states

                        astarsearch.SetStartAndGoalStates(nodeStart, nodeEnd);

                        unsigned int SearchState;
                        unsigned int SearchSteps = 0;

                        do {
                            SearchState = astarsearch.SearchStep();

                            SearchSteps++;

#if DEBUG_LISTS

                            cout << "Steps:" << SearchSteps << "\n";

                int len = 0;

                cout << "Open:\n";
                MapSearchNode *p = astarsearch.GetOpenListStart();
                while( p )
                {
                    len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                    ((MapSearchNode *)p)->PrintNodeInfo();
#endif
                    p = astarsearch.GetOpenListNext();

                }

                cout << "Open list has " << len << " nodes\n";

                len = 0;

                cout << "Closed:\n";
                p = astarsearch.GetClosedListStart();
                while( p )
                {
                    len++;
#if !DEBUG_LIST_LENGTHS_ONLY
                    p->PrintNodeInfo();
#endif
                    p = astarsearch.GetClosedListNext();
                }

                cout << "Closed list has " << len << " nodes\n";
#endif

                        } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

                        if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
                            cout << "Search found goal state\n";

                            MapSearchNode *node = astarsearch.GetSolutionStart();
#if DISPLAY_SOLUTION
                            cout << "Displaying solution\n";
#endif
                            int steps = 0;

                            node->PrintNodeInfo();
                            for (;;) {
                                node = astarsearch.GetSolutionNext();

                                if (!node) {
                                    break;
                                }

                                TileMap map(node, &window);

                                node->PrintNodeInfo();

                                steps++;

                                posX = node->x;
                                posY = node->y;

                                this_thread::sleep_for(chrono::milliseconds(100));

                            };

                            cout << "Solution steps " << steps << endl;

                            // Once you're done with the solution you can free the nodes up
                            astarsearch.FreeSolutionNodes();

                        } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
                            cout << "Search terminated. Did not find goal state\n";

                        }

                        // Display the number of loops the search went through
                        cout << "SearchSteps : " << SearchSteps << "\n";

                        SearchCount++;

                        astarsearch.EnsureMemoryFreed();
	                    }
                    }
            }
	    }
	    MapSearchNode mapSearchNode;
	    TileMap newMap (&mapSearchNode,&window);

	    for (int i=0;i<MAP_WIDTH;i++){
	        for(int j=0;j<MAP_HEIGHT;j++){
                if (GetMap(i, j) == 9) {
                    newMap.tileMap[i][j].setFillColor(sf::Color::Cyan);
                }

                //Check if (i,j) is the hero's node
                if (i == posX && j == posY) {
                    newMap.tileMap[i][j].setFillColor(sf::Color::Green);
                }
	            window.draw(newMap.getTileMap()[i][j]);
	        }
	    }
	    window.draw(tileSelector);
	    window.display();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
