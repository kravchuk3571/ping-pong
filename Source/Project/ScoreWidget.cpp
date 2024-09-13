#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::SetPlayer1Score(int32 Score)
{
    if (Player1ScoreText)
    {
        Player1ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
    }
}

void UScoreWidget::SetPlayer2Score(int32 Score)
{
    if (Player2ScoreText)
    {
        Player2ScoreText->SetText(FText::FromString(FString::FromInt(Score)));
    }
}
