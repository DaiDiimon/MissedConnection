// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ConvesrationManager.h"
#include "DA_Conversation.h"
#include "MissedConnectionGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MISSEDCONNECTION_API UMissedConnectionGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<EConversationFlag> acquired_flags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FString> viewed_conversations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDA_Conversation *conversation_to_load;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString scene_to_return_to;
	
};
