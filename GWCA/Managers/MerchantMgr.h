#pragma once

#include <Windows.h>

#include "GWCAManager.h"
#include <GWCA\GameEntities\Item.h>

namespace GW {

	struct TransactionInfo {
		DWORD itemcount;
		DWORD* itemids;
		DWORD* itemquantities;
	};

	struct QuoteInfo {
		DWORD unknown; // = 0
		DWORD itemcount;
		DWORD* itemids;
	};

	enum TransactionType : DWORD {
		MerchantBuy = 0x1,
		CollectorBuy,
		CrafterBuy,
		WeaponsmithCustomize,

		MerchantSell = 0xB,
		TraderBuy,
		TraderSell,

		UnlockRunePriestOfBalth = 0xF
	};

	class MerchantMgr : public GWCAManager<MerchantMgr> {
		friend class GWCAManager<MerchantMgr>;

	public:
		MerchantMgr();

		void TransactItems(TransactionType type,
			DWORD gold_give,
			TransactionInfo give,
			DWORD gold_recv,
			TransactionInfo recv
		);

		void RequestQuote(TransactionType type,
			QuoteInfo give,
			QuoteInfo recv
		);

		// note: can contain pointers to random items from your inventory
		GW::MerchItemArray GetMerchantItemsArray();

		//DWORD GetQuotedItemPrice();
	};
}
