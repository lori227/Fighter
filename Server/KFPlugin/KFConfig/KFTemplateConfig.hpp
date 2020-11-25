#ifndef	__KF_TEMPLATE_CONFIG_H__
#define	__KF_TEMPLATE_CONFIG_H__

#include "KFConfig.h"

namespace KFrame
{
	/////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	class KFTemplateSetting : public KFStrSetting
	{
	public:
		// ����
		uint32 _type = 0u;

		// ����
		uint32 _code = 0u;

		// ����
		std::string _template;

	};

	/////////////////////////////////////////////////////////////////////////////////
	class KFTemplateConfig : public KFConfigT< KFTemplateSetting >, public KFInstance< KFTemplateConfig >
	{
	public:
		KFTemplateConfig()
		{
			_key_name = "id";
			_file_name = "template";
		}

		~KFTemplateConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xmlnode, KFTemplateSetting* kfsetting )
		{
			kfsetting->_type = xmlnode.ReadUInt32( "type", true );
			kfsetting->_code = xmlnode.ReadUInt32( "code", true );
			kfsetting->_template = xmlnode.ReadString( "template", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
