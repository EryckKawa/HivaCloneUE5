// Eryck Torres Project


#include "DataAssets/Characters/DataAsset_CharacterCollection.h"

bool UDataAsset_CharacterCollection::ContainsCharacter(TSubclassOf<AHivaPlayerCharacter> CharacterClass) const
{
	return AvailableCharacters.Contains(CharacterClass);
}

TSubclassOf<AHivaPlayerCharacter> UDataAsset_CharacterCollection::GetCharacterByIndex(int32 Index) const
{
	if (AvailableCharacters.IsValidIndex(Index)) return AvailableCharacters[Index];

	return nullptr;
}
