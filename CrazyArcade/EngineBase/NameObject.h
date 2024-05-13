#pragma once
#include <string>
#include "EngineString.h"

// Ό³Έν :
class UNameObject
{
public:
	// constrcuter destructer
	UNameObject();
	virtual ~UNameObject();

	// delete Function

	void SetName(std::string_view _View)
	{
		// Name = UEngineString::ToUpper(_View);
		Name = _View;
	}

	std::string GetName()
	{
		return Name;
	}

protected:

private:
	std::string Name;

};

