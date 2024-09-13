#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

UCLASS()
class PROJECT_API UScoreWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPlayer1Score(int32 Score);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPlayer2Score(int32 Score);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Player1ScoreText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Player2ScoreText;
};
