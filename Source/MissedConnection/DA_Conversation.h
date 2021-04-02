// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Conversation.generated.h"

UENUM(BlueprintType)
enum class EConversationType : uint8
{
	INSIDE	UMETA(DisplayName = "Inside"),
	OUTSIDE UMETA(DisplayName = "Outside")
};

/**
 * 
 */
UCLASS(BlueprintType)
class MISSEDCONNECTION_API UDA_Conversation : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EConversationType conversation_type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString filename;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase *music;


	
};
