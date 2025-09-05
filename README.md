# Hiva - Projeto Unreal Engine 5

## Visão Geral

Hiva é um projeto de jogo desenvolvido em Unreal Engine 5 que implementa um sistema de combate baseado em habilidades (Gameplay Ability System - GAS) com personagens jogáveis e inimigos. O projeto utiliza uma arquitetura modular focada em componentes e sistemas de habilidades, demonstrando as melhores práticas de desenvolvimento em Unreal Engine 5.

### Características Principais

- **Sistema de Combate Avançado**: Implementação completa do Gameplay Ability System (GAS)
- **Arquitetura Modular**: Componentes especializados e reutilizáveis
- **Sistema de Input Robusto**: Enhanced Input com Gameplay Tags
- **IA Inteligente**: Sistema de inimigos com comportamento automático
- **Sistema de Armas**: Armas com habilidades específicas e animações
- **Otimização**: Carregamento assíncrono e gestão eficiente de recursos

## Arquitetura do Projeto

### Padrões de Design Utilizados

O projeto implementa vários padrões de design importantes:

#### 1. **Component-Based Architecture**
- Cada funcionalidade é encapsulada em componentes especializados
- Facilita reutilização e manutenção do código
- Permite composição flexível de funcionalidades

#### 2. **Template Method Pattern**
- `UPawnExtentionComponentBase` fornece métodos template para acesso a Pawn e Controller
- Garante type-safety através de static_assert

#### 3. **Strategy Pattern**
- Diferentes tipos de habilidades implementam estratégias específicas
- `EHivaAbilityActivationPolity` define diferentes políticas de ativação

#### 4. **Data-Driven Design**
- Data Assets controlam configurações e comportamentos
- Separação clara entre código e dados configuráveis

### Estrutura Hierárquica

```
Hiva Project
├── Core Systems
│   ├── Gameplay Ability System (GAS)
│   ├── Enhanced Input System
│   └── Attribute System
├── Character Systems
│   ├── Base Character (AHivaBaseCharacter)
│   ├── Player Character (AHivaPlayerCharacter)
│   └── Enemy Character (AHivaEnemyCharacter)
├── Combat Systems
│   ├── Pawn Combat Component
│   ├── Player Combat Component
│   └── Enemy Combat Component
├── Weapon Systems
│   ├── Weapon Base (AHivaWeaponBase)
│   └── Player Weapon (AHivaPlayerWeapon)
└── Data Management
    ├── Startup Data Assets
    ├── Input Configuration
    └── Character Collections

## Análise Detalhada dos Sistemas

### 1. Sistema de Personagens

#### `AHivaBaseCharacter` - A Fundação de Todos os Personagens

**Arquivo**: `Source/Hiva/Public/Characters/HivaBaseCharacter.h`

Esta é a classe base fundamental que estabelece a arquitetura para todos os personagens do jogo. Sua implementação é crucial para o funcionamento do Gameplay Ability System.

**Arquitetura e Design**:
```cpp
class HIVA_API AHivaBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
    // Implementa IAbilitySystemInterface para integração com GAS
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
    
    // Componentes principais do GAS
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UHivaAbilitySystemComponent* HivaAbilitySystemComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
    UHivaAttributeSet* HivaAttributeSet;
    
    // Sistema de inicialização via Data Assets
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterDataAsset")
    TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpDataAsset;
};
```

**Fluxo de Inicialização**:
1. **PossessedBy()**: Chamado quando o personagem é possuído por um Controller
2. **Carregamento de Data Asset**: Carrega configurações específicas do personagem
3. **Configuração do GAS**: Aplica habilidades e efeitos definidos no Data Asset

**Vantagens desta Arquitetura**:
- **Reutilização**: Todos os personagens herdam funcionalidades GAS
- **Flexibilidade**: Data Assets permitem configuração sem recompilação
- **Manutenibilidade**: Mudanças na base afetam todos os personagens

#### `AHivaPlayerCharacter` - O Personagem do Jogador

**Arquivo**: `Source/Hiva/Public/Characters/HivaPlayerCharacter.h`

Implementação especializada para personagens controlados pelo jogador, com foco em input, câmera e combate.

**Sistema de Câmera Avançado**:
```cpp
// Configuração da câmera no construtor
CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
CameraBoom->SetupAttachment(GetRootComponent());
CameraBoom->TargetArmLength = 200.f;
CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
CameraBoom->bUsePawnControlRotation = true;

FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
FollowCamera->bUsePawnControlRotation = false;
```

**Sistema de Input Robusto**:
```cpp
void AHivaPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Configuração do Enhanced Input
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
    Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
    
    // Binding de ações nativas
    HivaInputComponent->BindNativeInputAction(InputConfigDataAsset, HivaGameplayTags::InputTag_Look, 
                                            ETriggerEvent::Triggered, this, &AHivaPlayerCharacter::Input_Look);
    
    // Binding de habilidades
    HivaInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, 
                                             &ThisClass::Input_AbilityInputPressed, 
                                             &ThisClass::Input_AbilityInputReleased);
}
```

**Sistema de Movimento**:
```cpp
void AHivaPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
    const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
    const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
    
    // Movimento baseado na rotação da câmera
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
```

#### `AHivaEnemyCharacter` - Sistema de IA Inteligente

**Arquivo**: `Source/Hiva/Public/Characters/HivaEnemyCharacter.h`

Implementação otimizada para inimigos controlados por IA, com carregamento assíncrono e configurações específicas.

**Configuração de IA**:
```cpp
AHivaEnemyCharacter::AHivaEnemyCharacter()
{
    // Auto-possessão por IA
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    
    // Configurações de movimento otimizadas para IA
    GetCharacterMovement()->bUseControllerDesiredRotation = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 100.f;
}
```

**Carregamento Assíncrono Otimizado**:
```cpp
void AHivaEnemyCharacter::InitEnemyStartupData()
{
    // Carregamento assíncrono para evitar travamentos
    UAssetManager::GetStreamableManager().RequestAsyncLoad(
        CharacterStartUpDataAsset.ToSoftObjectPath(),
        FStreamableDelegate::CreateLambda([this]()
        {
            if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpDataAsset.Get())
            {
                LoadedData->GiveToAbilitySystemComponent(HivaAbilitySystemComponent);
                Debug::Print(TEXT("Enemy Startup Data Initialized"), FColor::Green);
            }
        })
    );
}
```

### 2. Gameplay Ability System (GAS) - Análise Completa

O Gameplay Ability System é o coração do projeto Hiva, fornecendo um framework robusto para habilidades, atributos e efeitos de gameplay.

#### `UHivaAbilitySystemComponent` - O Cérebro do Sistema

**Arquivo**: `Source/Hiva/Public/AbilitySystem/HivaAbilitySystemComponent.h`

Este componente estende o `UAbilitySystemComponent` padrão do Unreal, adicionando funcionalidades específicas para o projeto.

**Gerenciamento de Input de Habilidades**:
```cpp
void UHivaAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
    if (!InInputTag.IsValid()) return;
    
    // Procura por habilidades que correspondem à tag de input
    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
        
        // Tenta ativar a habilidade
        TryActivateAbility(AbilitySpec.Handle);
    }
}
```

**Sistema de Concessão de Habilidades de Armas**:
```cpp
void UHivaAbilitySystemComponent::GrantPlayerWeaponAbilities(
    const TArray<FHivaPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel)
{
    for (const FHivaPlayerAbilitySet& AbilitySet : InWeaponAbilities)
    {
        if (!AbilitySet.IsValid()) continue;
        
        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToAdd);
        AbilitySpec.SourceObject = GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
        
        GiveAbility(AbilitySpec);
    }
}
```

#### `UHivaAttributeSet` - Sistema de Atributos

**Arquivo**: `Source/Hiva/Public/AbilitySystem/HivaAttributeSet.h`

Define os atributos fundamentais dos personagens com macros especializadas para facilitar o acesso.

**Implementação dos Atributos**:
```cpp
class HIVA_API UHivaAttributeSet : public UAttributeSet
{
public:
    // Atributos de Vida
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
    FGameplayAttributeData CurrentHealth;
    ATTRIBUTE_ACCESSORS(UHivaAttributeSet, CurrentHealth);
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Health")
    FGameplayAttributeData MaxHealth;
    ATTRIBUTE_ACCESSORS(UHivaAttributeSet, MaxHealth);
    
    // Atributos de Combate
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage")
    FGameplayAttributeData AttackPower;
    ATTRIBUTE_ACCESSORS(UHivaAttributeSet, AttackPower)
    
    UPROPERTY(BlueprintReadOnly, Category = "Attributes|Damage")
    FGameplayAttributeData DefensePower;
    ATTRIBUTE_ACCESSORS(UHivaAttributeSet, DefensePower)
};
```

**Macro ATTRIBUTE_ACCESSORS**:
Esta macro gera automaticamente getters, setters e initers para cada atributo:
- `GetCurrentHealth()` / `SetCurrentHealth()` / `InitCurrentHealth()`
- `GetMaxHealth()` / `SetMaxHealth()` / `InitMaxHealth()`
- E assim por diante...

#### `UHivaGameplayAbility` - Base para Todas as Habilidades

**Arquivo**: `Source/Hiva/Public/AbilitySystem/Abilities/HivaGameplayAbility.h`

Classe base personalizada que estende `UGameplayAbility` com funcionalidades específicas do projeto.

**Políticas de Ativação**:
```cpp
UENUM()
enum class EHivaAbilityActivationPolity : uint8
{
    OnTriggered,  // Ativada quando solicitada
    OnGiven      // Ativada automaticamente quando concedida
};
```

**Ciclo de Vida das Habilidades**:
```cpp
void UHivaGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, 
                                       const FGameplayAbilitySpec& Spec)
{
    Super::OnGiveAbility(ActorInfo, Spec);
    
    if (AbilityActivationPolicy == EHivaAbilityActivationPolity::OnGiven)
    {
        // Ativa automaticamente se configurado
        if (ActorInfo && !Spec.IsActive())
        {
            ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
        }
    }
}

void UHivaGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, 
                                    const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, 
                                    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
    
    if (AbilityActivationPolicy == EHivaAbilityActivationPolity::OnGiven)
    {
        // Remove a habilidade quando termina
        if (ActorInfo)
        {
            ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
        }
    }
}
```

**Métodos de Conveniência**:
```cpp
// Acesso fácil ao componente de combate
UFUNCTION(BlueprintPure, Category = "HivaAbility")
UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

// Acesso ao Ability System Component específico do projeto
UFUNCTION(BlueprintPure, Category = "HivaAbility")
UHivaAbilitySystemComponent* GetHivaAbilitySystemComponentFromActorInfo() const
{
    return Cast<UHivaAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
```

### 3. Sistema de Combate - Arquitetura Modular

O sistema de combate é construído em camadas, permitindo especialização para diferentes tipos de personagens.

#### `UPawnExtentionComponentBase` - A Base de Todos os Componentes

**Arquivo**: `Source/Hiva/Public/Components/PawnExtentionComponentBase.h`

Esta classe base fornece métodos template seguros para acesso a Pawn e Controller, garantindo type-safety através de static_assert.

**Implementação Template Segura**:
```cpp
template <class T>
T* GetOwningPawn() const
{	
    static_assert(TPointerIsConvertibleFromTo<T,APawn>::Value,
                 "'T' Template Parameter to GetPawn must be derived from APawn");
    return CastChecked<T>(GetOwner());
}

template <class T>
T* GetOwningController() const
{
    static_assert(TPointerIsConvertibleFromTo<T,AController>::Value,
                 "'T' Template Parameter to GetController must be derived from AController");
    return GetOwningPawn<APawn>()->GetController<T>();
}
```

**Vantagens desta Abordagem**:
- **Type Safety**: Compile-time checking previne erros de casting
- **Performance**: CastChecked é mais rápido que Cast com verificações
- **Flexibilidade**: Templates permitem acesso tipado a diferentes tipos de Pawn/Controller

#### `UPawnCombatComponent` - Sistema de Armas Universal

**Arquivo**: `Source/Hiva/Public/Components/Combat/PawnCombatComponent.h`

Componente base que gerencia armas para qualquer tipo de personagem (jogador ou inimigo).

**Sistema de Registro de Armas**:
```cpp
void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, 
                                                AHivaWeaponBase* InWeaponToRegister, 
                                                bool bRegisterAsEquippedWeaponOnSpawn)
{
    // Registra a arma no mapa usando Gameplay Tag como chave
    CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
    
    // Opcionalmente equipa a arma automaticamente
    if (bRegisterAsEquippedWeaponOnSpawn)
    {
        CurrentEquippedWeaponTag = InWeaponTagToRegister;
    }
}
```

**Sistema de Busca de Armas**:
```cpp
AHivaWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
    {
        if (AHivaWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
        {
            return *FoundWeapon;
        }
    }
    return nullptr;
}

AHivaWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
    return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
```

**Estrutura de Dados**:
```cpp
private:
    // Mapa que associa Gameplay Tags a armas específicas
    TMap<FGameplayTag, AHivaWeaponBase*> CharacterCarriedWeaponMap;
    
public:
    // Tag da arma atualmente equipada
    UPROPERTY(BlueprintReadWrite, Category = "Player|Combat")
    FGameplayTag CurrentEquippedWeaponTag;
```

#### `UPlayerCombatComponent` - Especialização para Jogador

**Arquivo**: `Source/Hiva/Public/Components/Combat/PlayerCombatComponent.h`

Estende o componente base com funcionalidades específicas para o jogador.

**Método Especializado**:
```cpp
AHivaPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
    // Cast específico para armas do jogador
    return Cast<AHivaPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}
```

**Vantagens da Herança**:
- **Reutilização**: Herda toda funcionalidade base
- **Especialização**: Adiciona métodos específicos para armas do jogador
- **Type Safety**: Cast específico garante tipo correto

### 4. Sistema de Armas - Hierarquia e Funcionalidades

O sistema de armas é projetado com uma hierarquia clara que permite diferentes tipos de armas com funcionalidades específicas.

#### `AHivaWeaponBase` - A Fundação de Todas as Armas

**Arquivo**: `Source/Hiva/Public/Itens/Weapons/HivaWeaponBase.h`

Classe base que define a estrutura fundamental de todas as armas no jogo.

**Componentes Básicos**:
```cpp
class HIVA_API AHivaWeaponBase : public AActor
{
protected:
    // Mesh visual da arma
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
    UStaticMeshComponent* WeaponMesh;
    
    // Caixa de colisão para detecção de hits
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
    UBoxComponent* WeaponCollisionBox;
    
public:
    // Acesso rápido à caixa de colisão
    FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
};
```

**Características da Implementação**:
- **Herança de AActor**: Permite posicionamento independente no mundo
- **Componentes Modulares**: Mesh e colisão separados para flexibilidade
- **Blueprint Integration**: Propriedades expostas para configuração visual

#### `AHivaPlayerWeapon` - Armas Especializadas para Jogador

**Arquivo**: `Source/Hiva/Public/Itens/Weapons/HivaPlayerWeapon.h`

Estende a arma base com dados específicos para o jogador, incluindo habilidades e animações.

**Estrutura de Dados da Arma**:
```cpp
class HIVA_API AHivaPlayerWeapon : public AHivaWeaponBase
{
public:
    // Dados específicos da arma do jogador
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
    FHivaPlayerWeaponData PlayerWeaponData;
};
```

**Estrutura `FHivaPlayerWeaponData`**:
```cpp
USTRUCT(BlueprintType)
struct FHivaPlayerWeaponData
{
    GENERATED_BODY()
    
    // Camada de animação específica da arma
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UHivaPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
    
    // Contexto de input específico da arma
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputMappingContext* WeaponInputMappingContext;
    
    // Habilidades padrão da arma
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty = "InputTag"))
    TArray<FHivaPlayerAbilitySet> DefaultWeaponAbilities;
};
```

**Estrutura `FHivaPlayerAbilitySet`**:
```cpp
USTRUCT(BlueprintType)
struct FHivaPlayerAbilitySet
{
    GENERATED_BODY()
    
    // Tag de input para ativar a habilidade
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;
    
    // Classe da habilidade a ser adicionada
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "AbilitySet"))
    TSubclassOf<UHivaGameplayAbility> AbilityToAdd;
    
    // Validação da estrutura
    bool IsValid() const
    {
        return InputTag.IsValid() && AbilityToAdd;
    }
};
```

### 5. Sistema de Input - Enhanced Input com Gameplay Tags

#### `UHivaInputComponent` - Input Component Personalizado

**Arquivo**: `Source/Hiva/Public/Components/Input/HivaInputComponent.h`

Estende o `UEnhancedInputComponent` com funcionalidades específicas para binding de habilidades.

**Binding de Ações Nativas**:
```cpp
template <class UserObject, typename CallbackFunc>
void UHivaInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, 
                                               const FGameplayTag& InInputTag, 
                                               ETriggerEvent TriggerEvent,
                                               UserObject* ContextObject, 
                                               CallbackFunc CallbackFunction)
{
    checkf(InInputConfig, TEXT("Input Config must not be null when binding native input action."));
    
    if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
    {
        BindAction(FoundAction, TriggerEvent, ContextObject, CallbackFunction);
    }
}
```

**Binding de Habilidades**:
```cpp
template <class UserObject, typename CallbackFunc>
void UHivaInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, 
                                               UserObject* ContextObject,
                                               CallbackFunc AbilityInputPressedCallbackFunction, 
                                               CallbackFunc AbilityInputReleasedCallbackFunction)
{
    checkf(InInputConfig, TEXT("Input Config must not be null when binding ability input action."));
    
    for (const FHivaInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
    {
        if (AbilityInputActionConfig.IsValid())
        {
            // Binding para pressionar
            BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Started, 
                     ContextObject, AbilityInputPressedCallbackFunction, 
                     AbilityInputActionConfig.InputTag);
            
            // Binding para soltar
            BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, 
                     ContextObject, AbilityInputReleasedCallbackFunction, 
                     AbilityInputActionConfig.InputTag);
        }
    }
}
```

### 6. Sistema de Data Assets - Configuração Dinâmica

#### `UDataAsset_StartUpDataBase` - Configuração de Inicialização

**Arquivo**: `Source/Hiva/Public/DataAssets/StartUpData/DataAsset_StartUpDataBase.h`

Data Asset base que gerencia a inicialização de personagens com habilidades e efeitos.

**Estrutura de Dados**:
```cpp
class HIVA_API UDataAsset_StartUpDataBase : public UDataAsset
{
protected:
    // Habilidades que são ativadas automaticamente quando concedidas
    UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
    TArray<TSubclassOf<UHivaGameplayAbility>> ActivateOnGivenAbilities;
    
    // Habilidades reativas (ativadas por eventos)
    UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
    TArray<TSubclassOf<UHivaGameplayAbility>> ReactiveAbilities;
    
    // Efeitos de gameplay aplicados na inicialização
    UPROPERTY(EditDefaultsOnly, Category = "StartUp Data")
    TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;
};
```

**Método de Aplicação**:
```cpp
void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, 
                                                           int32 ApplyLevel)
{
    check(InAbilitySystemComponentToGive);
    
    // Concede habilidades que são ativadas automaticamente
    GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponentToGive, ApplyLevel);
    
    // Concede habilidades reativas
    GrantAbilities(ReactiveAbilities, InAbilitySystemComponentToGive, ApplyLevel);
    
    // Aplica efeitos de gameplay
    if (!StartUpGameplayEffects.IsEmpty())
    {
        for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
        {
            if(!EffectClass) continue;
            
            UGameplayEffect* EffectClassDefaultObject = EffectClass->GetDefaultObject<UGameplayEffect>();
            
            InAbilitySystemComponentToGive->ApplyGameplayEffectToSelf(
                EffectClassDefaultObject,
                ApplyLevel,
                InAbilitySystemComponentToGive->MakeEffectContext()
            );
        }
    }
}
```

**Método de Concessão de Habilidades**:
```cpp
void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UHivaGameplayAbility>>& InAbilitiesToGive,
                                               UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, 
                                               int32 ApplyLevel)
{
    if (InAbilitiesToGive.IsEmpty()) return;
    
    for (const TSubclassOf<UHivaGameplayAbility>& Ability : InAbilitiesToGive)
    {
        if (!Ability) continue;
        
        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = InAbilitySystemComponentToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        
        InAbilitySystemComponentToGive->GiveAbility(AbilitySpec);
    }
}
```

### 7. Sistema de Gameplay Tags - Organização e Categorização

#### `HivaGameplayTags` - Namespace Centralizado

**Arquivo**: `Source/Hiva/Public/HivaGameplayTags.h`

O sistema de Gameplay Tags é fundamental para a organização e identificação de elementos do jogo. Todas as tags são declaradas em um namespace centralizado.

**Estrutura das Tags**:
```cpp
namespace HivaGameplayTags
{
    /** Input Tags - Tags para ações de input **/
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeCharacter)
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Gloves)
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Gloves)
    
    /** Player Tags - Tags específicas do jogador **/
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Gloves);
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Gloves);
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Gloves);

    /** Enemy Tags - Tags específicas dos inimigos **/
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon_Gloves);
    
    /** Test Event Tags - Tags para eventos de teste **/
    HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Test);
}
```

**Categorização das Tags**:

1. **Input Tags**: Identificam ações de input do jogador
   - `InputTag_Move`: Movimento do personagem
   - `InputTag_Look`: Rotação da câmera
   - `InputTag_ChangeCharacter`: Troca de personagem
   - `InputTag_LightAttack_Gloves`: Ataque leve com luvas
   - `InputTag_HeavyAttack_Gloves`: Ataque pesado com luvas

2. **Player Tags**: Identificam elementos específicos do jogador
   - `Player_Weapon_Gloves`: Identificação das luvas como arma
   - `Player_Ability_Attack_Light_Gloves`: Habilidade de ataque leve
   - `Player_Ability_Attack_Heavy_Gloves`: Habilidade de ataque pesado

3. **Enemy Tags**: Identificam elementos específicos dos inimigos
   - `Enemy_Weapon_Gloves`: Luvas dos inimigos

4. **Event Tags**: Identificam eventos do sistema
   - `Player_Event_Test`: Evento de teste para debug

**Vantagens do Sistema de Tags**:
- **Organização**: Tags são categorizadas e organizadas hierarquicamente
- **Performance**: Gameplay Tags são otimizadas para comparação rápida
- **Flexibilidade**: Fácil adição de novas tags sem modificar código
- **Debugging**: Tags facilitam identificação de problemas
- **Networking**: Tags são replicadas automaticamente em multiplayer

## Fluxos de Execução e Inicialização

### 1. Fluxo de Inicialização do Personagem

#### Para Personagens do Jogador:
```
1. Construtor do Personagem
   ├── Criação dos componentes básicos
   ├── Configuração da câmera
   ├── Configuração do movimento
   └── Criação do componente de combate

2. PossessedBy()
   ├── Chamada do método da classe base
   ├── Carregamento do Data Asset de inicialização
   └── Aplicação de habilidades e efeitos

3. SetupPlayerInputComponent()
   ├── Configuração do Enhanced Input
   ├── Binding de ações nativas
   └── Binding de habilidades

4. BeginPlay()
   └── Inicialização final do personagem
```

#### Para Personagens Inimigos:
```
1. Construtor do Personagem
   ├── Configuração de IA (AutoPossessAI)
   ├── Configuração de movimento otimizada
   └── Criação do componente de combate

2. PossessedBy()
   ├── Chamada do método da classe base
   └── Inicialização assíncrona de dados

3. InitEnemyStartupData()
   ├── Carregamento assíncrono do Data Asset
   ├── Callback de aplicação de habilidades
   └── Log de confirmação
```

### 2. Fluxo de Ativação de Habilidades

```
1. Input do Jogador
   ├── Detecção de input via Enhanced Input
   ├── Chamada do callback de habilidade
   └── Passagem da Gameplay Tag

2. Ability System Component
   ├── Recebe a tag de input
   ├── Procura por habilidades correspondentes
   └── Tenta ativar a habilidade

3. Gameplay Ability
   ├── Verificação de pré-condições
   ├── Execução da habilidade
   └── Aplicação de efeitos
```

### 3. Fluxo de Sistema de Armas

```
1. Spawn da Arma
   ├── Criação da arma no mundo
   ├── Configuração de mesh e colisão
   └── Registro no componente de combate

2. Registro no Combat Component
   ├── Adição ao mapa de armas
   ├── Associação com Gameplay Tag
   └── Equipamento automático (opcional)

3. Uso da Arma
   ├── Busca da arma por tag
   ├── Verificação de disponibilidade
   └── Execução de habilidades específicas
```

## Dependências e Configuração de Build

### Módulos Principais

**Arquivo**: `Source/Hiva/Hiva.Build.cs`

```csharp
public class Hiva : ModuleRules
{
    public Hiva(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
    
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core",              // Funcionalidades básicas do Unreal
            "CoreUObject",       // Sistema de objetos e reflection
            "Engine",            // Motor principal do Unreal Engine
            "InputCore",         // Sistema de input básico
            "EnhancedInput",     // Sistema de input aprimorado
            "GameplayTags",      // Sistema de Gameplay Tags
            "GameplayTasks"      // Sistema de tarefas de gameplay
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
```

**Análise das Dependências**:

1. **Core**: Fornece funcionalidades fundamentais como logging, strings, containers
2. **CoreUObject**: Sistema de objetos com reflection, garbage collection, serialização
3. **Engine**: Motor principal com componentes, actors, world, physics
4. **InputCore**: Sistema básico de input (teclado, mouse, gamepad)
5. **EnhancedInput**: Sistema moderno de input com actions, triggers, modifiers
6. **GameplayTags**: Sistema de tags para organização e identificação
7. **GameplayTasks**: Sistema de tarefas para AI e gameplay complexo

### Configurações de Build

- **PCH Usage**: `UseExplicitOrSharedPCHs` para otimização de compilação
- **Public Dependencies**: Módulos acessíveis publicamente
- **Private Dependencies**: Módulos internos (atualmente vazios)

## Funcionalidades Principais Detalhadas

### 1. Sistema de Movimento Avançado

**Características**:
- **Movimento Relativo à Câmera**: Movimento baseado na direção da câmera
- **Configurações Personalizáveis**: Velocidade, rotação, desaceleração ajustáveis
- **Orientação Automática**: Personagem se orienta na direção do movimento
- **Controle de Câmera**: Rotação independente da câmera

**Implementação**:
```cpp
// Configuração no construtor
GetCharacterMovement()->bOrientRotationToMovement = true;
GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
GetCharacterMovement()->MaxWalkSpeed = 400.f;
GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

// Movimento baseado na câmera
const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
AddMovementInput(ForwardDirection, MovementVector.Y);
```

### 2. Sistema de Combate Modular

**Arquitetura**:
- **Componente Base**: `UPawnCombatComponent` para funcionalidades universais
- **Especializações**: `UPlayerCombatComponent` e `UEnemyCombatComponent`
- **Sistema de Armas**: Mapa de armas com Gameplay Tags
- **Gestão de Equipamento**: Sistema de arma atual equipada

**Funcionalidades**:
- Registro e busca de armas por tag
- Sistema de equipamento automático
- Integração com sistema de habilidades
- Suporte a múltiplas armas simultâneas

### 3. Sistema de Habilidades (GAS) Completo

**Componentes Principais**:
- **Ability System Component**: Gerenciamento central de habilidades
- **Attribute Set**: Atributos dos personagens (vida, ataque, defesa)
- **Gameplay Abilities**: Habilidades específicas do jogo
- **Gameplay Effects**: Efeitos temporários e permanentes

**Tipos de Habilidades**:
- **Ataques Leves**: Ataques rápidos com luvas
- **Ataques Pesados**: Ataques poderosos com luvas
- **Mudança de Personagem**: Sistema de troca de personagens

### 4. Sistema de IA Inteligente

**Características**:
- **Auto-Possessão**: Inimigos são automaticamente controlados por IA
- **Carregamento Assíncrono**: Dados carregados sem travar o jogo
- **Configurações Otimizadas**: Movimento e comportamento específicos para IA
- **Integração com GAS**: Inimigos também usam sistema de habilidades

**Otimizações**:
- Carregamento assíncrono de Data Assets
- Configurações de movimento específicas para IA
- Sistema de debug integrado

### 5. Sistema de Input Robusto

**Enhanced Input Integration**:
- **Input Actions**: Ações configuráveis no editor
- **Input Mapping Contexts**: Contextos específicos para diferentes situações
- **Gameplay Tags**: Binding de habilidades via tags
- **Template System**: Sistema de templates para binding automático

**Funcionalidades**:
- Binding automático de ações nativas
- Binding automático de habilidades
- Suporte a múltiplos contextos de input
- Integração com sistema de armas

## Estrutura de Arquivos Detalhada

```
Source/Hiva/
├── Public/                          # Headers públicos
│   ├── Characters/                  # Sistema de personagens
│   │   ├── HivaBaseCharacter.h     # Classe base de personagens
│   │   ├── HivaPlayerCharacter.h   # Personagem do jogador
│   │   └── HivaEnemyCharacter.h     # Personagem inimigo
│   ├── AbilitySystem/              # Gameplay Ability System
│   │   ├── HivaAbilitySystemComponent.h    # Componente principal do GAS
│   │   ├── HivaAttributeSet.h              # Atributos dos personagens
│   │   └── Abilities/
│   │       └── HivaGameplayAbility.h       # Base para habilidades
│   ├── Components/                  # Componentes modulares
│   │   ├── Combat/                 # Sistema de combate
│   │   │   ├── PawnCombatComponent.h       # Base de combate
│   │   │   ├── PlayerCombatComponent.h     # Combate do jogador
│   │   │   └── EnemyCombatComponent.h     # Combate do inimigo
│   │   ├── Input/
│   │   │   └── HivaInputComponent.h        # Input personalizado
│   │   └── PawnExtentionComponentBase.h   # Base para componentes
│   ├── Itens/Weapons/              # Sistema de armas
│   │   ├── HivaWeaponBase.h        # Base para armas
│   │   └── HivaPlayerWeapon.h      # Arma do jogador
│   ├── DataAssets/                 # Assets de dados
│   │   ├── StartUpData/
│   │   │   └── DataAsset_StartUpDataBase.h # Base para dados de inicialização
│   │   └── Input/
│   │       └── DataAsset_InputConfig.h    # Configuração de input
│   ├── HivaTypes/                  # Estruturas e tipos
│   │   └── HivaStructTypes.h       # Estruturas de dados
│   ├── GameModes/
│   │   └── HivaGameMode.h          # Modo de jogo principal
│   ├── Controllers/
│   │   └── HivaPlayerController.h  # Controlador do jogador
│   └── HivaGameplayTags.h         # Sistema de tags
├── Private/                        # Implementações (.cpp)
│   └── [Mesma estrutura dos headers]
├── Hiva.Build.cs                   # Configuração de build
├── Hiva.cpp                       # Arquivo principal do módulo
└── Hiva.h                         # Header principal do módulo
```

## Características Técnicas Avançadas

### 1. Arquitetura Baseada em Componentes
- **Modularidade**: Cada funcionalidade é um componente independente
- **Reutilização**: Componentes podem ser reutilizados em diferentes contextos
- **Manutenibilidade**: Mudanças isoladas não afetam outros sistemas
- **Extensibilidade**: Fácil adição de novas funcionalidades

### 2. Sistema de Templates Seguro
- **Type Safety**: Verificação de tipos em tempo de compilação
- **Performance**: CastChecked mais rápido que verificações de runtime
- **Flexibilidade**: Templates permitem diferentes tipos de Pawn/Controller
- **Debugging**: Static_assert fornece mensagens claras de erro

### 3. Data-Driven Design
- **Configurabilidade**: Comportamentos configuráveis via Data Assets
- **Iteração Rápida**: Mudanças sem recompilação
- **Separação de Responsabilidades**: Código separado de dados
- **Flexibilidade**: Fácil criação de variações de personagens

### 4. Otimizações de Performance
- **Carregamento Assíncrono**: Assets carregados sem travar o jogo
- **Gameplay Tags**: Comparações otimizadas para identificação
- **Component Caching**: Acesso rápido a componentes frequentemente usados
- **Memory Management**: Gestão eficiente de memória com Unreal's GC

### 5. Sistema de Debug Integrado
- **Debug Helper**: Sistema de debug personalizado
- **Logging**: Logs estruturados para diferentes sistemas
- **Visual Debugging**: Informações visuais no editor
- **Performance Profiling**: Ferramentas para análise de performance

## Considerações de Desenvolvimento

### Boas Práticas Implementadas
1. **SOLID Principles**: Código seguindo princípios de design sólido
2. **RAII**: Resource Acquisition Is Initialization
3. **Const Correctness**: Uso correto de const onde apropriado
4. **Smart Pointers**: Uso de ponteiros inteligentes do Unreal
5. **Error Handling**: Verificações robustas de null pointers

### Padrões de Design Utilizados
1. **Component Pattern**: Funcionalidades encapsuladas em componentes
2. **Template Method**: Métodos base com implementações específicas
3. **Strategy Pattern**: Diferentes estratégias de habilidade
4. **Factory Pattern**: Criação de objetos através de Data Assets
5. **Observer Pattern**: Sistema de eventos com Gameplay Tags

### Extensibilidade
- **Novos Personagens**: Fácil criação através de herança
- **Novas Armas**: Sistema modular permite novas armas
- **Novas Habilidades**: Framework GAS facilita novas habilidades
- **Novos Tipos de Inimigos**: IA modular permite diferentes comportamentos
- **Novos Modos de Jogo**: GameMode base permite variações

Este projeto representa uma implementação robusta e bem arquitetada de sistemas de combate em Unreal Engine 5, demonstrando as melhores práticas de desenvolvimento e integração com os sistemas nativos do engine.
