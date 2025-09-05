// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/HivaGameplayAbility.h"
#include "HivaEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AHivaEnemyCharacter;
/**
 * 
 */
UCLASS()
class HIVA_API UHivaEnemyGameplayAbility : public UHivaGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Hiva|Ability")
	AHivaEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Hiva|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AHivaEnemyCharacter> CachedHivaEnemyCharacter;
};
