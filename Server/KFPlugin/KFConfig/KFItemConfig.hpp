#ifndef	__KF_ITEM_CONFIG_H__
#define	__KF_ITEM_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFItemSetting : public KFIntSetting
	{
	public:
		// ����
		uint32 _type = 0u;

		// Ʒ��
		uint32 _quality = 0u;

		// �ѵ�����
		uint32 _overlay_type = 0u;

		// �ѵ�����
		uint32 _overlay_count = 0u;

		// ʹ�ô���
		uint32 _use_count = 0u;

		// ʹ������
		uint32 _use_limit = 0u;

		// ���ۼ۸�
		KFElements _sell;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFItemConfig : public KFConfigT< KFItemSetting >, public KFInstance< KFItemConfig >
	{
	public:
		KFItemConfig()
		{
			_key_name = "id";
			_file_name = "item";
		}

		~KFItemConfig() = default;

		virtual void LoadAllComplete()
		{
			for ( auto& iter : _settings._objects )
			{
				auto kfsetting = iter.second;

				KFGlobal::Instance()->ParseElement( kfsetting->_sell, _file_name.c_str(), kfsetting->_row );
			}
		}

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFItemSetting* kfsetting )
		{
			kfsetting->_type = xmlnode.ReadUInt32( "type", true );
			kfsetting->_quality = xmlnode.ReadUInt32( "quality", true );
			kfsetting->_overlay_type = xmlnode.ReadUInt32( "overlaytype", true );
			kfsetting->_overlay_count = xmlnode.ReadUInt32( "overlaycount", true );
			kfsetting->_use_count = xmlnode.ReadUInt32( "usecount", true );
			kfsetting->_use_limit = xmlnode.ReadUInt32( "uselimit", true );
			kfsetting->_sell._str_parse = xmlnode.ReadString( "sell", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
