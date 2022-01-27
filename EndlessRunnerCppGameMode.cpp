// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerCppGameMode.h"
#include "EndlessRunnerCppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerCppGameMode::AEndlessRunnerCppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
