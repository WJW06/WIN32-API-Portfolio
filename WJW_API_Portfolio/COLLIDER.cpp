#include "COLLIDER.h"
#include "OBJECT.h"

int COLLIDER::nNextID = 0;

COLLIDER::COLLIDER():
	pObject(nullptr),
	pOffsetPos{0,0},
	pFinalPos{0,0},
	nWidth(0),
	nHeight(0),
	nId(nNextID++)
{
}

COLLIDER::~COLLIDER()
{
	
}

void COLLIDER::Update()
{
	POINT pObjectPos = pObject->GetPosition();
	pFinalPos.x = pObjectPos.x + pOffsetPos.x;
	pFinalPos.y = pObjectPos.y + pOffsetPos.y;
}

void COLLIDER::Render()
{

}
