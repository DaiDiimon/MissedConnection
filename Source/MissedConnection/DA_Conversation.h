// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ConvesrationManager.h"
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
	TSet<EConversationFlag> required_flags;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool A_speaker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool inside;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool final_A_solo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool final_B_solo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString filename;	
};
