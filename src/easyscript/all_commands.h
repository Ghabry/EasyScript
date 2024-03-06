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

#pragma once

#include "event_command.h"
// END = 10,
#include "commands/call_common_event.h"
// ForceFlee = 1006,
// EnableCombo = 1007,
// ChangeClass = 1008,
// ChangeBattleCommands = 1009,
// OpenLoadMenu = 5001,
// ExitGame = 5002,
// ToggleAtbMode = 5003,
// ToggleFullscreen = 5004,
// OpenVideoOptions = 5005,
#include "commands/show_message.h"
#include "commands/message_options.h"
#include "commands/change_face_graphic.h"
#include "commands/show_choice.h"
// InputNumber = 10150,
// ControlSwitches = 10210,
// ControlVars = 10220,
// TimerOperation = 10230,
#include "commands/change_gold.h"
// ChangeItems = 10320,
// ChangePartyMembers = 10330,
// ChangeExp = 10410,
// ChangeLevel = 10420,
// ChangeParameters = 10430,
// ChangeSkills = 10440,
// ChangeEquipment = 10450,
// ChangeHP = 10460,
// ChangeSP = 10470,
// ChangeCondition = 10480,
// FullHeal = 10490,
// SimulatedAttack = 10500,
// ChangeHeroName = 10610,
// ChangeHeroTitle = 10620,
// ChangeSpriteAssociation = 10630,
// ChangeActorFace = 10640,
// ChangeVehicleGraphic = 10650,
// ChangeSystemBGM = 10660,
// ChangeSystemSFX = 10670,
// ChangeSystemGraphics = 10680,
// ChangeScreenTransitions = 10690,
// EnemyEncounter = 10710,
// OpenShop = 10720,
// ShowInn = 10730,
// EnterHeroName = 10740,
// Teleport = 10810,
// MemorizeLocation = 10820,
// RecallToLocation = 10830,
// EnterExitVehicle = 10840,
// SetVehicleLocation = 10850,
// ChangeEventLocation = 10860,
// TradeEventLocations = 10870,
// StoreTerrainID = 10910,
// StoreEventID = 10920,
// EraseScreen = 11010,
// ShowScreen = 11020,
// TintScreen = 11030,
// FlashScreen = 11040,
// ShakeScreen = 11050,
// PanScreen = 11060,
// WeatherEffects = 11070,
// ShowPicture = 11110,
// MovePicture = 11120,
// ErasePicture = 11130,
// ShowBattleAnimation = 11210,
// PlayerVisibility = 11310,
// FlashSprite = 11320,
// MoveEvent = 11330,
// ProceedWithMovement = 11340,
// HaltAllMovement = 11350,
// Wait = 11410,
#include "commands/play_bgm.h"
// FadeOutBGM = 11520,
// MemorizeBGM = 11530,
// PlayMemorizedBGM = 11540,
#include "commands/play_sound.h"
// PlayMovie = 11560,
// KeyInputProc = 11610,
// ChangeMapTileset = 11710,
// ChangePBG = 11720,
// ChangeEncounterSteps = 11740,
// TileSubstitution = 11750,
// TeleportTargets = 11810,
// ChangeTeleportAccess = 11820,
// EscapeTarget = 11830,
// ChangeEscapeAccess = 11840,
// OpenSaveMenu = 11910,
// ChangeSaveAccess = 11930,
// OpenMainMenu = 11950,
// ChangeMainMenuAccess = 11960,
// ConditionalBranch = 12010,
#include "commands/label.h"
// Loop = 12210,
// BreakLoop = 12220,
// EndEventProcessing = 12310,
// EraseEvent = 12320,
// CallEvent = 12330,
// Comment = 12410,
// GameOver = 12420,
// ReturntoTitleScreen = 12510,
// ChangeMonsterHP = 13110,
// ChangeMonsterMP = 13120,
// ChangeMonsterCondition = 13130,
// ShowHiddenMonster = 13150,
// ChangeBattleBG = 13210,
// ShowBattleAnimation_B = 13260,
// ConditionalBranch_B = 13310,
// TerminateBattle = 13410,
// VictoryHandler = 20710,
// EscapeHandler = 20711,
// DefeatHandler = 20712,
// EndBattle = 20713,
// Transaction = 20720,
// NoTransaction = 20721,
// EndShop = 20722,
// Stay = 20730,
// NoStay = 20731,
// EndInn = 20732,
// ElseBranch = 22010,
// EndBranch = 22011,
// EndLoop = 22210,
// Comment_2 = 22410,
// ElseBranch_B = 23310,
// EndBranch_B = 23311,
// Maniac_GetSaveInfo = 3001,
// Maniac_Save = 3002,
// Maniac_Load = 3003,
// Maniac_EndLoadProcess = 3004,
// Maniac_GetMousePosition = 3005,
// Maniac_SetMousePosition = 3006,
// Maniac_ShowStringPicture = 3007,
// Maniac_GetPictureInfo = 3008,
// Maniac_ControlBattle = 3009,
// Maniac_ControlAtbGauge = 3010,
// Maniac_ChangeBattleCommandEx = 3011,
// Maniac_GetBattleInfo = 3012,
// Maniac_ControlVarArray = 3013,
// Maniac_KeyInputProcEx = 3014,
// Maniac_RewriteMap = 3015,
// Maniac_ControlGlobalSave = 3016,
// Maniac_ChangePictureId = 3017,
// Maniac_SetGameOption = 3018,
// Maniac_CallCommand = 3019,
// Maniac_ControlStrings = 3020,
// Maniac_GetGameInfo = 3021,
// Maniac_EditPicture = 3025,
// Maniac_WritePicture = 3026,
// Maniac_AddMoveRoute = 3027,
// Maniac_EditTile = 3028,
// Maniac_ControlTextProcessing = 3029
#include "commands/trigger_event_at.h"
#include "commands/unknown_command.h"
#include "commands/unknown_branch_command.h"
