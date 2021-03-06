// Fill out your copyright notice in the Description page of Project Settings.

#include "UIFlipbook.h"
#include "SUIFlipbookImage.h"
#include "Engine/Texture2D.h"


//LOCTEXT
#define LOCTEXT_NAMESPACE "UMG"

UUIFlipbook::UUIFlipbook(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
    , Duration(0.05f)
    , LoopInterval(0.0f)
    , ColumnCount(1)
    , RowCount(1)
    , CutFrameCount(0)
    , ColorAndOpacity(FLinearColor::White)
{

}


void UUIFlipbook::PlayAnimation(bool ShouldLoop, bool InShouldNotifyAtEnd /*= false*/)
{
    if (!MyImage.IsValid())
    {
        return;
    }

    MyImage->PlayAnimation(ShouldLoop, InShouldNotifyAtEnd);
}

void UUIFlipbook::PauseAnimation()
{
    if (!MyImage.IsValid())
    {
        return;
    }

    MyImage->PauseAnimation();
}

void UUIFlipbook::ResumeAnimation()
{
    if (!MyImage.IsValid())
    {
        return;
    }

    MyImage->ResumeAnimation();
}

void UUIFlipbook::StopAnimation(bool ShouldnotifyAnimationEndEvent)
{
    if (!MyImage.IsValid())
    {
        return;
    }

    MyImage->StopAnimation(ShouldnotifyAnimationEndEvent);
}

void UUIFlipbook::ResetAnimation()
{
    if (!MyImage.IsValid())
    {
        return;
    }

    MyImage->ResetAnimation();
}

bool UUIFlipbook::IsAnimationPlaying()
{
    if (!MyImage.IsValid())
    {
        return false;
    }

    return  MyImage->IsAnimationPlaying();
}

bool UUIFlipbook::IsAnimationPaused()
{
    if (!MyImage.IsValid())
    {
        return false;
    }

    return  MyImage->IsAnimationPaused();
}


void UUIFlipbook::HandleAnimationEnd()
{
    OnAnimationEnd.Broadcast();
}


TSharedRef<SWidget> UUIFlipbook::RebuildWidget()
{
    MyImage = SNew(SUIFlipbookImage);

    return MyImage.ToSharedRef();
}

void UUIFlipbook::SynchronizeProperties()
{
    Super::SynchronizeProperties();

    TAttribute<FSlateColor> ColorAndOpacityBinding = PROPERTY_BINDING(FSlateColor, ColorAndOpacity);

    if (MyImage.IsValid())
    {
        MyImage->SetDuration(Duration);
        MyImage->SetLoopInterval(LoopInterval);
        MyImage->SetColumnCount(ColumnCount);
        MyImage->SetRowCount(RowCount);
        MyImage->SetCutFrameCount(CutFrameCount);
        MyImage->SetOnAnimationEnd(BIND_UOBJECT_DELEGATE(FAnimationEndDelegate, HandleAnimationEnd));
        MyImage->SetColorAndOpacity(ColorAndOpacityBinding);
        MyImage->SetImageRes(FlipbookImage);

        //After changing the properties we should reset the animation.
        MyImage->ResetAnimation();

        if (bAutoPlayLoop)
        {
            MyImage->PlayAnimation(true);
        }
        else
        {
            MyImage->StopAnimation(false);
        }
    }
}



void UUIFlipbook::ReleaseSlateResources(bool bReleaseChildren)
{
    Super::ReleaseSlateResources(bReleaseChildren);

    MyImage.Reset();
}

#if WITH_EDITOR



const FText UUIFlipbook::GetPaletteCategory()
{
    return LOCTEXT("Common", "Custom Widget");
}
#endif

#undef LOCTEXT_NAMESPACE