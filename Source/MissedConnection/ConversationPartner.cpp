// Fill out your copyright notice in the Description page of Project Settings.
#include "ConversationPartner.h"

#include "Components/AudioComponent.h"
#include "ConversationSpeaker.h"

// Sets default values
AConversationPartner::AConversationPartner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	audio_component = CreateDefaultSubobject<UAudioComponent>(FName("Audio Component"));
	audio_component->SetupAttachment(RootComponent);

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

