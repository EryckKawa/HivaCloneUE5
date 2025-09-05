// Eryck Torres Project


#include "Characters/HivaPlayerCharacter.h"
#include "HivaDebugHelper.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/HivaInputComponent.h"
#include "HivaGameplayTags.h"
#include "AbilitySystem/HivaAbilitySystemComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

AHivaPlayerCharacter::AHivaPlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
}

void AHivaPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpDataAsset.IsNull())
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataAsset.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(HivaAbilitySystemComponent);
		}
	}
}

void AHivaPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is nullptr in %s. Please set it up in the Blueprint."), *GetName());

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UHivaInputComponent* HivaInputComponent = CastChecked<UHivaInputComponent>(PlayerInputComponent);

	HivaInputComponent->BindNativeInputAction(InputConfigDataAsset, HivaGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this,
	                                          &AHivaPlayerCharacter::Input_Look);
	HivaInputComponent->BindNativeInputAction(InputConfigDataAsset, HivaGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this,
	                                          &AHivaPlayerCharacter::Input_Move);
	HivaInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void AHivaPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHivaPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (!Controller) return;
	
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHivaPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AHivaPlayerCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	HivaAbilitySystemComponent->OnAbilityInputPressed(InputTag);
}

void AHivaPlayerCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	HivaAbilitySystemComponent->OnAbilityInputReleased(InputTag);
}
