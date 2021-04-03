// Fill out your copyright notice in the Description page of Project Settings.


#include "ConvesrationManager.h"
#include "ConversationPartner.h"
#include "ConversationPlayer.h"
#include "ConversationSpeaker.h"
#include "Containers/Map.h"
#include "Internationalization/Regex.h"
#include "Misc/FileHelper.h"
#include "Utility.h"

// Sets default values for this component's properties
UConvesrationManager::UConvesrationManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// ...
}


// Called when the game starts
void UConvesrationManager::BeginPlay()
{
	Super::BeginPlay();

	player->speaker->SetManager(this);
	partner->speaker->SetManager(this);

	// ...
	
}



bool UConvesrationManager::ResolveCommand(FString command, FString args)
{
	if (command_map.Contains(command)) {
		Command func = command_map[command];
		return (this->*func)(args);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("INVALID COMMAND"));
	}
	return false;
}

bool UConvesrationManager::Look(FString args)
{
	

	return true;
}

bool UConvesrationManager::PlayAnimation(FString args)
{
	
	return true;
}

bool UConvesrationManager::Me(FString args)
{
	args.TrimQuotesInline();
	player->speaker->StartDialogue(args);
	return false;
}

bool UConvesrationManager::You(FString args)
{
	args.TrimQuotesInline();
	partner->speaker->StartDialogue(args);
	return false;
}

bool UConvesrationManager::Branch(FString args)
{
	return false;
}

bool UConvesrationManager::End(FString args)
{
	// Exit the scene
	Utility::Print("END");

	return false;
}

bool UConvesrationManager::Wait(FString args)
{
	float seconds = FCString::Atof(*args);
	if (seconds <= 0) {
		UE_LOG(LogTemp, Error, TEXT("INVALID WAIT"));
	}
	WaitFor(seconds);
	return false;
}

void UConvesrationManager::Continue()
{
	while (read_index < text.Len()) {
		int new_line_index = text.Find(TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, read_index);
		if (new_line_index == -1) new_line_index = text.Len();
		FString line = text.Mid(read_index, new_line_index - read_index).TrimStartAndEnd();
		Utility::Print("NEXT");
		Utility::Print(line);
		if (line.Len() == 0) {
			read_index = new_line_index + 1;
		}
		else {
			int space_index = line.Find(TEXT(" "), ESearchCase::CaseSensitive, ESearchDir::FromStart);
			Utility::Print(FString::FromInt(space_index));
			FString command, args;
			if (space_index != -1) {
				command = line.Left(space_index).TrimStartAndEnd();
				args = line.RightChop(space_index + 1).TrimStartAndEnd();
			}
			else {
				command = line;
			}
			Utility::Print(command);
			Utility::Print(args);
			bool status = ResolveCommand(command, args);
			read_index = new_line_index + 1;
			// If a command returns false, then we don't want to continue. Something must call Continue later on though!
			if (!status) break;
		}
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

void UConvesrationManager::WaitFor(float seconds)
{
	wait_timer = seconds;
	wait_timer_active = true;
}

void UConvesrationManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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

