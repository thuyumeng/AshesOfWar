// the utility header file for the AttributeSet classes

#pragma once
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"


// Macro that simplifies the declaration of accessor functions for attributes.
// Example: ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health) creates:
// - static FGameplayAttribute GetHealthAttribute();
// - float GetHealth() const;
// - void SetHealth(float NewVal);
// - void InitHealth(float NewVal);
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Gets the raw numeric value of an attribute from an attribute set instance
#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)