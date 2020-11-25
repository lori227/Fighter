#ifndef	__KF_ZONE_CONFIG_H__
#define	__KF_ZONE_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFZoneSetting : public KFIntSetting
	{
	public:
		// ��¼��С��id
		uint32 _login_id = 0u;

		// ���ݿ�С��id
		uint32 _data_id = 0u;

		// С������
		std::string _name;

		// С�����
		uint32 _flag = 0u;

		// �Ƽ���ʶ
		uint32 _recommend = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFZoneConfig : public KFConfigT< KFZoneSetting >, public KFInstance< KFZoneConfig >
	{
	public:
		KFZoneConfig()
		{
			_key_name = "id";
			_file_name = "zone";
		}

		~KFZoneConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFZoneSetting* kfsetting )
		{
			kfsetting->_login_id = xmlnode.ReadUInt32( "loginid", true );
			kfsetting->_data_id = xmlnode.ReadUInt32( "dataid", true );
			kfsetting->_name = xmlnode.ReadString( "name", true );
			kfsetting->_flag = xmlnode.ReadUInt32( "flag", true );
			kfsetting->_recommend = xmlnode.ReadUInt32( "recommend", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
