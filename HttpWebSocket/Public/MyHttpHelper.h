// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IHttpRequest.h"


/**
 * 
 */
class MyHttpHelper;

class MyHttpHelper
{
public:
	MyHttpHelper();
	~MyHttpHelper();

	static MyHttpHelper* GetMyHttpHelper();

public:
	void DoGet(const FString& URL);
	void OnGetComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed);

	void DoHead(const FString& URL);

	void DoPost(const FString& URL);
	void OnPostComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed);

private:
	 static MyHttpHelper* Ins;
};
