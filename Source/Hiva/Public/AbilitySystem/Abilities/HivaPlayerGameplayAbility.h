// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HivaGameplayAbility.h"
#include "HivaPlayerGameplayAbility.generated.h"

class UPlayerCombatComponent;
class AHivaPlayerController;
class AHivaPlayerCharacter;
/**
 * 
 */
UCLASS()
class HIVA_API UHivaPlayerGameplayAbility : public UHivaGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Hiva|Ability")
	AHivaPlayerCharacter* GetPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Hiva|Ability")
	AHivaPlayerController* GetPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Hiva|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();
	
private:
	// Cache the player character to avoid repeated casts
	TWeakObjectPtr<AHivaPlayerCharacter> CachedHivaPlayerCharacter;
	TWeakObjectPtr<AHivaPlayerController> CachedHivaPlayerController;
};
