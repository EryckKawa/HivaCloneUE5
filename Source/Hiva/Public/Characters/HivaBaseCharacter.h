// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "HivaBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UHivaAttributeSet;
class UHivaAbilitySystemComponent;

UCLASS()
class HIVA_API AHivaBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AHivaBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface
	/** Returns the Ability System Component for this character */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface
	
protected:
	//~ Begin APawn Interface
	// Called when the game starts or when spawned GAS need this function to work properly
	virtual void PossessedBy(AController* NewController) override;  
	//~ End APawn Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UHivaAbilitySystemComponent* HivaAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UHivaAttributeSet* HivaAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterDataAsset")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpDataAsset;

public:
	FORCEINLINE UHivaAbilitySystemComponent* GetHivaAbilitySystemComponent() const { return HivaAbilitySystemComponent; }
	FORCEINLINE UHivaAttributeSet* GetHivaAttributeSet() const { return HivaAttributeSet; }
	
};
