#ifndef	__KF_ITEMTYPE_CONFIG_H__
#define	__KF_ITEMTYPE_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFItemTypeSetting : public KFIntSetting
	{
	public:
		// ���ʱ����ı�������
		std::string _obtain_bag;

		// ���ƶ��ı���/�ֿ���
		StringSet _move_bag_list;

		// �ɷ�����ҳǩ����
		StringSet _tab_list;

		// ʹ������
		uint32 _use_limit = 0u;

		// ����˳��
		uint32 _sort = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFItemTypeConfig : public KFConfigT<KFItemTypeSetting>, public KFInstance<KFItemTypeConfig>
	{
	public:
		KFItemTypeConfig()
		{
			_key_name = "type";
			_file_name = "itemtype";
		}

		~KFItemTypeConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFItemTypeSetting> setting )
		{
			setting->_obtain_bag = xml_node.ReadString( "obtainbag", true );
			setting->_move_bag_list = xml_node.ReadStringSet( "movebaglist", true );
			setting->_tab_list = xml_node.ReadStringSet( "tablist", true );
			setting->_use_limit = xml_node.ReadUInt32( "uselimit", true );
			setting->_sort = xml_node.ReadUInt32( "sort", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
