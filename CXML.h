#ifndef __CXML_H__
#define __CXML_H__





/*
-------------------------------------------------
	Includes
-------------------------------------------------
*/

// Defines
#include <stack>


class CXML{
	public :			
		CXML(char* string, CXML* parent){
			_string = string;
			_value = 0;
			_numChilds = 0;

			_childs = 0;
			_parent = parent;
		}

		void setString(char* value){_value = value;}
		char* getString(){return _string;}

		void setValue(char* value){_value = value;}
		char* getValue(){return _value;}

		void setParent(CXML* parent){_parent = parent;}
		void addChild(){++_numChilds;}
		void setNumChild(vu8 childs){_numChilds = childs;}
		u8 getNumChild(){return _numChilds;}
		void setChilds(CXML**childs){_childs = childs;}
		CXML** getChilds(){return _childs;}

	private:
		char *_string;
		char *_value;
		u8 _numChilds;
		CXML **_childs;
		CXML *_parent;
};


#endif
