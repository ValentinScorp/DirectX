#include "Precompiled.h"

#ifndef SOURCE_SMALOADER_H_
#define SOURCE_SMALOADER_H_

class GameObject;

class SmaLoader
{
public:
	SmaLoader();

	GameObject* load(std::string file);

	~SmaLoader();
};



#endif /* SOURCE_SMALOADER_H_ */
