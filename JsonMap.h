#include "CoreMinimal.h"
#include "Misc/TVariant.h"
#include <initializer_list>

class FJsonMapValue
{
public:
	FJsonMapValue();

	FJsonMapValue(int32 InInt);
	FJsonMapValue(float InFloat);
	FJsonMapValue(const FString& InString);
	FJsonMapValue(bool InBool);

	TVariant<FString, int32, bool, float > Get() const;

	FString ToString();
private:
	TVariant<FString, int32, bool, float > InternalValue;
};

class FJsonMapInput
{
public:
	FJsonMapInput();

	FJsonMapInput(const char* InKeyName, int32 InInt);
	FJsonMapInput(const char* InKeyName, float InFloat);
	FJsonMapInput(const char* InKeyName, const char* InString);
	FJsonMapInput(const char* InKeyName, const FString& InString);
	FJsonMapInput(const char* InKeyName, bool InBool);

	TTuple<FString, FJsonMapValue > Get() const;
private:
	TTuple<FString, FJsonMapValue > InternalValue;
};

class FJsonMap
{
public:
	FJsonMap();
	FJsonMap(std::initializer_list<FJsonMapInput> InList);

	FString ToString();

private:
	TMap<FString, FJsonMapValue> InternalObjectMap;
};