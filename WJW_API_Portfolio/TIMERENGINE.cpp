#include "TIMERENGINE.h"

void MoveTimer(BIOLOGY* pBiology)
{
    pBiology->TimeUp(1);
    if (pBiology->GetTime() >= 10)
    {
        pBiology->nAni++;
        pBiology->TimeUp(1);
        pBiology->SetTime(0);
    }
}

void FireTimer(BIOLOGY* pBiology)
{
    pBiology->nAni++;
    pBiology->SetAS(0);
}