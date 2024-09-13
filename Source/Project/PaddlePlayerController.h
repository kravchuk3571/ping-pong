#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "PaddlePlayerController.generated.h"

UENUM(BlueprintType)
enum class EPlayerID : uint8
{
    Player1 UMETA(DisplayName = "Player 1"),
    Player2 UMETA(DisplayName = "Player 2")
};

UCLASS()
class PROJECT_API APaddlePlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

public:
    void AddScore(EPlayerID PlayerID);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> ScoreWidgetClass;

private:
    void SetupInput();
    void SetupCamera();
    void CreateScoreWidgetIfLocal();
    void UpdateScoreUI();
    void Move(const FInputActionValue& Value);

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputMappingContext* PlayerMappingContext = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    class UInputAction* MoveAction = nullptr;

    UPROPERTY()
    class UScoreWidget* ScoreWidget = nullptr;

    class APaddlePawn* PaddlePawn = nullptr;
    int32 Player1Score = 0;
    int32 Player2Score = 0;
};
