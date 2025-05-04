#pragma once
#include "NativeGameplayTags.h"

// The miner's AI event tags
namespace AIEventTags
{
	// The basic Unit State Tags
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventAIControl);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventAIPlayerControl);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventAIStunned);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventAIResetState);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventAIRecoverFromStun);

	// The EventTag that notifies the resource node is empty.
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(EventResourceEmpty);
};
	