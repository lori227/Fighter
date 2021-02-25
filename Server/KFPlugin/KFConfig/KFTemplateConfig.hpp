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
	class KFTemplateConfig : public KFConfigT<KFTemplateSetting>, public KFInstance<KFTemplateConfig>
	{
	public:
		KFTemplateConfig()
		{
			_key_name = "id";
			_file_name = "template";
		}

		~KFTemplateConfig() = default;

	protected:
		virtual void ReadSetting( KFXmlNode& xml_node, std::shared_ptr<KFTemplateSetting> setting )
		{
			setting->_type = xml_node.ReadUInt32( "type", true );
			setting->_code = xml_node.ReadUInt32( "code", true );
			setting->_template = xml_node.ReadString( "template", true );
		}

	};

	/////////////////////////////////////////////////////////////////////////////////
}
#endif
