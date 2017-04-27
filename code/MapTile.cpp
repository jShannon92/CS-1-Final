#include "MapTile.h"

MapTile::MapTile(){
	//type = 0;
	moveable = true;
}
/*
void MapTile::setType(int itype){
	type = itype;
}
*/
void MapTile::setMoveable(bool imoveable){
	moveable = imoveable;
}
