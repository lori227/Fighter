require "core/core"
require "framework/framework"

require "logic/ui/ui"
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

g_Config = CConfig.New()
g_GameFSM = CFSM.New()
g_Facade = CFacade.New()
g_View = CView.New()
g_Model = CModel.New()
g_Controller = CController.New()

g_ConfigManager = CConfigManager.New()
g_UIManager = CUIManager.New()
