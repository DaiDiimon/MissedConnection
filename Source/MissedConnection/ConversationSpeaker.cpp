// Fill out your copyright notice in the Description page of Project Settings.

#include "ConvesrationManager.h"
#include "Components/AudioComponent.h"
#include "ConversationSpeaker.h"

// Sets default values for this component's properties
UConversationSpeaker::UConversationSpeaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UConversationSpeaker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UConversationSpeaker::ReadNextChar()
{
	FString text = dialogue.Left(read_index++);
	UpdateDialogueUI(text);

	if (!audio_component->IsPlaying()) {
		TCHAR character = text[read_index - 1];
		switch (character) {
			case '.':
				audio_component->Sound = period_sound;
				break;
			case '!':
				audio_component->Sound = exclamation_sound;
				break;
			case '?':
				audio_component->Sound = question_sound;
				break;
			default:
				if (vocal_sounds.Num() > 0) {
					int sound = FMath::RandRange(0, vocal_sounds.Num() - 1);
					audio_component->Sound = vocal_sounds[sound];
				}
		}
		audio_component->Play();
	}


	if (read_index < dialogue.Len()) {
		// Delay next letter
		dialogue_timer = 1 / speed;
	}
	else {
		// Dialogue over
		dialogue_active = false;

		// Wait a bit before continuing
		wait_timer_active = true;
		wait_timer = wait_time;

	}

}


// Called every frame
void UConversationSpeaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (dialogue_active) {
		if (dialogue_timer < 0) {
			// Trigger next letter
			ReadNextChar();
		}
		else {
			dialogue_timer -= DeltaTime;
		}
	}

	if (wait_timer_active) {
		if (wait_timer < 0) {
			wait_timer_active = false;
			conversation_manager->Continue();
		}
		else {
			wait_timer -= DeltaTime;
		}
	}
	// ...
}

void UConversationSpeaker::StartDialogue(FString d)
{
	dialogue = d;
	dialogue_active = true;
	ReadNextChar();
}

void UConversationSpeaker::SetManager(UConvesrationManager* cm)
{
	conversation_manager = cm;
}

void UConversationSpeaker::SetAudioComponent(UAudioComponent* ac)
{
	audio_component = ac;
}

