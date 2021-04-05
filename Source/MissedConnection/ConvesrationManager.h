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
	FIGHT		UMETA(DisplayName = "FIGHT"),
	IFYOUSAYSO	UMETA(DisplayName = "IFYOUSAYSO"),
	POUT		UMETA(DisplayName = "POUT"),
	FISTPUMP	UMETA(DisplayName = "FISTPUMP"),
	COCKY		UMETA(DisplayName = "COCKY")
};

UENUM(BlueprintType)
enum class EConversationFlag : uint8 {
	HECKLING1           		UMETA(DisplayName = "HECKLING1"),
	FRIENDS1            		UMETA(DisplayName = "FRIENDS1"),	
	KICKOUT1            		UMETA(DisplayName = "KICKOUT1"),
	USUAL1          		    UMETA(DisplayName = "USUAL1"),
	KICKOUT2            		UMETA(DisplayName = "KICKOUT2"),
	RUSHAWAY            		UMETA(DisplayName = "RUSHAWAY"),
	FIRSTMEET           		UMETA(DisplayName = "FIRSTMEET"),
	FINALASOLO          		UMETA(DisplayName = "FINALASOLO"),
	WORK_GAMEDEV            	UMETA(DisplayName = "WORK-GAMEDEV"),
	WORK_WIZARD         		UMETA(DisplayName = "WORK-WIZARD"),
	INTEREST_MUSIC          	UMETA(DisplayName = "INTEREST-MUSIC"),
	WORK_CHEF           		UMETA(DisplayName = "WORK-CHEF"),
	WORK_GAMEDEV_PLUS           UMETA(DisplayName = "WORK-GAMEDEV-PLUS"),
	INTEREST_MUSIC_PLUS         UMETA(DisplayName = "INTEREST-MUSIC-PLUS"),
	WORK_CHEF_PLUS          	UMETA(DisplayName = "WORK-CHEF-PLUS"),
	MEMES           		    UMETA(DisplayName = "MEMES"),
	INTEREST_COMEDY_PLUS        UMETA(DisplayName = "INTEREST-COMEDY-PLUS"),
	WORK_WIZARD_PLUS            UMETA(DisplayName = "WORK-WIZARD-PLUS")
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
		{TEXT("fight"), EConversationAnimation::FIGHT},
		{TEXT("ifyousayso"), EConversationAnimation::IFYOUSAYSO },
		{TEXT("pout"), EConversationAnimation::POUT},
		{TEXT("fistpump"), EConversationAnimation::FISTPUMP},
		{TEXT("cocky"), EConversationAnimation::COCKY}
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
		{ TEXT("heckling1"), EConversationFlag::HECKLING1            },
		{ TEXT("friends1"), EConversationFlag::FRIENDS1             },
		{ TEXT("kickout1"), EConversationFlag::KICKOUT1             },
		{ TEXT("usual1"), EConversationFlag::USUAL1          	 },
		{ TEXT("kickout2"), EConversationFlag::KICKOUT2             },
		{ TEXT("rushaway"), EConversationFlag::RUSHAWAY             },
		{ TEXT("firstmeet"), EConversationFlag::FIRSTMEET            },
		{ TEXT("finalasolo"), EConversationFlag::FINALASOLO           },
		{ TEXT("work-gamedev"), EConversationFlag::WORK_GAMEDEV         },
		{ TEXT("work-wizard"), EConversationFlag::WORK_WIZARD          },
		{ TEXT("interest-music"), EConversationFlag::INTEREST_MUSIC       },
		{ TEXT("work-chef"), EConversationFlag::WORK_CHEF            },
		{ TEXT("work-gamedev-PLUS"), EConversationFlag::WORK_GAMEDEV_PLUS    },
		{ TEXT("interest-music-PLUS"), EConversationFlag::INTEREST_MUSIC_PLUS  },
		{ TEXT("work-chef-PLUS"), EConversationFlag::WORK_CHEF_PLUS       },
		{ TEXT("memes"), EConversationFlag::MEMES           	 },
		{ TEXT("interest-comedy-PLUS"), EConversationFlag::INTEREST_COMEDY_PLUS },
		{ TEXT("work-wizard-PLUS"), EConversationFlag::WORK_WIZARD_PLUS     }
	};

	TMap<FString, int> label_map;

		
};
