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
	class KFItemConfig : public KFConfigT<KFItemSetting>, public KFInstance<KFItemConfig>
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
			for ( auto& iter : _setting_list._objects )
			{
				auto setting = iter.second;

				KFGlobal::Instance()->ParseElement( setting->_sell, _file_name.c_str(), setting->_row );
			}
		}

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFItemSetting> setting )
		{
			setting->_type = xml_node.ReadUInt32( "type", true );
			setting->_quality = xml_node.ReadUInt32( "quality", true );
			setting->_overlay_type = xml_node.ReadUInt32( "overlaytype", true );
			setting->_overlay_count = xml_node.ReadUInt32( "overlaycount", true );
			setting->_use_count = xml_node.ReadUInt32( "usecount", true );
			setting->_use_limit = xml_node.ReadUInt32( "uselimit", true );
			setting->_sell._str_parse = xml_node.ReadString( "sell", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
