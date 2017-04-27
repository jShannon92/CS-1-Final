#ifndef MAPTILE_H
#define MAPTILE_H

class MapTile
{
	private:
		bool moveable; //We actually probably don't need this unless we want to make obsticales in the middle of the map.
		//0-blank 1-food 2-head 3-tail
		//int type;
	public:
		MapTile();
		//void setType(int itype);
		//int getType(void){ return type; };
		void setMoveable(bool imoveable);
		bool getMoveable(void){ return moveable; };

};

#endif
