// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "HivaTypes/HivaStructTypes.h"
#include "Itens/Weapons/HivaWeaponBase.h"
#include "HivaPlayerWeapon.generated.h"

/**
 * 
 */
UCLASS()
class HIVA_API AHivaPlayerWeapon : public AHivaWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FHivaPlayerWeaponData PlayerWeaponData;
};
