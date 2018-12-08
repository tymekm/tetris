#include "Render.h"
#include "Tetris.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

const int HEIGHT = 18;
const int WIDTH = 13;

void gameLoop(Tetris & tetris);
void moveOccDown(vector<Coords> & occ, const vector<int> & l, Render & s);
std::multimap<int, std::string> readScores();
void writeScores(std::multimap<int, std::string> & scores);


int main()
{
    using std::cout;
    using std::cin;

    Tetris tetris(HEIGHT, WIDTH);  
    gameLoop(tetris);
    endwin();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::multimap<int, std::string> scoresMap = readScores();
    auto highScore = std::max_element(scoresMap.begin(), scoresMap.end());
    int newScore = tetris.getScore();
    if (newScore > highScore->first)
	cout << "New High Score!\n";
    else
	cout << "Game Over!\n";
    cout << "Score: " << newScore << '\n';
    cout << "Enter your name" << std::endl;
    std::string name;
    getline(cin, name);
    scoresMap.insert(std::pair<int, std::string>(newScore, name));
    int n = 1;
    for (auto s = scoresMap.crbegin(); s != scoresMap.crend(); s++)
	if (n <= 10)
	{
	    cout << n << ": " << s->first << " " << s->second << '\n';
	    n++;
	}
    writeScores(scoresMap);
}

void gameLoop(Tetris & tetris)
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    int tick = 0;
    int key;

    while (true)
    {
	if (tetris.getState() == GameState::gameover)
	{
	    werase(stdscr);
	    refresh();
	    break;
	}
	key = getch();
	Direction dir;
	switch (key) 
	{
	    case KEY_DOWN:
		dir = Direction::down;
		break;
	    case KEY_LEFT:
		dir = Direction::left;
		break;
	    case KEY_RIGHT:
		dir = Direction::right;
		break;
	    case ' ':
		dir = Direction::rotate;
	        break;
	    case 'p':
	    case 'P':
		tetris.pause();
		break;
	}
	if (tetris.getState() == GameState::paused)
	    continue;
	if (key != ERR)
	    tetris.movePiece(dir);
	sleep_for(milliseconds(1));
	tick += 1;
	if (tick == (1000 - tetris.getLevel() * 40))
	{
	    tetris.movePiece(Direction::down);
	    tick = 0;
	}
    }
}
std::multimap<int, std::string> readScores()
{
    std::ifstream file;
    file.open("./score");
    std::multimap<int, std::string> scoresMap;
    int score;
    std::string name;
    while (file >> score >> name)
	scoresMap.insert(std::pair<int, std::string>(score, name));
    file.close();
    return scoresMap;
}

void writeScores(std::multimap<int, std::string> & scoresMap)
{
    std::ofstream file;
    file.open("./score");
    for (auto & s : scoresMap) 
	file << s.first << ' ' << s.second << '\n';
    file.close();
}

