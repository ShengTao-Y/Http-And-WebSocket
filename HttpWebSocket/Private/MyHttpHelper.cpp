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
	delete Ins;
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
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &MyHttpHelper::OnGetComplete);
	HttpRequest->ProcessRequest(); //ִ������

}

void MyHttpHelper::OnGetComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed)
{

	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("GET::LoadMgr Request or HttpResponse is not valid"));
		return;
	}

	if (bSuccessed && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		const FString Msg = HttpResponse->GetContentAsString();

		UE_LOG(LogTemp, Warning, TEXT("GET::This is http response: %s"), *Msg);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GET::Read http response failed : %d"), HttpResponse->GetResponseCode());
	}

	HttpRequest->OnProcessRequestComplete().Unbind();
}

void MyHttpHelper::DoHead(const FString& URL)
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("HEAD"));
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json")); //����Content-TypeΪjson����˼�Ǳ������Ͷ˷��͵�ʵ�����ݵ�����Ϊjson��
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json,version=1.0"));//����Acceptָ����json�Ұ汾��Ϊ1.0
	HttpRequest->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed)
		{
			if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
			{
				UE_LOG(LogTemp, Warning, TEXT("HEAD::LoadMgr Request or HttpResponse is not valid"));
				return;
			}

			if (bSuccessed && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
			{
				const FString HeaderLength = HttpResponse->GetHeader(TEXT("Content-Type")); //��ȡHEAD��Content-Length������
				//const int Length = FCString::Atoi(*HeaderLength);

				UE_LOG(LogTemp, Warning, TEXT("HEAD::This is http Content-Length : %s"), *HeaderLength);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HEAD::Read http response failed : %d"), HttpResponse->GetResponseCode());
			}

			HttpRequest->OnProcessRequestComplete().Unbind();
		}
	);
	HttpRequest->ProcessRequest(); //ִ������
}

void MyHttpHelper::DoPost(const FString& URL)
{
	auto HttpRequest = FHttpModule::Get().CreateRequest();

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(TEXT("POST")); //�����GET���ڵ���SetVerbʱ����TEXT(��POST��)
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json")); //����Content-TypeΪjson����˼�Ǳ������Ͷ˷��͵�ʵ�����ݵ�����Ϊjson��
	HttpRequest->SetHeader(TEXT("Accept"), TEXT("application/json,version=1.0"));//����Acceptָ����json�Ұ汾��Ϊ1.0
	HttpRequest->OnProcessRequestComplete().BindRaw(this, &MyHttpHelper::OnPostComplete);
	HttpRequest->ProcessRequest(); //ִ������
}

void MyHttpHelper::OnPostComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccessed)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("POST::LoadMgr Request or HttpResponse is not valid"));
		return;
	}

	if (bSuccessed && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		const FString Msg = HttpResponse->GetContentAsString();

		UE_LOG(LogTemp, Warning, TEXT("POST::This is http response: %s"), *Msg);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("POST::Read http response failed : %d"), HttpResponse->GetResponseCode());
	}

	HttpRequest->OnProcessRequestComplete().Unbind();
}
