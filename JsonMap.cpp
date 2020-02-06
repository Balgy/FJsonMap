#include "JsonMap.h"

FJsonMap::FJsonMap()
{
	
}

FJsonMap::FJsonMap(std::initializer_list<FJsonMapInput> InList)
{
	for (auto& Elem : InList)
	{
		InternalObjectMap.Add(Elem.Get());
	}
}

FString FJsonMap::ToString()
{
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	for (auto& Elem : InternalObjectMap)
	{
		auto ElemValue = Elem.Value.Get();
		if (ElemValue.IsType<int32>())
		{
			JsonObject->SetNumberField(Elem.Key, ElemValue.Get<int32>());
		}
		else if (ElemValue.IsType<FString>())
		{
			JsonObject->SetStringField(Elem.Key, ElemValue.Get<FString>());
		}
		else if (ElemValue.IsType<bool>())
		{
			JsonObject->SetBoolField(Elem.Key, ElemValue.Get<bool>());
		}
		else if (ElemValue.IsType<float>())
		{
			JsonObject->SetNumberField(Elem.Key, ElemValue.Get<float>());
		}
	}

	FString OutputString = "";
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject, Writer);

	return OutputString;
}

FJsonMapValue::FJsonMapValue()
{
	InternalValue.Set<int32>(0);
}

FJsonMapValue::FJsonMapValue(int32 InInt)
{
	InternalValue.Set<int32>(InInt);
}

FJsonMapValue::FJsonMapValue(float InFloat)
{
	InternalValue.Set<float>(InFloat);
}

FJsonMapValue::FJsonMapValue(const FString& InString)
{
	InternalValue.Set<FString>(InString);
}

FJsonMapValue::FJsonMapValue(bool InBool)
{
	InternalValue.Set<bool>(InBool);
}

TVariant<FString, int32, bool, float > FJsonMapValue::Get() const
{
	return InternalValue;
}

FString FJsonMapValue::ToString()
{
	if (InternalValue.IsType<int32>())
	{
		return FString::FromInt(InternalValue.Get<int32>());
	}
	else if (InternalValue.IsType<FString>())
	{
		return InternalValue.Get<FString>();
	}
	else if (InternalValue.IsType<bool>())
	{
		return FString::FromInt(InternalValue.Get<bool>());
	}
	else if (InternalValue.IsType<float>())
	{
		return FString::SanitizeFloat(InternalValue.Get<float>());
	}

	return "";
}

FJsonMapInput::FJsonMapInput()
{

}

FJsonMapInput::FJsonMapInput(const char* InKeyName, int32 InInt)
{
	InternalValue = TTuple<FString, FJsonMapValue >(FString(InKeyName), FJsonMapValue(InInt));
}

FJsonMapInput::FJsonMapInput(const char* InKeyName, float InFloat)
{
	InternalValue = TTuple<FString, FJsonMapValue >(FString(InKeyName), FJsonMapValue(InFloat));
}

FJsonMapInput::FJsonMapInput(const char* InKeyName, const char* InString)
{
	InternalValue = TTuple<FString, FJsonMapValue >(FString(InKeyName), FJsonMapValue(FString(InString)));
}

FJsonMapInput::FJsonMapInput(const char* InKeyName, bool InBool)
{
	InternalValue = TTuple<FString, FJsonMapValue >(FString(InKeyName), FJsonMapValue(InBool));
}

FJsonMapInput::FJsonMapInput(const char* InKeyName, const FString& InString)
{
	InternalValue = TTuple<FString, FJsonMapValue >(FString(InKeyName), FJsonMapValue(InString));
}

TTuple<FString, FJsonMapValue > FJsonMapInput::Get() const
{
	return TTuple<FString, FJsonMapValue >(InternalValue.Key, FJsonMapValue(InternalValue.Value));
}