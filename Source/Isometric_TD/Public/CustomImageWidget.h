// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomImageWidget.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class ISOMETRIC_TD_API UCustomImageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    // События теперь передают индекс Image
    UFUNCTION(BlueprintImplementableEvent)
    void OnImageHovered(int32 ImageIndex);

    UFUNCTION(BlueprintImplementableEvent)
    void OnImageUnhovered(int32 ImageIndex);

    UFUNCTION(BlueprintCallable)
    void RegisterImage(UImage* Image);

protected:
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

    UPROPERTY(meta = (BindWidget))
    class UCanvasPanel* MainCanvas;

private:
    UPROPERTY()
    TArray<UImage*> Images;

    int32 FindImageUnderMouse(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
    bool IsMouseOverImage(UImage* Image, const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

    int32 CurrentHoveredIndex;
};
