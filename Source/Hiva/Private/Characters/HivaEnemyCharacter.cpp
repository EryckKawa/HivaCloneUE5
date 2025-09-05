// Eryck Torres Project


#include "Characters/HivaEnemyCharacter.h"
#include "HivaDebugHelper.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AHivaEnemyCharacter::AHivaEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 100.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

void AHivaEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartupData();
}

void AHivaEnemyCharacter::InitEnemyStartupData()
{
	if (CharacterStartUpDataAsset.IsNull())
	{
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpDataAsset.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataAsset.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(HivaAbilitySystemComponent);

					Debug::Print(TEXT("Enemy Startup Data Initialized"), FColor::Green);
				}
			})
		);
}
