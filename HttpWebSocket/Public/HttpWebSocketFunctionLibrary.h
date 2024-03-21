// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HttpWebSocketFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class HTTPWEBSOCKET_API UHttpWebSocketFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void DoGet(const FString& URL);

	UFUNCTION(BlueprintCallable)
	static void DoHead(const FString& URL);
	
};
