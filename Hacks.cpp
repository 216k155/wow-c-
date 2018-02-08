#include "LHack.hpp"

void Hacks::Init ()
{
	// Hook CGWorldFrame::Render to run code in the main thread every frame. This can be hooked instead of EndScene or Present, and is not DirectX-dependent.
	WoW::Render = reinterpret_cast<bool (__thiscall*)(unsigned int)>(DetourFunction(reinterpret_cast<byte*>(WoWBase + CGWorldFrame__Render), reinterpret_cast<byte*>(WoW::FrameHook)));
	Misc::SetCommandHook();

	// Unlock Lua
	const byte LuaUnlock[] = {0x8B, 0xE5, 0x5D, 0xC3};
	Write(WoWBase + SomeLuaFunction + 0x21D, LuaUnlock, 4);

	// To stop those damn pop-ups
	const byte NoPopups[] = {0x90, 0xE9};
	Write(WoWBase + CGGameUI__ShowBlockedActionFeedback + 0x10, NoPopups, 2);

	// Zoom Hack
	Write<byte>(WoWBase + CGCamera__UpdateMotion_ulong_ + 0x238, static_cast<byte>(0xF0));

	// Show all levels hack
	Write<byte>(WoWBase + Script_UnitLevel + 0xB6, 0xEB);

	// No Away hack
	const byte NOPs[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	Write(WoWBase + CGGameUI__Idle + 0x151, NOPs, 5);
	
	// Language hack
	const byte LanguageHack[] = {0xB8, 0x1, 0x0, 0x0, 0x0, 0xC2, 0x08, 0x0};
	Write(WoWBase + IsKnownLanguage, LanguageHack, 8);

	// Understanding all languages didn't work for some people. This should fix that.
	Write<byte>(WoWBase + ObfuscateLanguage + 0x75, 0x3A);
	
	// Follow any hack
	Write(WoWBase + CGUnit_C__SetTrackingTarget + 0x86, NOPs, 5);

	WoW::AddChatMessage("LHack loaded.");
	return;
}