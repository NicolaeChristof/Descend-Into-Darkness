// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DescendIntoDarknessGameMode.generated.h"

UCLASS(minimalapi)
class ADescendIntoDarknessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADescendIntoDarknessGameMode();

	class UDataTable* GetItemDB() const { return ItemDB; }

protected:

	UPROPERTY(EditDefaultsOnly)
    class UDatatable* ItemDB;
};



