// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomImageWidget.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UCustomImageWidget::NativeConstruct()
{
    Super::NativeConstruct();
    CurrentHoveredIndex = -1;
}

void UCustomImageWidget::RegisterImage(UImage* Image)
{
    if (Image && !Images.Contains(Image))
    {
        Images.Add(Image);
    }
}

FReply UCustomImageWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    int32 HoveredIndex = FindImageUnderMouse(InGeometry, InMouseEvent);

    if (HoveredIndex != CurrentHoveredIndex)
    {
        // Если был ховер на другом Image - уведомляем о уходе
        if (CurrentHoveredIndex != -1)
        {
            OnImageUnhovered(CurrentHoveredIndex);
        }

        // Если нашли новый Image - уведомляем о ховере
        if (HoveredIndex != -1)
        {
            OnImageHovered(HoveredIndex);
        }

        CurrentHoveredIndex = HoveredIndex;
    }

    return Super::NativeOnMouseMove(InGeometry, InMouseEvent);
}

int32 UCustomImageWidget::FindImageUnderMouse(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    // Проверяем с конца (верхние элементы по Z-order)
    for (int32 i = Images.Num() - 1; i >= 0; i--)
    {
        if (Images[i] && IsMouseOverImage(Images[i], InGeometry, InMouseEvent))
        {
            return i;
        }
    }
    return -1;
}

bool UCustomImageWidget::IsMouseOverImage(UImage* Image, const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (!Image) return false;

    FVector2D MouseAbsolutePos = InMouseEvent.GetScreenSpacePosition();
    FGeometry ImageGeometry = Image->GetCachedGeometry();
    FVector2D LocalMousePos = ImageGeometry.AbsoluteToLocal(MouseAbsolutePos);
    FVector2D ImageSize = ImageGeometry.GetLocalSize();

    return (LocalMousePos.X >= 0 && LocalMousePos.X <= ImageSize.X &&
        LocalMousePos.Y >= 0 && LocalMousePos.Y <= ImageSize.Y);
}