#pragma once

#include <Windows.h>

#include <GWCA\Context\GuildContext.h>
#include <GWCA\GameEntities\Guild.h>

namespace GW {

	namespace GuildMgr {

		GW::GuildContext* GetGuildContext();

		// Array of guilds, holds basically everything about a guild. Can get structs of all players in outpost ;)
		GW::GuildArray GetGuildArray();

		// Index in guild array of player guild.
		DWORD GetPlayerGuildIndex();

		// Announcement in guild at the moment.
		wchar_t* GetPlayerGuildAnnouncement();

		// Name of player who last edited the announcement.
		wchar_t* GetPlayerGuildAnnouncer();

		void TravelGH();

		void TravelGH(GW::GHKey key);

		void LeaveGH();
	};
}
