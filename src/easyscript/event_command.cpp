#include "event_command.h"
#include "chaiscript/chaiscript.hpp"
#include "all_commands.h"
#include "easyscript/commands/unknown_command.h"
#include "types.h"
#include <memory>
#include <stdexcept>

void EasyScript::EventCommand::SetDefaults(Code code, std::string_view string, std::initializer_list<int32_t> parameters) {
	this->code = code;
	this->string = string;
	this->parameters = std::vector<int32_t>(parameters.begin(), parameters.end());
}

std::string EasyScript::EventCommand::GetEscapedString() const {
	std::string out;
	out.reserve(this->string.size());

	for (char ch: string) {
		if (ch == '\\') {
			out += '\\';
		}
		out += ch;
	}

	return out;
}

void EasyScript::EventCommand::RegisterAll(chaiscript::ChaiScript& chai, EventCommandList& commands) {
	RegisterTypes(chai);

	// END::Register(chai, commands);
	CallCommonEvent::Register(chai, commands);
	// ForceFlee::Register(chai, commands);
	// EnableCombo::Register(chai, commands);
	// ChangeClass::Register(chai, commands);
	// ChangeBattleCommands::Register(chai, commands);
	// OpenLoadMenu::Register(chai, commands);
	// ExitGame::Register(chai, commands);
	// ToggleAtbMode::Register(chai, commands);
	// ToggleFullscreen::Register(chai, commands);
	// OpenVideoOptions::Register(chai, commands);
	ShowMessage::Register(chai, commands);
	MessageOptions::Register(chai, commands);
	ChangeFaceGraphic::Register(chai, commands);
	// ShowChoice::Register(chai, commands);
	// InputNumber::Register(chai, commands);
	// ControlSwitches::Register(chai, commands);
	// ControlVars::Register(chai, commands);
	// TimerOperation::Register(chai, commands);
	// ChangeGold::Register(chai, commands);
	// ChangeItems::Register(chai, commands);
	// ChangePartyMembers::Register(chai, commands);
	// ChangeExp::Register(chai, commands);
	// ChangeLevel::Register(chai, commands);
	// ChangeParameters::Register(chai, commands);
	// ChangeSkills::Register(chai, commands);
	// ChangeEquipment::Register(chai, commands);
	// ChangeHP::Register(chai, commands);
	// ChangeSP::Register(chai, commands);
	// ChangeCondition::Register(chai, commands);
	// FullHeal::Register(chai, commands);
	// SimulatedAttack::Register(chai, commands);
	// ChangeHeroName::Register(chai, commands);
	// ChangeHeroTitle::Register(chai, commands);
	// ChangeSpriteAssociation::Register(chai, commands);
	// ChangeActorFace::Register(chai, commands);
	// ChangeVehicleGraphic::Register(chai, commands);
	// ChangeSystemBGM::Register(chai, commands);
	// ChangeSystemSFX::Register(chai, commands);
	// ChangeSystemGraphics::Register(chai, commands);
	// ChangeScreenTransitions::Register(chai, commands);
	// EnemyEncounter::Register(chai, commands);
	// OpenShop::Register(chai, commands);
	// ShowInn::Register(chai, commands);
	// EnterHeroName::Register(chai, commands);
	// Teleport::Register(chai, commands);
	// MemorizeLocation::Register(chai, commands);
	// RecallToLocation::Register(chai, commands);
	// EnterExitVehicle::Register(chai, commands);
	// SetVehicleLocation::Register(chai, commands);
	// ChangeEventLocation::Register(chai, commands);
	// TradeEventLocations::Register(chai, commands);
	// StoreTerrainID::Register(chai, commands);
	// StoreEventID::Register(chai, commands);
	// EraseScreen::Register(chai, commands);
	// ShowScreen::Register(chai, commands);
	// TintScreen::Register(chai, commands);
	// FlashScreen::Register(chai, commands);
	// ShakeScreen::Register(chai, commands);
	// PanScreen::Register(chai, commands);
	// WeatherEffects::Register(chai, commands);
	// ShowPicture::Register(chai, commands);
	// MovePicture::Register(chai, commands);
	// ErasePicture::Register(chai, commands);
	// ShowBattleAnimation::Register(chai, commands);
	// PlayerVisibility::Register(chai, commands);
	// FlashSprite::Register(chai, commands);
	// MoveEvent::Register(chai, commands);
	// ProceedWithMovement::Register(chai, commands);
	// HaltAllMovement::Register(chai, commands);
	// Wait::Register(chai, commands);
	PlayBgm::Register(chai, commands);
	// FadeOutBGM::Register(chai, commands);
	// MemorizeBGM::Register(chai, commands);
	// PlayMemorizedBGM::Register(chai, commands);
	PlaySound::Register(chai, commands);
	// PlayMovie::Register(chai, commands);
	// KeyInputProc::Register(chai, commands);
	// ChangeMapTileset::Register(chai, commands);
	// ChangePBG::Register(chai, commands);
	// ChangeEncounterSteps::Register(chai, commands);
	// TileSubstitution::Register(chai, commands);
	// TeleportTargets::Register(chai, commands);
	// ChangeTeleportAccess::Register(chai, commands);
	// EscapeTarget::Register(chai, commands);
	// ChangeEscapeAccess::Register(chai, commands);
	// OpenSaveMenu::Register(chai, commands);
	// ChangeSaveAccess::Register(chai, commands);
	// OpenMainMenu::Register(chai, commands);
	// ChangeMainMenuAccess::Register(chai, commands);
	// ConditionalBranch::Register(chai, commands);
	// Label::Register(chai, commands);
	// JumpToLabel::Register(chai, commands);
	// Loop::Register(chai, commands);
	// BreakLoop::Register(chai, commands);
	// EndEventProcessing::Register(chai, commands);
	// EraseEvent::Register(chai, commands);
	// CallEvent::Register(chai, commands);
	// Comment::Register(chai, commands);
	// GameOver::Register(chai, commands);
	// ReturntoTitleScreen::Register(chai, commands);
	// ChangeMonsterHP::Register(chai, commands);
	// ChangeMonsterMP::Register(chai, commands);
	// ChangeMonsterCondition::Register(chai, commands);
	// ShowHiddenMonster::Register(chai, commands);
	// ChangeBattleBG::Register(chai, commands);
	// ShowBattleAnimation_B::Register(chai, commands);
	// ConditionalBranch_B::Register(chai, commands);
	// TerminateBattle::Register(chai, commands);
	// ShowChoiceOption::Register(chai, commands);
	// ShowChoiceEnd::Register(chai, commands);
	// VictoryHandler::Register(chai, commands);
	// EscapeHandler::Register(chai, commands);
	// DefeatHandler::Register(chai, commands);
	// EndBattle::Register(chai, commands);
	// Transaction::Register(chai, commands);
	// NoTransaction::Register(chai, commands);
	// EndShop::Register(chai, commands);
	// Stay::Register(chai, commands);
	// NoStay::Register(chai, commands);
	// EndInn::Register(chai, commands);
	// ElseBranch::Register(chai, commands);
	// EndBranch::Register(chai, commands);
	// EndLoop::Register(chai, commands);
	// Comment_2::Register(chai, commands);
	// ElseBranch_B::Register(chai, commands);
	// EndBranch_B::Register(chai, commands);
	// Maniac_GetSaveInfo::Register(chai, commands);
	// Maniac_Save::Register(chai, commands);
	// Maniac_Load::Register(chai, commands);
	// Maniac_EndLoadProcess::Register(chai, commands);
	// Maniac_GetMousePosition::Register(chai, commands);
	// Maniac_SetMousePosition::Register(chai, commands);
	// Maniac_ShowStringPicture::Register(chai, commands);
	// Maniac_GetPictureInfo::Register(chai, commands);
	// Maniac_ControlBattle::Register(chai, commands);
	// Maniac_ControlAtbGauge::Register(chai, commands);
	// Maniac_ChangeBattleCommandEx::Register(chai, commands);
	// Maniac_GetBattleInfo::Register(chai, commands);
	// Maniac_ControlVarArray::Register(chai, commands);
	// Maniac_KeyInputProcEx::Register(chai, commands);
	// Maniac_RewriteMap::Register(chai, commands);
	// Maniac_ControlGlobalSave::Register(chai, commands);
	// Maniac_ChangePictureId::Register(chai, commands);
	// Maniac_SetGameOption::Register(chai, commands);
	// Maniac_CallCommand::Register(chai, commands);
	// Maniac_ControlStrings::Register(chai, commands);
	// Maniac_GetGameInfo::Register(chai, commands);
	// Maniac_EditPicture::Register(chai, commands);
	// Maniac_WritePicture::Register(chai, commands);
	// Maniac_AddMoveRoute::Register(chai, commands);
	// Maniac_EditTile::Register(chai, commands);
	// Maniac_ControlTextProcessing::Register(chai, commands);
	TriggerEventAt::Register(chai, commands);
	UnknownCommand::Register(chai, commands);
}
