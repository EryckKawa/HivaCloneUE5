// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UHivaEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class HIVA_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray<TSubclassOf<UHivaEnemyGameplayAbility>> EnemyStartupAbilities;	
};
