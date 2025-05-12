#include "AIEventTags.h"

// miner's AI event tags
namespace AIEventTags
{
	// The basic Unit State Tags
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventAIControl,
		"AI.State.AIControl",
		"The EventTag that notifies the unit is under AI control.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventAIPlayerControl,
		"AI.State.AIPlayerControl",
		"The EventTag that notifies the unit is under Player control.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventAIStunned,
		"AI.State.Stunned",
		"The EventTag that notifies the unit is stunned.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventAIResetState,
		"AI.State.ResetState",
		"The EventTag that reset the state to Idle.");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventAIRecoverFromStun,
		"AI.State.RecoverFromStun",
		"The EventTag that notifies the unit is recovering from stun.");

    // The EventTag that notifies the resource node is empty.
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(
		EventResourceEmpty,
		"AI.Resource.Empty",
		"The EventTag that notifies the resource node is empty.");
};