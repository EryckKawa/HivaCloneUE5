// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtentionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AHivaWeaponBase;
/**
 * 
 */
UCLASS()
class HIVA_API UPawnCombatComponent : public UPawnExtentionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AHivaWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeaponOnSpawn = true);

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AHivaWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category = "Player|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Player|Combat")
	AHivaWeaponBase* GetCurrentEquippedWeapon() const;

private:
	//Assign a tag to a weapon to identify it, can assign more than 1 weapon and tap
	TMap<FGameplayTag, AHivaWeaponBase*> CharacterCarriedWeaponMap;
};
