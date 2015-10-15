#include "GWAPIMgr.h"

#include "MemoryMgr.h"
#include "GameThreadMgr.h"

#include "CtoSMgr.h"
#include "AgentMgr.h"
#include "ItemMgr.h"

#include "MerchantMgr.h"

#ifdef GWAPI_USEDIRECTX
#include "DirectXMgr.h"
#endif

#include "SkillbarMgr.h"
#include "EffectMgr.h"

#include "MapMgr.h"

#include "ChatMgr.h"

GWAPI::GWAPIMgr* GWAPI::GWAPIMgr::instance_ = NULL;
HANDLE GWAPI::GWCA::mutex_ = CreateMutexA(NULL, FALSE, NULL);
const DWORD GWAPI::GWCA::API_NO_OWNERSHIP = 0;


bool GWAPI::GWAPIMgr::init_sucessful_;

GWAPI::GWAPIMgr* GWAPI::GWAPIMgr::instance()
{
	return instance_;
}

GWAPI::GWAPIMgr::GWAPIMgr()
{
	if (MemoryMgr::Scan()){
		gamethread_ = new GameThreadMgr(this);
		ctos_ = new CtoSMgr(this);
		agents_ = new AgentMgr(this);
		items_ = new ItemMgr(this);
#ifdef GWAPI_USEDIRECTX
		directx_ = new DirectXMgr(this);
#endif
		skillbar_ = new SkillbarMgr(this);
		effects_ = new EffectMgr(this);
		map_ = new MapMgr(this);
		chat_ = new ChatMgr(this);
		chatcommands_ = new ChatCommandMgr(this);
		merchant_ = new MerchantMgr(this);
		guild_ = new GuildMgr(this);
		fList_ = new FriendListMgr(this);
		stoc_ = new StoCMgr(this);
		camera_ = new CameraMgr(this);
		init_sucessful_ = true;
	}
	else{
		init_sucessful_ = false;
	}
}

GWAPI::GWAPIMgr::~GWAPIMgr()
{
#ifdef GWAPI_USEDIRECTX
	directx_->RestoreHooks();
#endif
	gamethread_->RestoreHooks();
	merchant_->RestoreHooks();
	agents_->RestoreHooks();
	effects_->RestoreHooks();
	chatcommands_->RestoreHook();

	Gamethread()->calls_.clear();
#ifdef GWAPI_USEDIRECTX
	if (directx_) delete directx_;
#endif
	if (gamethread_) delete gamethread_;
	if (map_) delete map_;
	if (guild_) delete guild_;

	if (skillbar_) delete skillbar_;

	if (items_) delete items_;
	if (agents_) delete agents_;

	if (ctos_) delete ctos_;

	if (effects_) delete effects_;
	if (merchant_) delete merchant_;
	if (stoc_) delete stoc_;
	if (chatcommands_) delete chatcommands_;
	if (fList_) delete fList_;
	if (camera_) delete camera_;
}

bool GWAPI::GWAPIMgr::Initialize()
{
	if (!instance_) instance_ = new GWAPIMgr();
	return init_sucessful_;
}

void GWAPI::GWAPIMgr::Destruct()
{
	if (instance_){
		delete instance_;
	}
}

GWAPI::GWCA::GWCA()
{
	if (WaitForSingleObject(mutex_, INFINITE) != WAIT_OBJECT_0)
	{
		throw 1;
	}
	api_ = GWAPIMgr::instance();
}

GWAPI::GWCA::GWCA(DWORD mutex_timeout)
{
	if (mutex_timeout > 0){
		if (WaitForSingleObject(mutex_, mutex_timeout) != WAIT_OBJECT_0)
		{
			throw 1;
		}
	}
	api_ = GWAPIMgr::instance();
}

GWAPI::GWCA::~GWCA() {
	ReleaseMutex(mutex_);
}