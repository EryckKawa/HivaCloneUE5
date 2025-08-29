// Eryck Torres Project


#include "Characters/HivaBaseCharacter.h"

#include "AbilitySystem/HivaAbilitySystemComponent.h"
#include "AbilitySystem/HivaAttributeSet.h"

// Sets default values
AHivaBaseCharacter::AHivaBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	HivaAbilitySystemComponent = CreateDefaultSubobject<UHivaAbilitySystemComponent>(TEXT("HivaAbilitySystemComponent"));
	
	HivaAttributeSet = CreateDefaultSubobject<UHivaAttributeSet>(TEXT("HivaAttributeSet"));
}

UAbilitySystemComponent* AHivaBaseCharacter::GetAbilitySystemComponent() const
{
	return HivaAbilitySystemComponent;
}

void AHivaBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HivaAbilitySystemComponent)
	{
		HivaAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

