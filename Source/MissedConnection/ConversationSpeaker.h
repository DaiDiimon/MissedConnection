// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConversationSpeaker.generated.h"

class UConvesrationManager;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class MISSEDCONNECTION_API UConversationSpeaker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UConversationSpeaker();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool left_speaker;

	UPROPERTY(EditAnywhere)
	float speed = 10;

	UPROPERTY(EditAnywhere)
	float wait_time = 1;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateDialogueUI(const FString& text);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartDialogueUI();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndDialogueUI();

	UFUNCTION(BlueprintCallable)
	void SetAudioComponent(UAudioComponent* ac);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UConvesrationManager* conversation_manager;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* audio_component;

	UPROPERTY(EditAnywhere)
	USoundBase* period_sound;

	UPROPERTY(EditAnywhere)
	USoundBase* question_sound;

	UPROPERTY(EditAnywhere)
	USoundBase* exclamation_sound;

	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> vocal_sounds;

private:
	void ReadNextChar();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartDialogue(FString d);

	void SetManager(UConvesrationManager* cm);

private:

	int read_index = 0;

	FString dialogue;

	bool dialogue_active = false;

	float dialogue_timer;

	bool wait_timer_active = false;

	float wait_timer = 0;
	
		
};
