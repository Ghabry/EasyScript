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
#include "commands/unknown_command.h"
#include "state.h"
#include "types.h"
#include <memory>
#include <stdexcept>

EasyScript::EventCommand::EventCommand(Code code, int32_t indent)
	: code(code),
	  indent(indent)
{

}

EasyScript::EventCommand::EventCommand(Code code, int32_t indent, std::string string, std::vector<int32_t> parameters)
	: code(code),
	  indent(indent),
	  string(std::move(string)),
	  parameters(std::move(parameters))
{

}

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

void EasyScript::EventCommand::RegisterAll(State& state) {
	auto& chai = state.chai;
	RegisterTypes(chai);

	// END::Register(state);
	CallCommonEvent::Register(state);
	// ForceFlee::Register(state);
	// EnableCombo::Register(state);
	// ChangeClass::Register(state);
	// ChangeBattleCommands::Register(state);
	// OpenLoadMenu::Register(state);
	// ExitGame::Register(state);
	// ToggleAtbMode::Register(state);
	// ToggleFullscreen::Register(state);
	// OpenVideoOptions::Register(state);
	ShowMessage::Register(state);
	MessageOptions::Register(state);
	ChangeFaceGraphic::Register(state);
	ShowChoice::Register(state);
	// InputNumber::Register(state);
	// ControlSwitches::Register(state);
	// ControlVars::Register(state);
	// TimerOperation::Register(state);
	// ChangeGold::Register(state);
	// ChangeItems::Register(state);
	// ChangePartyMembers::Register(state);
	// ChangeExp::Register(state);
	// ChangeLevel::Register(state);
	// ChangeParameters::Register(state);
	// ChangeSkills::Register(state);
	// ChangeEquipment::Register(state);
	// ChangeHP::Register(state);
	// ChangeSP::Register(state);
	// ChangeCondition::Register(state);
	// FullHeal::Register(state);
	// SimulatedAttack::Register(state);
	// ChangeHeroName::Register(state);
	// ChangeHeroTitle::Register(state);
	// ChangeSpriteAssociation::Register(state);
	// ChangeActorFace::Register(state);
	// ChangeVehicleGraphic::Register(state);
	// ChangeSystemBGM::Register(state);
	// ChangeSystemSFX::Register(state);
	// ChangeSystemGraphics::Register(state);
	// ChangeScreenTransitions::Register(state);
	// EnemyEncounter::Register(state);
	// OpenShop::Register(state);
	// ShowInn::Register(state);
	// EnterHeroName::Register(state);
	// Teleport::Register(state);
	// MemorizeLocation::Register(state);
	// RecallToLocation::Register(state);
	// EnterExitVehicle::Register(state);
	// SetVehicleLocation::Register(state);
	// ChangeEventLocation::Register(state);
	// TradeEventLocations::Register(state);
	// StoreTerrainID::Register(state);
	// StoreEventID::Register(state);
	// EraseScreen::Register(state);
	// ShowScreen::Register(state);
	// TintScreen::Register(state);
	// FlashScreen::Register(state);
	// ShakeScreen::Register(state);
	// PanScreen::Register(state);
	// WeatherEffects::Register(state);
	// ShowPicture::Register(state);
	// MovePicture::Register(state);
	// ErasePicture::Register(state);
	// ShowBattleAnimation::Register(state);
	// PlayerVisibility::Register(state);
	// FlashSprite::Register(state);
	// MoveEvent::Register(state);
	// ProceedWithMovement::Register(state);
	// HaltAllMovement::Register(state);
	// Wait::Register(state);
	PlayBgm::Register(state);
	// FadeOutBGM::Register(state);
	// MemorizeBGM::Register(state);
	// PlayMemorizedBGM::Register(state);
	PlaySound::Register(state);
	// PlayMovie::Register(state);
	// KeyInputProc::Register(state);
	// ChangeMapTileset::Register(state);
	// ChangePBG::Register(state);
	// ChangeEncounterSteps::Register(state);
	// TileSubstitution::Register(state);
	// TeleportTargets::Register(state);
	// ChangeTeleportAccess::Register(state);
	// EscapeTarget::Register(state);
	// ChangeEscapeAccess::Register(state);
	// OpenSaveMenu::Register(state);
	// ChangeSaveAccess::Register(state);
	// OpenMainMenu::Register(state);
	// ChangeMainMenuAccess::Register(state);
	// ConditionalBranch::Register(state);
	// Label::Register(state);
	// JumpToLabel::Register(state);
	// Loop::Register(state);
	// BreakLoop::Register(state);
	// EndEventProcessing::Register(state);
	// EraseEvent::Register(state);
	// CallEvent::Register(state);
	// Comment::Register(state);
	// GameOver::Register(state);
	// ReturntoTitleScreen::Register(state);
	// ChangeMonsterHP::Register(state);
	// ChangeMonsterMP::Register(state);
	// ChangeMonsterCondition::Register(state);
	// ShowHiddenMonster::Register(state);
	// ChangeBattleBG::Register(state);
	// ShowBattleAnimation_B::Register(state);
	// ConditionalBranch_B::Register(state);
	// TerminateBattle::Register(state);
	// ShowChoiceOption::Register(state);
	// ShowChoiceEnd::Register(state);
	// VictoryHandler::Register(state);
	// EscapeHandler::Register(state);
	// DefeatHandler::Register(state);
	// EndBattle::Register(state);
	// Transaction::Register(state);
	// NoTransaction::Register(state);
	// EndShop::Register(state);
	// Stay::Register(state);
	// NoStay::Register(state);
	// EndInn::Register(state);
	// ElseBranch::Register(state);
	// EndBranch::Register(state);
	// EndLoop::Register(state);
	// Comment_2::Register(state);
	// ElseBranch_B::Register(state);
	// EndBranch_B::Register(state);
	// Maniac_GetSaveInfo::Register(state);
	// Maniac_Save::Register(state);
	// Maniac_Load::Register(state);
	// Maniac_EndLoadProcess::Register(state);
	// Maniac_GetMousePosition::Register(state);
	// Maniac_SetMousePosition::Register(state);
	// Maniac_ShowStringPicture::Register(state);
	// Maniac_GetPictureInfo::Register(state);
	// Maniac_ControlBattle::Register(state);
	// Maniac_ControlAtbGauge::Register(state);
	// Maniac_ChangeBattleCommandEx::Register(state);
	// Maniac_GetBattleInfo::Register(state);
	// Maniac_ControlVarArray::Register(state);
	// Maniac_KeyInputProcEx::Register(state);
	// Maniac_RewriteMap::Register(state);
	// Maniac_ControlGlobalSave::Register(state);
	// Maniac_ChangePictureId::Register(state);
	// Maniac_SetGameOption::Register(state);
	// Maniac_CallCommand::Register(state);
	// Maniac_ControlStrings::Register(state);
	// Maniac_GetGameInfo::Register(state);
	// Maniac_EditPicture::Register(state);
	// Maniac_WritePicture::Register(state);
	// Maniac_AddMoveRoute::Register(state);
	// Maniac_EditTile::Register(state);
	// Maniac_ControlTextProcessing::Register(state);
	TriggerEventAt::Register(state);
	UnknownCommand::Register(state);
}
