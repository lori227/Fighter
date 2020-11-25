#ifndef	__KF_SIGN_CONFIG_H__
#define	__KF_SIGN_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFSignSetting : public KFIntSetting
	{
	public:
		// ǩ������
		KFElements _reward;

		// ���⽱������
		uint32 _probability = 0u;

		// ����Ľ���
		KFElements _extend_reward;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFSignConfig : public KFConfigT< KFSignSetting >, public KFInstance< KFSignConfig >
	{
	public:
		KFSignConfig()
		{
			_key_name = "id";
			_file_name = "sign";
		}

		~KFSignConfig() = default;

		virtual void LoadAllComplete()
		{
			for ( auto& iter : _settings._objects )
			{
				auto kfsetting = iter.second;

				KFGlobal::Instance()->ParseElement( kfsetting->_reward, _file_name.c_str(), kfsetting->_row );
				KFGlobal::Instance()->ParseElement( kfsetting->_extend_reward, _file_name.c_str(), kfsetting->_row );
			}
		}

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFSignSetting* kfsetting )
		{
			kfsetting->_reward._str_parse = xmlnode.ReadString( "reward", true );
			kfsetting->_probability = xmlnode.ReadUInt32( "probability", true );
			kfsetting->_extend_reward._str_parse = xmlnode.ReadString( "extendreward", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
