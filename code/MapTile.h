#ifndef MAPTILE_H
#define MAPTILE_H

class MapTile
{
	private:
		bool moveable; //We actually probably don't need this unless we want to make obsticales in the middle of the map.
	public:
		MapTile();
		void setMoveable(bool imoveable);
		bool getMoveable(void){ return moveable; };

};

#endif
