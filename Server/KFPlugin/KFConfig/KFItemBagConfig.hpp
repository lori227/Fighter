#ifndef	__KF_ITEMBAG_CONFIG_H__
#define	__KF_ITEMBAG_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFItemBagSetting : public KFStrSetting
	{
	public:
		// �������
		uint32 _max_count = 0u;

		// ������������
		std::string _index_name;

		// ҳǩ�б�
		StringSet _tab_list;

		// �����Ƿ񵯳����ⱳ��
		std::string _extend_bag;

		// ��ͬʱʹ�õı���
		StringList _use_child_bag;

		// ����Դ�������ƶ����������Ҫ����
		StringSet _update_add_from_source;

		// �ƶ���Ŀ�걳���ĵ�����Ҫ����
		StringSet _update_move_to_target;

		// �ƶ���Ҫ�ͻ���Ʈ�ֵı���
		StringSet _show_move_to_target;

		// ��ӵ����Ƿ�֪ͨ�ͻ���Ʈ��
		bool _show_when_add = false;

		// �Ƿ�֧��ֱ���ƶ�
		bool _can_move = false;

		// �Ƿ�֧��һ���ƶ�����
		bool _can_move_all = false;

		// �Ƿ�֧��һ�����
		bool _can_cleanup = false;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFItemBagConfig : public KFConfigT<KFItemBagSetting>, public KFInstance<KFItemBagConfig>
	{
	public:
		KFItemBagConfig()
		{
			_key_name = "id";
			_file_name = "itembag";
		}

		~KFItemBagConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFItemBagSetting> setting )
		{
			setting->_max_count = xml_node.ReadUInt32( "maxcount", true );
			setting->_index_name = xml_node.ReadString( "indexname", true );
			setting->_tab_list = xml_node.ReadStringSet( "tablist", true );
			setting->_extend_bag = xml_node.ReadString( "extendbag", true );
			setting->_use_child_bag = xml_node.ReadStringList( "usechildbag", true );
			setting->_update_add_from_source = xml_node.ReadStringSet( "updateaddfromsource", true );
			setting->_update_move_to_target = xml_node.ReadStringSet( "updatemovetotarget", true );
			setting->_show_move_to_target = xml_node.ReadStringSet( "showmovetotarget", true );
			setting->_show_when_add = xml_node.ReadBoolen( "showwhenadd", true );
			setting->_can_move = xml_node.ReadBoolen( "canmove", true );
			setting->_can_move_all = xml_node.ReadBoolen( "canmoveall", true );
			setting->_can_cleanup = xml_node.ReadBoolen( "cancleanup", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
