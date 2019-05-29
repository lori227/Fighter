// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "libprotobuf/Public/MyProtobufGameMode.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMyProtobufGameMode() {}
// Cross Module References
	LIBPROTOBUF_API UClass* Z_Construct_UClass_AMyProtobufGameMode_NoRegister();
	LIBPROTOBUF_API UClass* Z_Construct_UClass_AMyProtobufGameMode();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_libprotobuf();
// End Cross Module References
	void AMyProtobufGameMode::StaticRegisterNativesAMyProtobufGameMode()
	{
	}
	UClass* Z_Construct_UClass_AMyProtobufGameMode_NoRegister()
	{
		return AMyProtobufGameMode::StaticClass();
	}
	struct Z_Construct_UClass_AMyProtobufGameMode_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AMyProtobufGameMode_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_libprotobuf,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AMyProtobufGameMode_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "MyProtobufGameMode.h" },
		{ "ModuleRelativePath", "Public/MyProtobufGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AMyProtobufGameMode_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AMyProtobufGameMode>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AMyProtobufGameMode_Statics::ClassParams = {
		&AMyProtobufGameMode::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x008002A8u,
		METADATA_PARAMS(Z_Construct_UClass_AMyProtobufGameMode_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AMyProtobufGameMode_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AMyProtobufGameMode()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AMyProtobufGameMode_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AMyProtobufGameMode, 3882755887);
	template<> LIBPROTOBUF_API UClass* StaticClass<AMyProtobufGameMode>()
	{
		return AMyProtobufGameMode::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AMyProtobufGameMode(Z_Construct_UClass_AMyProtobufGameMode, &AMyProtobufGameMode::StaticClass, TEXT("/Script/libprotobuf"), TEXT("AMyProtobufGameMode"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AMyProtobufGameMode);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
