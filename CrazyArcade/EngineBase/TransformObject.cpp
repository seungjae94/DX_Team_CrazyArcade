#include "PreCompile.h"
#include "TransformObject.h"

UTransformObject::UTransformObject() 
{
}

UTransformObject::~UTransformObject() 
{
}

void UTransformObject::ChildUpdate()
{
	for (size_t i = 0; i < Childs.size(); i++)
	{
		Childs[i]->Transform.ParentMat = Transform.World;
		Childs[i]->Transform.TransformUpdate();
		Childs[i]->ChildUpdate();
	}
}