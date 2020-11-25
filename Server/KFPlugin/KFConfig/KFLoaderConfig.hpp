#ifndef	__KF_LOADER_CONFIG_H__
#define	__KF_LOADER_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	class KFConfigData
	{
	public:
		// ������
		std::string _name;

		// �����ļ�·��
		std::string _path;

		// ���ļ�������(���ļ����¼��غ���Ҫ���¼���)
		std::string _parent_name;

		// �Ƿ�������¼���
		bool _can_reload = false;

		// �Ƿ���Ҫ�������
		uint32 _clear_type = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFLoaderSetting : public KFStrSetting
	{
	public:
		// �����ļ��б�
		std::vector<KFConfigData> _config_data;
	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFLoaderConfig : public KFConfigT< KFLoaderSetting >, public KFInstance< KFLoaderConfig >
	{
	public:
		KFLoaderConfig()
		{
			_key_name = "id";
			_file_name = "loader";
		}

		~KFLoaderConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFLoaderSetting* kfsetting )
		{
		
			KFConfigData configdata;
			configdata._name = xmlnode.ReadString( "name" );
			configdata._path = xmlnode.ReadChannelString( "path" );
			configdata._parent_name = xmlnode.ReadString( "parentname" );
			configdata._can_reload = xmlnode.ReadBoolen( "canreload" );
			configdata._clear_type = xmlnode.ReadUInt32( "cleartype" );
			kfsetting->_config_data.push_back( configdata );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
