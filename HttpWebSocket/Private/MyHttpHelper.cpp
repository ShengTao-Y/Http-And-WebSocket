// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHttpHelper.h"
#include "HttpModule.h"


//��̬����ʹ��ǰ�趨��
MyHttpHelper* MyHttpHelper::Ins = nullptr;

MyHttpHelper::MyHttpHelper()
{

}

MyHttpHelper::~MyHttpHelper()
{
}

MyHttpHelper* MyHttpHelper::GetMyHttpHelper()
{
	if (Ins == nullptr)
	{
		Ins = new MyHttpHelper();
	}
	return Ins;
	
}

void MyHttpHelper::DoGet(const FString& URL)
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("GET"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json")); //����Content-TypeΪjson����˼�Ǳ������Ͷ˷��͵�ʵ�����ݵ�����Ϊjson��
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json,version=1.0"));//����Acceptָ����json�Ұ汾��Ϊ1.0
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &MyHttpHelper::OnLoadComplete);
	HttpRequest->ProcessRequest(); //ִ������


}

void MyHttpHelper::OnLoadComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed)
{


	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("LoadMgr Request or HttpResponse is not valid"));
		return;
	}
	

	if (bSuccessed && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		const FString Msg = HttpResponse->GetContentAsString();

		UE_LOG(LogTemp, Warning, TEXT("This is http response: %s"), *Msg);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Read http response failed : %d"), HttpResponse->GetResponseCode());
	}

	HttpRequest->OnProcessRequestComplete().Unbind();
}