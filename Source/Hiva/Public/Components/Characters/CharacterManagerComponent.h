// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Characters/HivaPlayerCharacter.h"
#include "Components/PawnExtentionComponentBase.h"
#include "CharacterManagerComponent.generated.h"

class UDataAsset_CharacterCollection;
/**
 * 
 */
UCLASS()
class HIVA_API UCharacterManagerComponent : public UPawnExtentionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Character Manager")
	void SwitchToNextCharacter();

	UFUNCTION(BlueprintCallable, Category = "Character Manager")
	void SwitchToPreviousCharacter();

	UFUNCTION(BlueprintCallable, Category = "Character Manager")
	void SwitchToCharacterByIndex(int32 Index);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Manager")
	UDataAsset_CharacterCollection* DataAssetCharactersCollections;

private:
	UPROPERTY()
	int32 CurrentCharacterIndex = 0;

	/** Realiza a lógica de spawn e possessão do novo personagem. */
	void SpawnAndPossessCharacter(TSubclassOf<AHivaPlayerCharacter> CharacterClass);
};
