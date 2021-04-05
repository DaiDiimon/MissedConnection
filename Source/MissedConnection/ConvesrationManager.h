// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConvesrationManager.generated.h"

UENUM(BlueprintType)
enum class EConversationAnimation : uint8 {
	IDLE		UMETA(DisplayName = "IDLE"),
	JOLLY		UMETA(DisplayName = "JOLLY"),
	DEJECTED	UMETA(DisplayName = "DEJECTED"),
	DISAGREE	UMETA(DisplayName = "DISAGREE"),
	LOOKAROUND	UMETA(DisplayName = "LOOKAROUND"),
	NOWAY		UMETA(DisplayName = "NOWAY"),
	POINT		UMETA(DisplayName = "POINT"),
	SHRUG		UMETA(DisplayName = "SHRUG"),
	WONDERING	UMETA(DisplayName = "WONDERING"),
	FIGHT		UMETA(DisplayName = "FIGHT")
};

UENUM(BlueprintType)
enum class EConversationFlag : uint8 {
	FIRSTMEET		UMETA(DisplayName = "First Meet"),
	HECKLING1		UMETA(DisplayName = "Heckling 1"),
	HECKLING2		UMETA(DisplayName = "Heckling 2"),
	FRIENDS1		UMETA(DisplayName = "Friends 1"),
	FRIENDS2		UMETA(DisplayName = "Friends 2"),
	KICKOUT1		UMETA(DisplayName = "Kickout 1"),
	KICKOUT2		UMETA(DisplayName = "Kickout 2"),
	RUSHAWAY		UMETA(DisplayName = "Rush Away"),
	FINALASOLO		UMETA(DisplayName = "Final A Solo")
};


USTRUCT(BlueprintType)
struct FBranchInfo {
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString dialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool has_label;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString label;

};

class AConversationPartner;
class AConversationPlayer;

UCLASS(ClassGroup = (Custom), Blueprintable, meta = (BlueprintSpawnableComponent))
class MISSEDCONNECTION_API UConvesrationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UConvesrationManager();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		AConversationPlayer* player;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
		AConversationPartner* partner;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void BranchBlueprint(const TArray<FBranchInfo>& branches);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void EndBlueprint();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SkipUI(bool state);


private:
	typedef bool (UConvesrationManager::* Command)(FString);

	bool ResolveCommand(FString command, FString args);

	bool PlayAnimation(FString args);

	bool Flag(FString args);

	bool Look(FString args);

	bool You(FString args);

	bool Wait(FString args);

	bool Branch(FString args);

	bool End(FString args);

	void SetupLabels();

	void WaitFor(float seconds);

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool Me(FString args);

	UFUNCTION(BlueprintCallable)
		void Continue();

	UFUNCTION(BlueprintCallable)
		FString ReadFile(FString filename);

	UFUNCTION(BlueprintCallable)
		void JumpToLabel(FString label);


	//Skip until branch or end, process flags
	UFUNCTION(BlueprintCallable)
	void Skip();



private:
	FString text;

	bool skipMode = false;

	bool wait_timer_active = false;

	float wait_timer = 0;

	int read_index = 0;

	TMap<FString, EConversationAnimation> animation_map = {
		{TEXT("idle"), EConversationAnimation::IDLE},
		{TEXT("jolly"), EConversationAnimation::JOLLY},
		{TEXT("dejected"), EConversationAnimation::DEJECTED},
		{TEXT("disagree"), EConversationAnimation::DISAGREE},
		{TEXT("lookaround"), EConversationAnimation::LOOKAROUND},
		{TEXT("noway"), EConversationAnimation::NOWAY},
		{TEXT("point"), EConversationAnimation::POINT},
		{TEXT("shrug"), EConversationAnimation::SHRUG},
		{TEXT("wondering"), EConversationAnimation::WONDERING},
		{TEXT("fight"), EConversationAnimation::FIGHT}
	};

	TMap<FString, Command> command_map = {
		{TEXT("look"), &UConvesrationManager::Look},
		{TEXT("animate"), &UConvesrationManager::PlayAnimation},
		{TEXT("you"), &UConvesrationManager::You},
		{TEXT("me"), &UConvesrationManager::Me},
		{TEXT("wait"), &UConvesrationManager::Wait},
		{TEXT("end"), &UConvesrationManager::End},
		{TEXT("branch"), &UConvesrationManager::Branch},
		{TEXT("flag"), &UConvesrationManager::Flag}
	};

	TMap<FString, EConversationFlag> flag_map = {
		{ TEXT("firstmeet"), EConversationFlag::FIRSTMEET },
		{ TEXT("heckling1"), EConversationFlag::HECKLING1 },
		{ TEXT("heckling2"), EConversationFlag::HECKLING2 },
		{ TEXT("friends1"), EConversationFlag::FRIENDS1 },
		{ TEXT("friends2"), EConversationFlag::FRIENDS2 },
		{ TEXT("kickout1"), EConversationFlag::KICKOUT1 },
		{ TEXT("kickout2"), EConversationFlag::KICKOUT2 },
		{ TEXT("rushaway"), EConversationFlag::RUSHAWAY },
		{ TEXT("finalasolo"), EConversationFlag::FINALASOLO }
	};

	TMap<FString, int> label_map;

		
};
