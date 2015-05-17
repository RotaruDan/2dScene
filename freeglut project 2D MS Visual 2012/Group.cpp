//---------------------------------------------------------------------------
// Dan Cristian, Rotaru
//---------------------------------------------------------------------------
#include "Actor.h"
#include "Group.h"

	Group::Group(){

	}

	Group::~Group(){

	}

	void Group::drawChildren(){
		unsigned int i, size = children.size();
		for(i = 0; i < size; ++i){
			Actor* child = children[i];
			if((*child).isVisible()) {
				(*child).render();
			}
		}
	}

	void Group::addChildren(Actor* actor){
		children.push_back(actor);
	}

	void Group::draw(){
		drawChildren();
	}

	
	vector<Actor*> Group::getChildren() {
		return children;
	}