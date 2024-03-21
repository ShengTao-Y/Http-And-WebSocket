// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpWebSocketFunctionLibrary.h"
#include "MyHttpHelper.h"

void UHttpWebSocketFunctionLibrary::DoGet(const FString& URL)
{
	MyHttpHelper::GetMyHttpHelper()->DoGet(URL); //静态函数 全局可用
}