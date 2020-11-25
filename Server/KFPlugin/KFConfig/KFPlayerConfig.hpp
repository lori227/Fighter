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
	class KFPlayerConfig : public KFConfigT< KFPlayerSetting >, public KFInstance< KFPlayerConfig >
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
			for ( auto& iter : _settings._objects )
			{
				auto kfsetting = iter.second;

				KFGlobal::Instance()->ParseElement( kfsetting->_reward, _file_name.c_str(), kfsetting->_row );
			}
		}

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFPlayerSetting* kfsetting )
		{
			kfsetting->_type = xmlnode.ReadUInt32( "type", true );
			kfsetting->_reward._str_parse = xmlnode.ReadString( "reward", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
