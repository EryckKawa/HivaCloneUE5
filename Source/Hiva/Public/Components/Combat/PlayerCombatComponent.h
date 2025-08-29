// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class AHivaPlayerWeapon;
/**
 * 
 */
UCLASS()
class HIVA_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AHivaPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;
};
