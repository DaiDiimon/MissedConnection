// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Conversation.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MISSEDCONNECTION_API UDA_Conversation : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool inside;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString filename;	
};
