#ifndef	__KF_PLAYER_CONFIG_H__
#define	__KF_PLAYER_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFPlayerSetting : public KFIntSetting
	{
	public:
		// ��������(1=���˺�,2=�½�ɫ)
		uint32 _type = 0u;

		// ��õ�����
		KFElements _reward;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFPlayerConfig : public KFConfigT<KFPlayerSetting>, public KFInstance<KFPlayerConfig>
	{
	public:
		KFPlayerConfig()
		{
			_key_name = "row";
			_file_name = "player";
		}

		~KFPlayerConfig() = default;

		virtual void LoadAllComplete()
		{
			for ( auto& iter : _setting_list._objects )
			{
				auto setting = iter.second;

				KFGlobal::Instance()->ParseElement( setting->_reward, _file_name.c_str(), setting->_row );
			}
		}

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFPlayerSetting> setting )
		{
			setting->_type = xml_node.ReadUInt32( "type", true );
			setting->_reward._str_parse = xml_node.ReadString( "reward", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
