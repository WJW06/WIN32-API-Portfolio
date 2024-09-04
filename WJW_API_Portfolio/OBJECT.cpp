#include "OBJECT.h"
#include "COLLIDER.h"

OBJECT::OBJECT():
	nReductionRate(0),
	pPosition{0,0},
	nRealWidth(0),
	nRealHeight(0),
	pCollider(nullptr)
{
}

OBJECT::~OBJECT()
{
	if (pCollider != nullptr)
		delete pCollider;
}

void OBJECT::CreateCollider()
{
	pCollider = new COLLIDER;
	pCollider->pObject = this;
}

void OBJECT::Update()
{
	this;
	if (pCollider)
	{
		pCollider->Update();
		pCollider->SetWidth((GetCollider()->GetxFinalPos() + GetRealWidth() / nReductionRate));
		pCollider->SetHeight((GetCollider()->GetyFinalPos() + GetRealHeight() / 2));
	}
}
