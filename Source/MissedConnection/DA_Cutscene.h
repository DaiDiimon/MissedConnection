// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Cutscene.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MISSEDCONNECTION_API UDA_Cutscene : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadONly)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTexture2D*> images;

	UFUNCTION(BlueprintPure)
	int32 Count();
	
};
