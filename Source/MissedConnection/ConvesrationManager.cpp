// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvesrationManager.h"
#include "ConversationPartner.h"
#include "ConversationPlayer.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UConvesrationManager::UConvesrationManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UConvesrationManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UConvesrationManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UConvesrationManager::ReadFile(FString filename)
{
	

	FString full_path = FPaths::Combine(FPaths::ProjectContentDir(), filename);
	UE_LOG(LogTemp, Display, TEXT("%s"), *full_path);
	bool status = FFileHelper::LoadFileToString(text, *full_path);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("Bool: %s"), status ? TEXT("true") : TEXT("false")));
	//FString result;
	//IPlatformFile& file = FPlatformFileManager::Get().GetPlatformFile();
	//if (file.CreateDirectory(*directory)) {
	//	FString myFile = directory + "/" + filename;
	//	FFileHelper::LoadFileToString(result, *myFile);
	//}
	UE_LOG(LogTemp, Display, TEXT("%s"), *text);
	return text;
}

