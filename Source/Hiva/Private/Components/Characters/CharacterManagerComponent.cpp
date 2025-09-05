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
		// Salve referência ao pawn atual
		PreviousPawn = CurrentPlayer;
        
		PreviousLocation = CurrentPlayer->GetActorLocation();
		PreviousRotation = CurrentPlayer->GetActorRotation(); 
        
		SpawnLocation = PreviousLocation;
		SpawnRotation = PlayerController->GetControlRotation();
        
		PlayerController->UnPossess();

		// 🔹 Torna o pawn invisível
		CurrentPlayer->SetActorHiddenInGame(true);

		// 🔹 Remove colisão
		CurrentPlayer->SetActorEnableCollision(false);

		// 🔹 Desativa input
		CurrentPlayer->DisableInput(PlayerController);

		// 🔹 Esconde todos os atores anexados
		TArray<AActor*> AttachedActors;
		CurrentPlayer->GetAttachedActors(AttachedActors);

		for (AActor* Attached : AttachedActors)
		{
			if (Attached)
			{
				Attached->SetActorHiddenInGame(true);
				Attached->SetActorEnableCollision(false);
			}
		}
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