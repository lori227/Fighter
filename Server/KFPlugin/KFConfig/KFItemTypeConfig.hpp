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
	class KFItemTypeConfig : public KFConfigT< KFItemTypeSetting >, public KFInstance< KFItemTypeConfig >
	{
	public:
		KFItemTypeConfig()
		{
			_key_name = "type";
			_file_name = "itemtype";
		}

		~KFItemTypeConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFItemTypeSetting* kfsetting )
		{
			kfsetting->_obtain_bag = xmlnode.ReadString( "obtainbag", true );
			kfsetting->_move_bag_list = xmlnode.ReadStringSet( "movebaglist", true );
			kfsetting->_tab_list = xmlnode.ReadStringSet( "tablist", true );
			kfsetting->_use_limit = xmlnode.ReadUInt32( "uselimit", true );
			kfsetting->_sort = xmlnode.ReadUInt32( "sort", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
