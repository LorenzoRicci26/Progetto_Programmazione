////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// STL A* Search implementation
// (C)2001 Justin Heyes-Jones
//
// Finding a path on a simple grid maze
// This shows how to do shortest path finding using A*

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MapSearchNode.h"
#include "Subject.h"
#include "TileMap.h"

#include <iostream>
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


// Main
int main(  )
{

	cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	//Create an instance for utility object
	Utility utility(world_map,MAP_WIDTH,MAP_HEIGHT);

	//Create an instance for the application's window
	sf::RenderWindow window (sf::VideoMode(640,640),"AstarSearch",sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

	//Create instances for the mouse position
    sf::Vector2u mousePosGrid;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Create an instance for a rectangle that works as a tile selector
    sf::RectangleShape tileSelector;
    tileSelector = sf::RectangleShape(sf::Vector2f(32.f,32.f));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Red);

    //Create an instance for the audio
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile("CLICK.wav");
    sound.setBuffer(buffer);

    int posX=0;
	int posY=0;

	//Create an Instance for a Hero
	Gamecharacter* hero = new Gamecharacter(posX,posY);

	//While loop for the app
	while (window.isOpen()) {
	    sf::Event event;
        //Update mouse position
        mousePosWindow = sf::Mouse::getPosition(window);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0)
            mousePosGrid.x = static_cast<unsigned>(mousePosView.x) / 32.f ;
        if(mousePosView.y >= 0)
            mousePosGrid.y = static_cast<unsigned>(mousePosView.y) / 32.f ;

        //Update tileselector
        tileSelector.setPosition(mousePosGrid.x * 32.f, mousePosGrid.y * 32.f);

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

                        // Create an instance of the search class...
	                    AStarSearch<MapSearchNode> astarsearch (&utility);

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

                                try {
                                    TileMap movement (hero,&window,&utility,MAP_WIDTH,MAP_HEIGHT);

                                    hero->setPosition(node->x,node->y);

                                } catch (std::runtime_error &e) {
                                    std::cout<<e.what()<<std::endl;
                                    break;
                                } catch (std::out_of_range &e) {
                                    std::cout<<e.what()<<std::endl;
                                    break;
                                }

                                node->PrintNodeInfo();

                                steps++;

                                posX = node->x;
                                posY = node->y;

                                //if sound play here

                                this_thread::sleep_for(chrono::milliseconds(75)); //milliseconds between

                            }

                            cout << "Solution steps " << steps << endl;

                            // Once you're done with the solution you can free the nodes up
                            astarsearch.FreeSolutionNodes();

                        } else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
                            cout << "Search terminated. Did not find goal state\n";
                            cout << "The node goal is a wall or a point of the map unreachble"<<endl;
                        }

                        // Display the number of loops the search went through
                        cout << "SearchSteps : " << SearchSteps << "\n";

                        SearchCount++;

                        astarsearch.EnsureMemoryFreed();
	                    }
                    }
                case sf::Event::Resized:
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::GainedFocus:
                    break;
                case sf::Event::TextEntered:
                    break;
                case sf::Event::KeyPressed:
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelMoved:
                    break;
                case sf::Event::MouseWheelScrolled:
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
                    break;
                case sf::Event::MouseEntered:
                    break;
                case sf::Event::MouseLeft:
                    break;
                case sf::Event::JoystickButtonPressed:
                    break;
                case sf::Event::JoystickButtonReleased:
                    break;
                case sf::Event::JoystickMoved:
                    break;
                case sf::Event::JoystickConnected:
                    break;
                case sf::Event::JoystickDisconnected:
                    break;
                case sf::Event::TouchBegan:
                    break;
                case sf::Event::TouchMoved:
                    break;
                case sf::Event::TouchEnded:
                    break;
                case sf::Event::SensorChanged:
                    break;
                case sf::Event::Count:
                    break;
            }
	    }

        TileMap map (hero,&window,&utility,MAP_WIDTH,MAP_HEIGHT);

        window.clear();

	    for (int i=0;i<MAP_WIDTH;i++){
	        for(int j=0;j<MAP_HEIGHT;j++){

	            //For Walls
                if (utility.GetMap(i, j) == 9) {
                    map.tileMap[i][j].setFillColor(sf::Color::Cyan);
                }

                //Check if (i,j) is the hero's node
                if (i == posX && j == posY) {
                    map.tileMap[i][j].setFillColor(sf::Color::Green);
                }
	            window.draw(map.getTileMap()[i][j]);
	        }
	    }
	    window.draw(tileSelector);
	    window.display();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
