# Documentação do Projeto Hiva

## Visão Geral

**Hiva** é um projeto de jogo desenvolvido em Unreal Engine 5.5, criado por Eryck Torres. O projeto implementa um sistema de combate baseado em capoeira com mecânicas avançadas de gameplay abilities, sistema de armas, e animações complexas.

## Informações Técnicas

- **Engine**: Unreal Engine 5.5
- **Linguagem**: C++
- **Arquitetura**: Sistema de Componentes com Gameplay Ability System (GAS)
- **Plataforma**: Windows (Win64)
- **Versão do Projeto**: 1.0

## Estrutura do Projeto

### 1. Arquivos de Configuração

#### Hiva.uproject
O arquivo principal do projeto que define:
- **Engine Association**: UE 5.5
- **Módulos**: Hiva (Runtime)
- **Dependências**: Engine, EnhancedInput, GameplayAbilities
- **Plugins**: ModelingToolsEditorMode, GameplayAbilities

#### Hiva.Build.cs
Configurações de compilação que incluem:
- **Dependências Públicas**: Core, CoreUObject, Engine, InputCore, EnhancedInput, GameplayTags, GameplayTasks
- **PCH Usage**: UseExplicitOrSharedPCHs

### 2. Arquitetura do Sistema

#### 2.1 Sistema de Gameplay Abilities (GAS)
O projeto utiliza o Gameplay Ability System da Epic Games para gerenciar habilidades e mecânicas de combate:

- **HivaAbilitySystemComponent**: Componente principal que gerencia todas as habilidades
- **HivaGameplayAbility**: Classe base para todas as habilidades do jogo
- **HivaAttributeSet**: Sistema de atributos dos personagens

#### 2.2 Sistema de Tags
Implementa um sistema robusto de Gameplay Tags para categorização:

```cpp
namespace HivaGameplayTags
{
    // Input Tags
    InputTag_Move, InputTag_Look, InputTag_Capoeira
    InputTag_ChangeCharacter, InputTag_LightAttack_Gloves, InputTag_HeavyAttack_Gloves
    
    // Player Tags
    Player_Weapon_Gloves, Player_Ability_Attack_Light_Gloves, Player_Ability_Attack_Heavy_Gloves
    
    // Event Tags
    Player_Event_Test
}
```

### 3. Sistema de Personagens

#### 3.1 Hierarquia de Classes

```
AHivaBaseCharacter (Base)
    └── AHivaPlayerCharacter (Player)
```

#### 3.2 HivaBaseCharacter
- **Herança**: ACharacter + IAbilitySystemInterface
- **Componentes**: HivaAbilitySystemComponent, HivaAttributeSet
- **Funcionalidades**: Sistema de habilidades, atributos, dados de inicialização

#### 3.3 HivaPlayerCharacter
- **Extensão**: Funcionalidades específicas do jogador
- **Integração**: Sistema de combate, armas, animações

### 4. Sistema de Combate

#### 4.1 Componentes de Combate

- **PawnCombatComponent**: Gerenciamento geral de combate
- **PlayerCombatComponent**: Combate específico do jogador
- **Funcionalidades**: Registro de armas, equipamento, gerenciamento de armas carregadas

#### 4.2 Sistema de Armas

- **HivaWeaponBase**: Classe base para todas as armas
- **Componentes**: WeaponMesh (StaticMesh), WeaponCollisionBox (BoxComponent)
- **HivaPlayerWeapon**: Arma específica do jogador

### 5. Sistema de Input

#### 5.1 Enhanced Input
Utiliza o sistema Enhanced Input da UE5 para:
- Mapeamento de controles
- Contextos de input específicos por arma
- Tags de input para habilidades

#### 5.2 Mapeamento de Input
- **Movimento**: InputTag_Move, InputTag_Look
- **Combate**: InputTag_Capoeira, InputTag_LightAttack_Gloves, InputTag_HeavyAttack_Gloves
- **Sistema**: InputTag_ChangeCharacter

### 6. Sistema de Animação

#### 6.1 Hierarquia de Anim Instances

```
UHivaBaseAnimInstance (Base)
    └── UHivaCharacterAnimInstance (Character)
        └── UHivaPlayerLinkedAnimLayer (Player)
```

#### 6.2 HivaCharacterAnimInstance
- **Funcionalidades**: Atualização de animação em thread separada
- **Dados**: Velocidade no solo, aceleração
- **Performance**: NativeThreadSafeUpdateAnimation para otimização

### 7. Sistema de Data Assets

#### 7.1 Estrutura de Dados

- **DataAsset_StartUpDataBase**: Dados de inicialização base
- **MyDataAsset_PlayerStartUpData**: Dados específicos do jogador
- **Funcionalidades**: Habilidades ativas, habilidades reativas

#### 7.2 Tipos de Estruturas

```cpp
// Conjunto de habilidades do jogador
struct FHivaPlayerAbilitySet
{
    FGameplayTag InputTag;
    TSubclassOf<UHivaGameplayAbility> AbilityToAdd;
}

// Dados da arma do jogador
struct FHivaPlayerWeaponData
{
    TSubclassOf<UHivaPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
    UInputMappingContext* WeaponInputMappingContext;
    TArray<FHivaPlayerAbilitySet> DefaultWeaponAbilities;
}
```

### 8. Sistema de Habilidades

#### 8.1 Políticas de Ativação

```cpp
enum class EHivaAbilityActivationPolity : uint8
{
    OnTriggered,  // Ativa quando acionada
    OnGiven       // Ativa quando concedida
}
```

#### 8.2 Funcionalidades das Habilidades
- **GrantPlayerWeaponAbilities**: Concede habilidades de arma
- **OnAbilityInputPressed/Released**: Gerenciamento de input de habilidades
- **Integração com Combat Component**: Acesso ao sistema de combate

### 9. Estrutura de Diretórios

```
Source/Hiva/
├── Public/
│   ├── AbilitySystem/
│   │   ├── Abilities/
│   │   ├── HivaAbilitySystemComponent.h
│   │   └── HivaAttributeSet.h
│   ├── Characters/
│   │   ├── HivaBaseCharacter.h
│   │   └── HivaPlayerCharacter.h
│   ├── Components/
│   │   ├── Combat/
│   │   ├── Input/
│   │   └── PawnExtentionComponentBase.h
│   ├── DataAssets/
│   │   ├── Characters/
│   │   ├── Input/
│   │   └── StartUpData/
│   ├── HivaTypes/
│   │   └── HivaStructTypes.h
│   ├── Itens/
│   │   └── Weapons/
│   ├── AnimInstances/
│   │   └── Player/
│   ├── Controllers/
│   ├── GameModes/
│   ├── HivaGameplayTags.h
│   └── HivaDebugHelper.h
└── Private/
    └── [Implementações correspondentes]
```

### 10. Sistema de Debug

#### 10.1 HivaDebugHelper
Ferramentas de debug para desenvolvimento e teste do sistema

### 11. Funcionalidades Principais

#### 11.1 Sistema de Combate
- **Combate com Capoeira**: Movimentos específicos de capoeira
- **Sistema de Armas**: Luvas com ataques leves e pesados
- **Troca de Personagem**: Sistema para alternar entre personagens

#### 11.2 Sistema de Habilidades
- **Habilidades de Arma**: Habilidades específicas por tipo de arma
- **Habilidades Reativas**: Habilidades que respondem a eventos
- **Sistema de Níveis**: Aplicação de habilidades com diferentes níveis

#### 11.3 Sistema de Animação
- **Camadas de Animação**: Sistema de camadas para diferentes estados
- **Performance Otimizada**: Atualizações em thread separada
- **Integração com Movimento**: Sincronização com sistema de movimento

### 12. Configurações de Projeto

#### 12.1 Configurações do Editor
- **DefaultEditor.ini**: Configurações específicas do editor
- **DefaultEngine.ini**: Configurações do motor
- **DefaultGame.ini**: Configurações do jogo
- **DefaultInput.ini**: Configurações de input

#### 12.2 Plugins Ativos
- **GameplayAbilities**: Sistema de habilidades
- **ModelingToolsEditorMode**: Ferramentas de modelagem
- **EnhancedInput**: Sistema de input avançado

### 13. Dependências Externas

#### 13.1 Módulos do Unreal Engine
- **Core**: Funcionalidades básicas
- **CoreUObject**: Sistema de objetos
- **Engine**: Funcionalidades do motor
- **InputCore**: Sistema de input básico
- **EnhancedInput**: Sistema de input avançado
- **GameplayTags**: Sistema de tags
- **GameplayTasks**: Sistema de tarefas

### 14. Considerações de Performance

#### 14.1 Otimizações Implementadas
- **PCH Usage**: Uso de precompiled headers
- **Thread-Safe Animation**: Atualizações de animação em thread separada
- **Efficient Tag System**: Sistema de tags otimizado

#### 14.2 Boas Práticas
- **Component-Based Architecture**: Arquitetura baseada em componentes
- **Data-Driven Design**: Design orientado a dados com Data Assets
- **Modular Ability System**: Sistema de habilidades modular

### 15. Roadmap e Funcionalidades Futuras

#### 15.1 Funcionalidades Planejadas
- Sistema de combos mais complexo
- Mais tipos de armas
- Sistema de multiplayer
- Sistema de progressão de personagem

#### 15.2 Melhorias Técnicas
- Otimizações de performance adicionais
- Sistema de partículas para efeitos visuais
- Sistema de áudio avançado
- Integração com sistemas de física

### 16. Guia de Desenvolvimento

#### 16.1 Adicionando Novas Habilidades
1. Criar nova classe herdando de `UHivaGameplayAbility`
2. Definir tags de input apropriadas
3. Configurar política de ativação
4. Adicionar ao Data Asset correspondente

#### 16.2 Adicionando Novas Armas
1. Criar nova classe herdando de `AHivaWeaponBase`
2. Configurar mesh e colisão
3. Definir habilidades específicas da arma
4. Configurar contexto de input

#### 16.3 Adicionando Novos Personagens
1. Criar nova classe herdando de `AHivaBaseCharacter`
2. Configurar Data Asset de inicialização
3. Definir habilidades e atributos específicos
4. Configurar animações e movimentos

### 17. Troubleshooting

#### 17.1 Problemas Comuns
- **Habilidades não funcionando**: Verificar se o AbilitySystemComponent está configurado
- **Input não respondendo**: Verificar mapeamento de Enhanced Input
- **Animações travando**: Verificar configuração do AnimInstance

#### 17.2 Debug
- Usar `HivaDebugHelper` para informações de debug
- Verificar logs do Unreal Engine
- Utilizar ferramentas de debug do GAS

### 18. Conclusão

O projeto Hiva representa uma implementação robusta e bem estruturada de um sistema de combate baseado em capoeira, utilizando as melhores práticas do Unreal Engine 5.5. A arquitetura modular e baseada em componentes permite fácil extensão e manutenção, enquanto o sistema de Gameplay Abilities fornece uma base sólida para mecânicas de jogo complexas.

O projeto demonstra proficiência em:
- Arquitetura de sistemas de jogo
- Implementação de Gameplay Ability System
- Sistema de input avançado
- Otimização de performance
- Design orientado a dados

---

**Desenvolvido por**: Eryck Torres  
**Versão da Documentação**: 1.0  
**Data de Criação**: Dezembro 2024  
**Última Atualização**: Dezembro 2024
