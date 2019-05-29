// Fill out your copyright notice in the Description page of Project Settings.

#include "libprotobuf.h"
#include "MyProtobufGameMode.h"

#include "Proto/Test.pb.h"

AMyProtobufGameMode::AMyProtobufGameMode()
{
	SearchRequest Request;

	Request.set_query("test");
	Request.set_page_number(1);
	Request.set_result_per_page(2);

	const std::string Message = Request.SerializeAsString();

	UE_LOG(LogTemp, Display, TEXT("Test protobuf, Request size[%d]."), Message.size());
}


