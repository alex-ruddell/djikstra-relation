#ifndef _SetControl_h
#define _SetControl_h

#include "SetUI.h"
#include "SetOfStrings.h"
#include "StringRelation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <cctype>

class SetControl
{
	private:
		// Member variables.
		SetUI* setUI;
		SetOfStrings *setModel;
		StringRelation *relationModel;
		
	public:
		// Constructor and destructor respecively.
		SetControl();	
		~SetControl();
		
		// Member functions.
		bool Run();

};
#endif
