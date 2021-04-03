// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConvesrationManager.h"
#include "ConversationPartner.generated.h"

class UConversationSpeaker;
class UAudioComponent;

UCLASS()
class MISSEDCONNECTION_API AConversationPartner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConversationPartner();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UConversationSpeaker* speaker;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAudioComponent* audio_component;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimation(EConversationAnimation animation);

	UFUNCTION(BlueprintImplementableEvent)
	void Look(bool state, float time);

};
