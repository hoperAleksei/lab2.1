#pragma once
#include <string>
using namespace std;
const int c = 3;
const int d = 2;


class Game {

private:

	string genre;
	string releaseDate;
	string designer;
public:
	
	size_t key;
	string name;
	size_t getKey()
	{
		
		string data = this->name + this->designer;
		size_t len = data.length();
		size_t res = 0;
		for (size_t i = 0; i < len; ++i)
		{
			res += (size_t) data[i];
		}
		return res;
	}
	void setName(string nameC)
	{
		name = nameC;
		key = getKey();
	}
    bool operator==(const Game& g1)
    {
	    if ((name == g1.name) && (genre == g1.genre) && (releaseDate == g1.releaseDate) && (designer == g1.designer))
	    {
		    return true;
	    }
	    return false;
    }
    
	
	
	Game(string nameC, string genreC, string releaseDateC, string designerC)
	{
		name = move(nameC);
		genre = move(genreC);
		releaseDate = move(releaseDateC);
		designer = move(designerC);
		key = getKey();
	}
	
	Game() = default;
	friend ostream& operator<<(ostream& out, const Game& gm);
};

ostream& operator<<(ostream& out, const Game& gm)
{
	out << "Game(" << gm.name << ", " << gm.genre << ", " << gm.releaseDate << ", " << gm.designer << ")" << " with key: " << gm.key;
	return out;
	
}

