require "core/core"

require "logic/base/base"
require "logic/ui/ui"
require "logic/framework/framework"
require "logic/netPlayerData/netPlayerData"
require "logic/common/common"
require "logic/gameState/gameState"
require "logic/commonPrompt/commonPrompt"
require "logic/checkVersion/checkVersion"
require "logic/batchUpdate/batchUpdate"
require "logic/serverAuth/serverAuth"
require "logic/login/login"
require "logic/pvpMatch/pvpMatch"
require "logic/mainCampsite/mainCampsite"
require "logic/pack/pack"
require "logic/recruitmentOffice/recruitmentOffice"
require "logic/gameSetting/gameSetting"
require "logic/commConfirm/commConfirm"
require "logic/roleList/roleList"
require "logic/teamManagement/teamManagement"
require "logic/tips/tips"
require "logic/widgetClass/widgetClass"



g_LanguageCfg = require "configs/language/Language"
g_UITextCfg = require "configs/uitext/UIText"
g_recruitDivisorCfg = require "configs/recruitdivisor/RecruitDivisor"
g_heroRaceCfg = require "configs/HeroRace/HeroRace"
g_heroProfessionCfg = require "configs/HeroProfession/HeroProfession"

g_RecruitmentOfficeConfig = CRecruitmentOfficeConfig.New()

g_Config = CConfig.New()
g_GameFSM = CFSM.New()
g_Facade = CFacade.New()
g_View = CView.New()
g_Model = CModel.New()
g_Controller = CController.New()
g_MediatorFactory = CMediatorFactory.New()
g_NetPlayerDataCtrl = CNetPlayerDataCtrl.New()

g_TimeCtrl = CTimeCtrl.New()
g_TipsFactory = CTipsFactory.New()