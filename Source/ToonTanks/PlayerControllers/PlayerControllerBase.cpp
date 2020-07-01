// Copyright @CloudStudio 2020

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool bSetPlayerEnabled)
{
	if (bSetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
		APlayerControllerBase::bShowMouseCursor = true;
	}
	else
	{
		GetPawn()->DisableInput(this);
		APlayerControllerBase::bShowMouseCursor = false;
	}
}