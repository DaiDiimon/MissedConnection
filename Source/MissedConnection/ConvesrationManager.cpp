// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvesrationManager.h"
#include "ConversationPartner.h"
#include "ConversationPlayer.h"
#include "Containers/Map.h"
#include "Internationalization/Regex.h"
#include "Misc/FileHelper.h"

// Sets default values for this component's properties
UConvesrationManager::UConvesrationManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UConvesrationManager::BeginPlay()
{
	Super::BeginPlay();


	// ...
	
}



bool UConvesrationManager::ResolveCommand(FString command, FString args)
{
	if (command_map.Contains(command)) {
		Command func = command_map[command];
		(this->*func)(args);
		return true;
	}
	return false;
}

void UConvesrationManager::Look(FString args)
{
	
}

void UConvesrationManager::PlayAnimation(FString args)
{
	
}

void UConvesrationManager::Me(FString args)
{
	Speak(false);
}

void UConvesrationManager::You(FString args)
{
	Speak(true);
}

void UConvesrationManager::Branch(FString args)
{

}

void UConvesrationManager::End(FString args)
{
}

void UConvesrationManager::Wait(FString args)
{
}

void UConvesrationManager::Continue()
{
	int new_line_index = text.Find(TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, read_index);
	while (new_line_index != -1) {
		FString line = text.Mid(read_index, new_line_index - read_index);
		int space_index = text.Find(TEXT(" "), ESearchCase::CaseSensitive, ESearchDir::FromStart);
		FString command, args;
		if (space_index != -1) {
			command = line.Left(space_index);
			args = line.RightChop(space_index + 1);
		}
		else {
			command = line;
		}
		bool status = ResolveCommand(command, args);
		if (!status) {
			UE_LOG(LogTemp, Error, TEXT("INVALID COMMAND"));
			break;
		}
		// The function called might want to wait now
		if (wait_timer_active) break;

	}
}

void UConvesrationManager::SetupLabels()
{
	int label_index = text.Find(TEXT("LABEL "),ESearchCase::CaseSensitive, ESearchDir::FromStart);
	while (label_index != -1) {
		//get word after label and add it to labelMap
		int new_line_index = text.Find(TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, label_index + 6);
		if (new_line_index == -1) break;
		// 6 is length of LABEL with space
		FString tag = text.Mid(label_index + 6, new_line_index - label_index + 6);
		if (tag.Len() == 0) {
			UE_LOG(LogTemp, Error, TEXT("Invalid Label"));
		}
		label_map.Add(tag.TrimStartAndEnd(), new_line_index + 1);
		label_index = text.Find(TEXT("LABEL "), ESearchCase::CaseSensitive, ESearchDir::FromStart, new_line_index + 1);
	}
}

void UConvesrationManager::Speak(bool partner_speaking)
{
	

	WaitFor(1);
}

void UConvesrationManager::WaitFor(float seconds)
{
	wait_timer = seconds;
	wait_timer_active = true;
}

void UConvesrationManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (wait_timer_active) {
		if (wait_timer < 0) {
			wait_timer_active = false;
			Continue();
		}
		else {
			wait_timer -= DeltaTime;
		}
	}
}

FString UConvesrationManager::ReadFile(FString filename)
{
	FString full_path = FPaths::Combine(FPaths::ProjectContentDir(), filename);
	bool status = FFileHelper::LoadFileToString(text, *full_path);
	
	if (status) {
		read_index = 0;
		SetupLabels();
		Continue();
	}	
	else {
		UE_LOG(LogTemp, Error, TEXT("Conversation file failed to load!"));
	}

	return text;
}

