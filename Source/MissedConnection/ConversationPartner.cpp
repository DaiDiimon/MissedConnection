// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AudioComponent.h"
#include "ConversationSpeaker.h"
#include "ConversationPartner.h"

// Sets default values
AConversationPartner::AConversationPartner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UAudioComponent* ac = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	ac->SetupAttachment(RootComponent);

	speaker = CreateDefaultSubobject<UConversationSpeaker>(TEXT("Speaker"));
	AddOwnedComponent(speaker);
	speaker->SetAudioComponent(ac);

}

// Called when the game starts or when spawned
void AConversationPartner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConversationPartner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

