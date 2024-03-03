/*
 * This file is part of EasyScript.
 *
 * EasyScript is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyScript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyScript. If not, see <http://www.gnu.org/licenses/>.
 */

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

void EasyScript::EventCommand::RegisterAll(chaiscript::ChaiScript& chai, State& state) {
	RegisterTypes(chai);

	// END::Register(chai, state);
	CallCommonEvent::Register(chai, state);
	// ForceFlee::Register(chai, state);
	// EnableCombo::Register(chai, state);
	// ChangeClass::Register(chai, state);
	// ChangeBattleCommands::Register(chai, state);
	// OpenLoadMenu::Register(chai, state);
	// ExitGame::Register(chai, state);
	// ToggleAtbMode::Register(chai, state);
	// ToggleFullscreen::Register(chai, state);
	// OpenVideoOptions::Register(chai, state);
	ShowMessage::Register(chai, state);
	MessageOptions::Register(chai, state);
	ChangeFaceGraphic::Register(chai, state);
	// ShowChoice::Register(chai, state);
	// InputNumber::Register(chai, state);
	// ControlSwitches::Register(chai, state);
	// ControlVars::Register(chai, state);
	// TimerOperation::Register(chai, state);
	// ChangeGold::Register(chai, state);
	// ChangeItems::Register(chai, state);
	// ChangePartyMembers::Register(chai, state);
	// ChangeExp::Register(chai, state);
	// ChangeLevel::Register(chai, state);
	// ChangeParameters::Register(chai, state);
	// ChangeSkills::Register(chai, state);
	// ChangeEquipment::Register(chai, state);
	// ChangeHP::Register(chai, state);
	// ChangeSP::Register(chai, state);
	// ChangeCondition::Register(chai, state);
	// FullHeal::Register(chai, state);
	// SimulatedAttack::Register(chai, state);
	// ChangeHeroName::Register(chai, state);
	// ChangeHeroTitle::Register(chai, state);
	// ChangeSpriteAssociation::Register(chai, state);
	// ChangeActorFace::Register(chai, state);
	// ChangeVehicleGraphic::Register(chai, state);
	// ChangeSystemBGM::Register(chai, state);
	// ChangeSystemSFX::Register(chai, state);
	// ChangeSystemGraphics::Register(chai, state);
	// ChangeScreenTransitions::Register(chai, state);
	// EnemyEncounter::Register(chai, state);
	// OpenShop::Register(chai, state);
	// ShowInn::Register(chai, state);
	// EnterHeroName::Register(chai, state);
	// Teleport::Register(chai, state);
	// MemorizeLocation::Register(chai, state);
	// RecallToLocation::Register(chai, state);
	// EnterExitVehicle::Register(chai, state);
	// SetVehicleLocation::Register(chai, state);
	// ChangeEventLocation::Register(chai, state);
	// TradeEventLocations::Register(chai, state);
	// StoreTerrainID::Register(chai, state);
	// StoreEventID::Register(chai, state);
	// EraseScreen::Register(chai, state);
	// ShowScreen::Register(chai, state);
	// TintScreen::Register(chai, state);
	// FlashScreen::Register(chai, state);
	// ShakeScreen::Register(chai, state);
	// PanScreen::Register(chai, state);
	// WeatherEffects::Register(chai, state);
	// ShowPicture::Register(chai, state);
	// MovePicture::Register(chai, state);
	// ErasePicture::Register(chai, state);
	// ShowBattleAnimation::Register(chai, state);
	// PlayerVisibility::Register(chai, state);
	// FlashSprite::Register(chai, state);
	// MoveEvent::Register(chai, state);
	// ProceedWithMovement::Register(chai, state);
	// HaltAllMovement::Register(chai, state);
	// Wait::Register(chai, state);
	PlayBgm::Register(chai, state);
	// FadeOutBGM::Register(chai, state);
	// MemorizeBGM::Register(chai, state);
	// PlayMemorizedBGM::Register(chai, state);
	PlaySound::Register(chai, state);
	// PlayMovie::Register(chai, state);
	// KeyInputProc::Register(chai, state);
	// ChangeMapTileset::Register(chai, state);
	// ChangePBG::Register(chai, state);
	// ChangeEncounterSteps::Register(chai, state);
	// TileSubstitution::Register(chai, state);
	// TeleportTargets::Register(chai, state);
	// ChangeTeleportAccess::Register(chai, state);
	// EscapeTarget::Register(chai, state);
	// ChangeEscapeAccess::Register(chai, state);
	// OpenSaveMenu::Register(chai, state);
	// ChangeSaveAccess::Register(chai, state);
	// OpenMainMenu::Register(chai, state);
	// ChangeMainMenuAccess::Register(chai, state);
	// ConditionalBranch::Register(chai, state);
	// Label::Register(chai, state);
	// JumpToLabel::Register(chai, state);
	// Loop::Register(chai, state);
	// BreakLoop::Register(chai, state);
	// EndEventProcessing::Register(chai, state);
	// EraseEvent::Register(chai, state);
	// CallEvent::Register(chai, state);
	// Comment::Register(chai, state);
	// GameOver::Register(chai, state);
	// ReturntoTitleScreen::Register(chai, state);
	// ChangeMonsterHP::Register(chai, state);
	// ChangeMonsterMP::Register(chai, state);
	// ChangeMonsterCondition::Register(chai, state);
	// ShowHiddenMonster::Register(chai, state);
	// ChangeBattleBG::Register(chai, state);
	// ShowBattleAnimation_B::Register(chai, state);
	// ConditionalBranch_B::Register(chai, state);
	// TerminateBattle::Register(chai, state);
	// ShowChoiceOption::Register(chai, state);
	// ShowChoiceEnd::Register(chai, state);
	// VictoryHandler::Register(chai, state);
	// EscapeHandler::Register(chai, state);
	// DefeatHandler::Register(chai, state);
	// EndBattle::Register(chai, state);
	// Transaction::Register(chai, state);
	// NoTransaction::Register(chai, state);
	// EndShop::Register(chai, state);
	// Stay::Register(chai, state);
	// NoStay::Register(chai, state);
	// EndInn::Register(chai, state);
	// ElseBranch::Register(chai, state);
	// EndBranch::Register(chai, state);
	// EndLoop::Register(chai, state);
	// Comment_2::Register(chai, state);
	// ElseBranch_B::Register(chai, state);
	// EndBranch_B::Register(chai, state);
	// Maniac_GetSaveInfo::Register(chai, state);
	// Maniac_Save::Register(chai, state);
	// Maniac_Load::Register(chai, state);
	// Maniac_EndLoadProcess::Register(chai, state);
	// Maniac_GetMousePosition::Register(chai, state);
	// Maniac_SetMousePosition::Register(chai, state);
	// Maniac_ShowStringPicture::Register(chai, state);
	// Maniac_GetPictureInfo::Register(chai, state);
	// Maniac_ControlBattle::Register(chai, state);
	// Maniac_ControlAtbGauge::Register(chai, state);
	// Maniac_ChangeBattleCommandEx::Register(chai, state);
	// Maniac_GetBattleInfo::Register(chai, state);
	// Maniac_ControlVarArray::Register(chai, state);
	// Maniac_KeyInputProcEx::Register(chai, state);
	// Maniac_RewriteMap::Register(chai, state);
	// Maniac_ControlGlobalSave::Register(chai, state);
	// Maniac_ChangePictureId::Register(chai, state);
	// Maniac_SetGameOption::Register(chai, state);
	// Maniac_CallCommand::Register(chai, state);
	// Maniac_ControlStrings::Register(chai, state);
	// Maniac_GetGameInfo::Register(chai, state);
	// Maniac_EditPicture::Register(chai, state);
	// Maniac_WritePicture::Register(chai, state);
	// Maniac_AddMoveRoute::Register(chai, state);
	// Maniac_EditTile::Register(chai, state);
	// Maniac_ControlTextProcessing::Register(chai, state);
	TriggerEventAt::Register(chai, state);
	UnknownCommand::Register(chai, state);
}
