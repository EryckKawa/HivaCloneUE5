// Eryck Torres Project

#pragma once

#include "CoreMinimal.h"
#include "Characters/HivaPlayerCharacter.h"
#include "Engine/DataAsset.h"
#include "DataAsset_CharacterCollection.generated.h"

/**
 * 
 */
UCLASS()
class HIVA_API UDataAsset_CharacterCollection : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Collection")
	TArray<TSubclassOf<AHivaPlayerCharacter>> AvailableCharacters;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Collection")
	TMap<FName, TSubclassOf<AHivaPlayerCharacter>> CharactersNames;

	UFUNCTION(BlueprintCallable, Category = "Character Collection")
	bool ContainsCharacter(TSubclassOf<AHivaPlayerCharacter> CharacterClass) const;

	UFUNCTION(BlueprintCallable, Category = "Character Collection")
	TSubclassOf<AHivaPlayerCharacter> GetCharacterByIndex(int32 Index) const;
	
};
