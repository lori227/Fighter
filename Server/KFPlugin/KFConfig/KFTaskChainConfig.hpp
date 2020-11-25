#ifndef	__KF_TASKCHAIN_CONFIG_H__
#define	__KF_TASKCHAIN_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	class TaskChainData
	{
	public:
		// ��������
		uint32 _index = 0u;

		// ����
		uint32 _type = 0u;

		// ����id/�����id
		uint32 _task = 0u;

		// ����״̬
		uint32 _task_status = 0u;

		// ���ӿ�������
		uint32 _extend_type = 0u;

		// ���ӿ���������id/��
		uint32 _extend_chain = 0u;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFTaskChainSetting : public KFIntSetting
	{
	public:
		// ����������
		std::vector<TaskChainData> _task_chain_data;
	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFTaskChainConfig : public KFConfigT< KFTaskChainSetting >, public KFInstance< KFTaskChainConfig >
	{
	public:
		KFTaskChainConfig()
		{
			_key_name = "id";
			_file_name = "taskchain";
		}

		~KFTaskChainConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFTaskChainSetting* kfsetting )
		{
		
			TaskChainData taskchaindata;
			taskchaindata._index = xmlnode.ReadUInt32( "index" );
			taskchaindata._type = xmlnode.ReadUInt32( "type" );
			taskchaindata._task = xmlnode.ReadUInt32( "task" );
			taskchaindata._task_status = xmlnode.ReadUInt32( "taskstatus" );
			taskchaindata._extend_type = xmlnode.ReadUInt32( "extendtype" );
			taskchaindata._extend_chain = xmlnode.ReadUInt32( "extendchain" );
			kfsetting->_task_chain_data.push_back( taskchaindata );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
