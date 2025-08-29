// Eryck Torres Project


#include "Components/Characters/CharacterManagerComponent.h"
#include "DataAssets/Characters/DataAsset_CharacterCollection.h"

void UCharacterManagerComponent::SwitchToNextCharacter()
{
	if (!DataAssetCharactersCollections || DataAssetCharactersCollections->AvailableCharacters.IsEmpty())
	{
		return;
	}

	const int32 NumCharacters = DataAssetCharactersCollections->AvailableCharacters.Num();
	CurrentCharacterIndex = (CurrentCharacterIndex + 1) % NumCharacters;
	SwitchToCharacterByIndex(CurrentCharacterIndex);
}

void UCharacterManagerComponent::SwitchToPreviousCharacter()
{
	if (!DataAssetCharactersCollections || DataAssetCharactersCollections->AvailableCharacters.IsEmpty())
	{
		return;
	}

	const int32 NumCharacters = DataAssetCharactersCollections->AvailableCharacters.Num();
	CurrentCharacterIndex = (CurrentCharacterIndex - 1 + NumCharacters) % NumCharacters;
	SwitchToCharacterByIndex(CurrentCharacterIndex);
}

void UCharacterManagerComponent::SwitchToCharacterByIndex(int32 Index)
{
	if (!DataAssetCharactersCollections) return;

	TSubclassOf<AHivaPlayerCharacter> CharacterClass = DataAssetCharactersCollections->GetCharacterByIndex(Index);

	if (CharacterClass)
	{
		CurrentCharacterIndex = Index;
		SpawnAndPossessCharacter(CharacterClass);
	}
}

void UCharacterManagerComponent::SpawnAndPossessCharacter(TSubclassOf<AHivaPlayerCharacter> CharacterClass)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetOwner());

	if (!PlayerController) return;

	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;
	
	APawn* CurrentPlayer = PlayerController->GetPawn();
	if (CurrentPlayer)
	{
		SpawnLocation = CurrentPlayer->GetActorLocation();
		SpawnRotation = PlayerController->GetControlRotation();
		
		PlayerController->UnPossess();
		CurrentPlayer->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = PlayerController;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (NewPawn)
	{
		PlayerController->Possess(NewPawn);
	}
}
