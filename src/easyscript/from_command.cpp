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

// Todo: Branching event commands
// ShowChoice, ShowChoiceCommand, EndChoice <- DONE
// ConditionalBranch, ElseBranch, EndBranch
// CondionalBranch_B, ElseBranch_B, EndBranch_B
// Loop, EndLoop
// EnemyEncounter, VictoryHandler, EscapeHandler, DefeatHandler, EndBattle
// OpenShop, Transaction, NoTransaction, EndShop
// Stay, NoStay, EndInn

#include "from_command.h"
#include "all_commands.h"
#include "commands/change_face_graphic.h"
#include "commands/message_options.h"
#include "commands/play_bgm.h"
#include "commands/play_sound.h"
#include "commands/unknown_command.h"
#include "commands/unknown_branch_command.h"
#include "event_command.h"
#include "state.h"

#include <format>
#include <lcf/dbstring.h>
#include <lcf/rpg/eventcommand.h>
#include <string>
#include <vector>

template<typename Class>
std::string build_string_auto(const EasyScript::EventCommand& command) {
	std::string line = std::format("@{}.{}", Class::name[1], Class::name[2]);

	if constexpr (requires { Class::constructor_param; }) {
		line += "(" + Class::constructor_param.ToString(command, false) + ")";
	} else if constexpr (requires { Class::string_param; } ) {
		line += Class::string_param.ToString(command);
	}

	if constexpr (requires { Class::param; } ) {
		for (auto& param: Class::param) {
			if constexpr (requires { Class::StringFromParameter(command, param); }) {
				auto ret = Class::StringFromParameter(command, param);
				if (ret) {
					line += *ret;
				} else {
					if (!param.IsDefault(command)) {
						line += param.ToString(command);
					}
				}
			} else {
				if (!param.IsDefault(command)) {
					line += param.ToString(command);
				}
			}
		}
	}

	return line;
}

template<typename Class>
std::string build_string(const EasyScript::EventCommand& command) {
	if constexpr (requires { Class::StringFromCommand(command); }) {
		auto res = Class::StringFromCommand(command);
		if (res) {
			return *res;
		}
	}

	return build_string_auto<Class>(command);
}

std::string build_unknown_string(const EasyScript::EventCommand& command) {
	switch (command.code) {
		case EasyScript::Code::ConditionalBranch:
		case EasyScript::Code::ConditionalBranch_B:
		case EasyScript::Code::Loop:
		case EasyScript::Code::EnemyEncounter:
		case EasyScript::Code::OpenShop:
		case EasyScript::Code::Stay:
			return *EasyScript::UnknownBranchCommand::StringFromCommand(command);
		default:
			break;
	}

	return *EasyScript::UnknownCommand::StringFromCommand(command);
}

struct CommandState {
	int show_choice_cancel = -1;
	int show_choice_child_count = -1;
};

std::vector<std::string> EasyScript::FromCommandList(const State& state) {
	std::vector<std::string> lines;
	auto& commands = state.commands;
	const EventCommand* parent;

	std::vector<CommandState> cmd_states = {};
	const auto parent_commands = {Code::ShowChoice, Code::ConditionalBranch, Code::ConditionalBranch_B, Code::Loop, Code::EnemyEncounter, Code::OpenShop, Code::Stay};
	const auto unk_branch_commands = {Code::ElseBranch, Code::ElseBranch_B, Code::VictoryHandler, Code::EscapeHandler, Code::DefeatHandler, Code::Transaction, Code::NoTransaction, Code::NoStay};

	for (size_t i = 0; i < commands.size(); ++i) {
		auto& command = commands[i];

		if (std::find(parent_commands.begin(), parent_commands.end(), command->code) != parent_commands.end()) {
			parent = &*command;
		}

		if (command->code == Code::ShowMessage) {
			EventCommandList sub_commands = {command};
			for (i = i + 1; i < commands.size(); ++i) {
				auto& sub_command = commands[i];
				if (sub_command->code == Code::ShowMessage_2) {
					sub_commands.push_back(sub_command);
				} else {
					--i;
					break;
				}
			}
			lines.push_back(*ShowMessage::StringFromCommand(sub_commands));
		} else if (command->code == Code::ShowChoiceOption) {
			lines.push_back(*ShowChoiceOption::StringFromCommand(commands, i, *parent));
		} else if (std::find(unk_branch_commands.begin(), unk_branch_commands.end(), command->code) != unk_branch_commands.end()) {
			lines.push_back(*UnknownElseCommand::StringFromCommand(commands, i, *parent));
		} else {
			lines.push_back(FromCommand(*command));
		}
	}

	return lines;
}

std::vector<std::string> EasyScript::FromCommandList(const std::vector<lcf::rpg::EventCommand>& commands) {
	EventCommandList list;

	for (auto& command: commands) {
		EventCommand cmd;
		cmd.code = static_cast<Code>(command.code);
		cmd.indent = command.indent;
		cmd.string = lcf::ToString(command.string);
		cmd.parameters = { command.parameters.begin(), command.parameters.end() };
		list.emplace_back(std::make_shared<EventCommand>(cmd));
	}

	State state;
	state.commands = list;

	return FromCommandList(state);
}

std::string EasyScript::FromCommand(const EventCommand& command) {
	switch (command.code) {
		case Code::END:
			return {};
		case Code::CallCommonEvent:
			return build_string<CallCommonEvent>(command);
		//case Code::ForceFlee:
		//	return build_string<ForceFlee>(command);
		//case Code::EnableCombo:
		//	return build_string<EnableCombo>(command);
		//case Code::ChangeClass:
		//	return build_string<ChangeClass>(command);
		//case Code::ChangeBattleCommands:
		//	return build_string<ChangeBattleCommands>(command);
		//case Code::OpenLoadMenu:
		//	return build_string<OpenLoadMenu>(command);
		//case Code::ExitGame:
		//	return build_string<ExitGame>(command);
		//case Code::ToggleAtbMode:
		//	return build_string<ToggleAtbMode>(command);
		//case Code::ToggleFullscreen:
		//	return build_string<ToggleFullscreen>(command);
		//case Code::OpenVideoOptions:
		//	return build_string<OpenVideoOptions>(command);
		case Code::ShowMessage:
			assert(false);
			return {};
		case Code::MessageOptions:
			return build_string<MessageOptions>(command);
		case Code::ChangeFaceGraphic:
			return build_string<ChangeFaceGraphic>(command);
		case Code::ShowChoice:
			return build_string<ShowChoice>(command) + " {";
		//case Code::InputNumber:
		//	return build_string<InputNumber>(command);
		//case Code::ControlSwitches:
		//	return build_string<ControlSwitches>(command);
		//case Code::ControlVars:
		//	return build_string<ControlVars>(command);
		//case Code::TimerOperation:
		//	return build_string<TimerOperation>(command);
		case Code::ChangeGold:
			return build_string<ChangeGold>(command);
		//case Code::ChangeItems:
		//	return build_string<ChangeItems>(command);
		//case Code::ChangePartyMembers:
		//	return build_string<ChangePartyMembers>(command);
		//case Code::ChangeExp:
		//	return build_string<ChangeExp>(command);
		//case Code::ChangeLevel:
		//	return build_string<ChangeLevel>(command);
		//case Code::ChangeParameters:
		//	return build_string<ChangeParameters>(command);
		//case Code::ChangeSkills:
		//	return build_string<ChangeSkills>(command);
		//case Code::ChangeEquipment:
		//	return build_string<ChangeEquipment>(command);
		//case Code::ChangeHP:
		//	return build_string<ChangeHP>(command);
		//case Code::ChangeSP:
		//	return build_string<ChangeSP>(command);
		//case Code::ChangeCondition:
		//	return build_string<ChangeCondition>(command);
		//case Code::FullHeal:
		//	return build_string<FullHeal>(command);
		//case Code::SimulatedAttack:
		//	return build_string<SimulatedAttack>(command);
		//case Code::ChangeHeroName:
		//	return build_string<ChangeHeroName>(command);
		//case Code::ChangeHeroTitle:
		//	return build_string<ChangeHeroTitle>(command);
		//case Code::ChangeSpriteAssociation:
		//	return build_string<ChangeSpriteAssociation>(command);
		//case Code::ChangeActorFace:
		//	return build_string<ChangeActorFace>(command);
		//case Code::ChangeVehicleGraphic:
		//	return build_string<ChangeVehicleGraphic>(command);
		//case Code::ChangeSystemBGM:
		//	return build_string<ChangeSystemBGM>(command);
		//case Code::ChangeSystemSFX:
		//	return build_string<ChangeSystemSFX>(command);
		//case Code::ChangeSystemGraphics:
		//	return build_string<ChangeSystemGraphics>(command);
		//case Code::ChangeScreenTransitions:
		//	return build_string<ChangeScreenTransitions>(command);
		//case Code::EnemyEncounter:
		//	return build_string<EnemyEncounter>(command);
		//case Code::OpenShop:
		//	return build_string<OpenShop>(command);
		//case Code::ShowInn:
		//	return build_string<ShowInn>(command);
		//case Code::EnterHeroName:
		//	return build_string<EnterHeroName>(command);
		//case Code::Teleport:
		//	return build_string<Teleport>(command);
		//case Code::MemorizeLocation:
		//	return build_string<MemorizeLocation>(command);
		//case Code::RecallToLocation:
		//	return build_string<RecallToLocation>(command);
		//case Code::EnterExitVehicle:
		//	return build_string<EnterExitVehicle>(command);
		//case Code::SetVehicleLocation:
		//	return build_string<SetVehicleLocation>(command);
		//case Code::ChangeEventLocation:
		//	return build_string<ChangeEventLocation>(command);
		//case Code::TradeEventLocations:
		//	return build_string<TradeEventLocations>(command);
		//case Code::StoreTerrainID:
		//	return build_string<StoreTerrainID>(command);
		//case Code::StoreEventID:
		//	return build_string<StoreEventID>(command);
		//case Code::EraseScreen:
		//	return build_string<EraseScreen>(command);
		//case Code::ShowScreen:
		//	return build_string<ShowScreen>(command);
		//case Code::TintScreen:
		//	return build_string<TintScreen>(command);
		//case Code::FlashScreen:
		//	return build_string<FlashScreen>(command);
		//case Code::ShakeScreen:
		//	return build_string<ShakeScreen>(command);
		//case Code::PanScreen:
		//	return build_string<PanScreen>(command);
		//case Code::WeatherEffects:
		//	return build_string<WeatherEffects>(command);
		//case Code::ShowPicture:
		//	return build_string<ShowPicture>(command);
		//case Code::MovePicture:
		//	return build_string<MovePicture>(command);
		//case Code::ErasePicture:
		//	return build_string<ErasePicture>(command);
		//case Code::ShowBattleAnimation:
		//	return build_string<ShowBattleAnimation>(command);
		//case Code::PlayerVisibility:
		//	return build_string<PlayerVisibility>(command);
		//case Code::FlashSprite:
		//	return build_string<FlashSprite>(command);
		//case Code::MoveEvent:
		//	return build_string<MoveEvent>(command);
		//case Code::ProceedWithMovement:
		//	return build_string<ProceedWithMovement>(command);
		//case Code::HaltAllMovement:
		//	return build_string<HaltAllMovement>(command);
		//case Code::Wait:
		//	return build_string<Wait>(command);
		case Code::PlayBGM:
			return build_string<PlayBgm>(command);
		//case Code::FadeOutBGM:
		//	return build_string<FadeOutBGM>(command);
		//case Code::MemorizeBGM:
		//	return build_string<MemorizeBGM>(command);
		//case Code::PlayMemorizedBGM:
		//	return build_string<PlayMemorizedBGM>(command);
		case Code::PlaySound:
			return build_string<PlaySound>(command);
		//case Code::PlayMovie:
		//	return build_string<PlayMovie>(command);
		//case Code::KeyInputProc:
		//	return build_string<KeyInputProc>(command);
		//case Code::ChangeMapTileset:
		//	return build_string<ChangeMapTileset>(command);
		//case Code::ChangePBG:
		//	return build_string<ChangePBG>(command);
		//case Code::ChangeEncounterSteps:
		//	return build_string<ChangeEncounterSteps>(command);
		//case Code::TileSubstitution:
		//	return build_string<TileSubstitution>(command);
		//case Code::TeleportTargets:
		//	return build_string<TeleportTargets>(command);
		//case Code::ChangeTeleportAccess:
		//	return build_string<ChangeTeleportAccess>(command);
		//case Code::EscapeTarget:
		//	return build_string<EscapeTarget>(command);
		//case Code::ChangeEscapeAccess:
		//	return build_string<ChangeEscapeAccess>(command);
		//case Code::OpenSaveMenu:
		//	return build_string<OpenSaveMenu>(command);
		//case Code::ChangeSaveAccess:
		//	return build_string<ChangeSaveAccess>(command);
		//case Code::OpenMainMenu:
		//	return build_string<OpenMainMenu>(command);
		//case Code::ChangeMainMenuAccess:
		//	return build_string<ChangeMainMenuAccess>(command);
		//case Code::ConditionalBranch:
		//	return build_string<ConditionalBranch>(command);
		case Code::Label:
		case Code::JumpToLabel:
			return build_string<Label>(command);
		//case Code::Loop:
		//	return build_string<Loop>(command);
		//case Code::BreakLoop:
		//	return build_string<BreakLoop>(command);
		//case Code::EndEventProcessing:
		//	return build_string<EndEventProcessing>(command);
		//case Code::EraseEvent:
		//	return build_string<EraseEvent>(command);
		//case Code::CallEvent:
		//	return build_string<CallEvent>(command);
		case Code::Comment:
			assert(false);
			return {};
		//case Code::GameOver:
		//	return build_string<GameOver>(command);
		//case Code::ReturntoTitleScreen:
		//	return build_string<ReturntoTitleScreen>(command);
		//case Code::ChangeMonsterHP:
		//	return build_string<ChangeMonsterHP>(command);
		//case Code::ChangeMonsterMP:
		//	return build_string<ChangeMonsterMP>(command);
		//case Code::ChangeMonsterCondition:
		//	return build_string<ChangeMonsterCondition>(command);
		//case Code::ShowHiddenMonster:
		//	return build_string<ShowHiddenMonster>(command);
		//case Code::ChangeBattleBG:
		//	return build_string<ChangeBattleBG>(command);
		//case Code::ShowBattleAnimation_B:
		//	return build_string<ShowBattleAnimation_B>(command);
		//case Code::ConditionalBranch_B:
		//	return build_string<ConditionalBranch_B>(command);
		//case Code::TerminateBattle:
		//	return build_string<TerminateBattle>(command);
		case Code::ShowMessage_2:
			assert(false);
			return {};
		case Code::ShowChoiceOption:
			assert(false);
			return {};
		case Code::ShowChoiceEnd:
			return "}";
		//case Code::VictoryHandler:
		//	return build_string<VictoryHandler>(command);
		//case Code::EscapeHandler:
		//	return build_string<EscapeHandler>(command);
		//case Code::DefeatHandler:
		//	return build_string<DefeatHandler>(command);
		//case Code::EndBattle:
		//	return build_string<EndBattle>(command);
		//case Code::Transaction:
		//	return build_string<Transaction>(command);
		//case Code::NoTransaction:
		//	return build_string<NoTransaction>(command);
		//case Code::EndShop:
		//	return build_string<EndShop>(command);
		//case Code::Stay:
		//	return build_string<Stay>(command);
		//case Code::NoStay:
		//	return build_string<NoStay>(command);
		//case Code::EndInn:
		//	return build_string<EndInn>(command);
		//case Code::ElseBranch:
		//	return build_string<ElseBranch>(command);
		//case Code::EndBranch:
		//	return build_string<EndBranch>(command);
		//case Code::EndLoop:
		//	return build_string<EndLoop>(command);
		case Code::Comment_2:
			assert(false);
			return {};
		//case Code::ElseBranch_B:
		//	return build_string<ElseBranch_B>(command);
		//case Code::EndBranch_B:
		//	return build_string<EndBranch_B>(command);
		//case Code::Maniac_GetSaveInfo:
		//	return build_string<Maniac_GetSaveInfo>(command);
		//case Code::Maniac_Save:
		//	return build_string<Maniac_Save>(command);
		//case Code::Maniac_Load:
		//	return build_string<Maniac_Load>(command);
		//case Code::Maniac_EndLoadProcess:
		//	return build_string<Maniac_EndLoadProcess>(command);
		//case Code::Maniac_GetMousePosition:
		//	return build_string<Maniac_GetMousePosition>(command);
		//case Code::Maniac_SetMousePosition:
		//	return build_string<Maniac_SetMousePosition>(command);
		//case Code::Maniac_ShowStringPicture:
		//	return build_string<Maniac_ShowStringPicture>(command);
		//case Code::Maniac_GetPictureInfo:
		//	return build_string<Maniac_GetPictureInfo>(command);
		//case Code::Maniac_ControlBattle:
		//	return build_string<Maniac_ControlBattle>(command);
		//case Code::Maniac_ControlAtbGauge:
		//	return build_string<Maniac_ControlAtbGauge>(command);
		//case Code::Maniac_ChangeBattleCommandEx:
		//	return build_string<Maniac_ChangeBattleCommandEx>(command);
		//case Code::Maniac_GetBattleInfo:
		//	return build_string<Maniac_GetBattleInfo>(command);
		//case Code::Maniac_ControlVarArray:
		//	return build_string<Maniac_ControlVarArray>(command);
		//case Code::Maniac_KeyInputProcEx:
		//	return build_string<Maniac_KeyInputProcEx>(command);
		//case Code::Maniac_RewriteMap:
		//	return build_string<Maniac_RewriteMap>(command);
		//case Code::Maniac_ControlGlobalSave:
		//	return build_string<Maniac_ControlGlobalSave>(command);
		//case Code::Maniac_ChangePictureId:
		//	return build_string<Maniac_ChangePictureId>(command);
		//case Code::Maniac_SetGameOption:
		//	return build_string<Maniac_SetGameOption>(command);
		//case Code::Maniac_CallCommand:
		//	return build_string<Maniac_CallCommand>(command);
		//case Code::Maniac_ControlStrings:
		//	return build_string<Maniac_ControlStrings>(command);
		//case Code::Maniac_GetGameInfo:
		//	return build_string<Maniac_GetGameInfo>(command);
		//case Code::Maniac_EditPicture:
		//	return build_string<Maniac_EditPicture>(command);
		//case Code::Maniac_WritePicture:
		//	return build_string<Maniac_WritePicture>(command);
		//case Code::Maniac_AddMoveRoute:
		//	return build_string<Maniac_AddMoveRoute>(command);
		//case Code::Maniac_EditTile:
		//	return build_string<Maniac_EditTile>(command);
		//case Code::Maniac_ControlTextProcessing:
		//	return build_string<Maniac_ControlTextProcessing>(command);
		default:
			break;
	}

	if (command.code == static_cast<Code>(2002)) {
		return build_string<TriggerEventAt>(command);
	}

	return build_unknown_string(command);
}

std::string EasyScript::FromCommand(const lcf::rpg::EventCommand& command) {
	EventCommand cmd;
	cmd.code = static_cast<Code>(command.code);
	cmd.indent = command.indent;
	cmd.string = lcf::ToString(command.string);
	cmd.parameters = { command.parameters.begin(), command.parameters.end() };

	return FromCommand(cmd);
}
